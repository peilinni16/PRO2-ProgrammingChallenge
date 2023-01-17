/** @file Cjt_Clusters.cc
    @brief Implementación de la clase Cjt_Clusters
 */

#include "Cjt_Clusters.hh"
using namespace std; 

Cjt_Clusters::Cjt_Clusters() { }

void Cjt_Clusters::busca_minimo(string &id1, string &id2, double &d1)
{
    string aux_id1, aux_id2;
    double min;
    map<string, map<string, double> >::iterator it = clust_dist.begin();
    map<string, double>::iterator it2 = (it->second).begin();

    min = it2->second;
    aux_id1 = it->first;
    aux_id2 = it2->first;
    ++it2;

    while (it != clust_dist.end()) {
        map<string, double>::iterator it3 = (it->second).begin();
        while (it3 != (it->second).end()) {
            if (it3->second < min) {
                min = it3->second;
                aux_id1 = it->first;
                aux_id2 = it3->first;
                ++it3;
            }
            else ++it3;
        } ++it;
    }
    id1 = aux_id1;
    id2 = aux_id2;
    d1 = min;
}

bool Cjt_Clusters::es_posible() const
{
    return clust_dist.size() > 1;
}

bool Cjt_Clusters::existe_cluster(const string &id1) const
{
    if (conj_clust.find(id1) != conj_clust.end()) return true;
    else return false;
}

bool Cjt_Clusters::vacio() const
{
    return clust_dist.empty();
}

void Cjt_Clusters::aniadir_cluster(const Cluster &c1)
{
    conj_clust.insert(make_pair(c1.consulta_id_arbol(), c1));
}

void Cjt_Clusters::aniadir_distancia(const string& id1, const string &id2, const double &d1) 
{
    map<string, map<string, double> >::iterator it = clust_dist.find(id1);
    if (it != clust_dist.end()) {
        (it->second).insert(make_pair(id2, d1));
    }
    else {
        map<string, double> a;
        a.insert(make_pair(id2, d1));
        clust_dist.insert(make_pair(id1, a));
    }
}

void Cjt_Clusters::aniadir(const string &id1)
{
    clust_dist.insert(make_pair(id1, map<string, double>()));
}

void Cjt_Clusters::ejecuta_paso_wpgma()
{
    string id1, id2;
    double d1;
    busca_minimo(id1, id2, d1);
    actualiza_cjt_clusters(id1, id2, d1);
}

void Cjt_Clusters::reiniciar_conjunto()
{
    clust_dist.clear();
    conj_clust.clear();
}

void Cjt_Clusters::actualiza_cjt_clusters(string &id1, string &id2, double &d1)
{
    map<string, Cluster>::iterator it = conj_clust.find(id1);
    map<string, Cluster>::iterator it2 = conj_clust.find(id2);
    Cluster cluster(it->second, it2->second, d1);
    conj_clust.insert(make_pair(cluster.consulta_id_arbol(), cluster));
    conj_clust.erase(id1);
    conj_clust.erase(id2);
    recalcular_distancias(id1, id2); 
}

void Cjt_Clusters::recalcular_distancias(string &id1, string &id2)
{
    string nuevo = id1+id2;
    map<string, double> aux;
    map<string, map<string, double> >::iterator principal = clust_dist.begin();
    while (principal->first < id2) {
        if ((principal->first) < id1) {
            map<string, double>::iterator sub1 = (principal->second).find(id1);
            map<string, double>::iterator sub2 = (principal->second).find(id2);
            double distancia = ((sub1->second)+(sub2->second))/2;
            (principal->second).erase(id1);
            (principal->second).erase(id2);
            (principal->second).insert(make_pair(nuevo, distancia));
        }
        else if ((principal->first) == id1) {
            map<string, double>::iterator sub1 = (principal->second).begin();
            while (sub1 != (principal->second).end()) {
                if (sub1->first < id2) {
                    map<string, map<string, double> >::iterator itbusca = clust_dist.find(sub1->first);
                    map<string, double>::iterator sub_busca = (itbusca->second).find(id2);
                    double distancia = (sub_busca->second + sub1->second)/2;
                    aux.insert(make_pair(sub1->first, distancia));
                }
                else if (sub1->first > id2) {
                    map<string, map<string, double> >::iterator itbusca = clust_dist.find(id2);
                    map<string, double>::iterator sub_busca = (itbusca->second).find(sub1->first);
                    double distancia = (sub1->second + sub_busca->second)/2;
                    aux.insert(make_pair(sub1->first, distancia));
                }
                ++sub1;
            }
        }
        else {
            (principal->second).erase(id1);
            (principal->second).erase(id2);
        }
        ++principal;
    }
    clust_dist.erase(id1);
    clust_dist.erase(id2);
    clust_dist.insert(make_pair(nuevo, aux));
} 

void Cjt_Clusters::imprime_cluster(const string &id1) 
{
    map<string, Cluster>::iterator it = conj_clust.find(id1);
    (it->second).aux_imprime_cluster(); 
    cout << endl;
}

void Cjt_Clusters::imprime_arbol_filogenetico()
{
    while (conj_clust.size() > 1){
        ejecuta_paso_wpgma();
    }
    map<string, Cluster>::iterator it = conj_clust.begin();
    (it->second).aux_imprime_cluster();
}

void Cjt_Clusters::imprime_clust_distancias() const
{
    for (map<string, map<string, double> >::const_iterator it1 = clust_dist.begin(); it1 != clust_dist.end(); ++it1) {
        cout << it1->first << ':';
        for (map<string, double>::const_iterator it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2) {
            cout << ' ' << it2->first << " (" << it2->second << ')';
        }
        cout << endl;
    }
}
