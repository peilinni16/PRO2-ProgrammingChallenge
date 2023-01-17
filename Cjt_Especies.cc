/** @file Cjt_Especies.cc
    @brief Implementación de la clase Cjt_Especies
*/

#include "Cjt_Especies.hh"
using namespace std;

Cjt_Especies::Cjt_Especies() {}


void Cjt_Especies::elimina_especie(const string &id1)
{
    elimina_dist(id1);
    conjunto.erase(id1);
}

void Cjt_Especies::crea_especie(const string &id1, const string &g1, int &k1)
{   
    Especie e(id1, g1, k1);
    afegir_dist(e);
    conjunto.insert(make_pair(id1, e));
}

double Cjt_Especies::calcular_dist(Especie &e1,Especie &e2)
{
    map<string, int> kmer1 = e1.consultar_kmer();
    map<string, int> kmer2 = e2.consultar_kmer();

    map<string, int>::iterator it1 = kmer1.begin();
    map<string, int>::iterator it2 = kmer2.begin();

    double cont_inter = 0;
    double cont_union = 0;

    while (it1 != kmer1.end() and it2 != kmer2.end()) {
        if ((it1->first) < (it2->first)) {
            cont_union += it1->second; 
            ++it1;
        }
        else if ((it1->first) == (it2->first)) {
            cont_inter += min(it1->second, it2->second);
            cont_union += max(it1->second, it2->second); 
            ++it1;
            ++it2;
        }
        else if ((it1->first) > (it2->first)) {
            cont_union += it2->second;
            ++it2;
        }
    }
    while (it1 != kmer1.end()) {
        cont_union += it1->second;
        ++it1;
    }
    while (it2 != kmer2.end()) {
        cont_union += it2->second;
        ++it2;
    }
    double dist = ((1-(cont_inter/cont_union))*100);

    return dist;
}

void Cjt_Especies::afegir_dist(Especie &e)
{
    map<string, Especie>::iterator it1 = conjunto.begin();
    map_dist.insert(make_pair(e.consultar_ident(), map<string, double>()));    

    while (it1 != conjunto.end()) {
        if ((it1->first) < e.consultar_ident()) {
            double dist = calcular_dist((it1->second), e);
            map_dist[it1->first].insert(make_pair(e.consultar_ident(), dist));
        }

        else if ((it1->first) > e.consultar_ident()) {
            double dist2 = calcular_dist((it1->second), e);
            map_dist[e.consultar_ident()].insert(make_pair((it1->first), dist2));
        }
        ++it1;
    }
}

void Cjt_Especies::afegir_cjt_dist() 
{
    map<string, Especie>::iterator it = conjunto.begin();

    while (it != conjunto.end()) {
        
        map<string, map<string, double> >::iterator it2 = (map_dist.insert(make_pair(it->first, map<string, double>()))).first; //añado el id en el mapa de distancias y un map vacio
        map<string, Especie>::iterator aux = it; //declaro auxiliar para que se mueva por todo el conjunto
        ++aux;
        while (aux != conjunto.end()) {
            double dist = calcular_dist((it->second), (aux->second));
            (it2->second).insert(make_pair(aux->first, dist));
            ++aux;
        }
        ++it;
    }
}


void Cjt_Especies::elimina_dist(const string &id1)
{
    map_dist.erase(id1);
    map<string, map<string, double> >:: iterator it = map_dist.begin();

    while (it != map_dist.end()) {
        (it->second).erase(id1);
        ++it;
    }
}

bool Cjt_Especies::existe_especie(const string &id1) const
{
    map<string, Especie>::const_iterator it = conjunto.find(id1);
    if (it != conjunto.end()) return true;
    else return false;
}


double Cjt_Especies::distancia(const string &id1, const string &id2)
{
    double dist = 0.00;
    if (id1 < id2) {
        map<string, map<string, double> >::const_iterator it1 = map_dist.find(id1);
        map<string, double>::const_iterator it2 =  (it1->second).find(id2);
        dist = it2->second;
    }
    else if (id1 > id2) {
        map<string, map<string, double> >::const_iterator it1 = map_dist.find(id2);
        map<string, double>::const_iterator it2 =  (it1->second).find(id1);
        dist = it2->second;
    }
    return dist;
}  

void Cjt_Especies::lee_cjt_especies(int nesp, int &k1)
{
    map_dist.clear();
    conjunto.clear();
    string id1, g1;
    for (int i = 0; i < nesp; ++i) {
        cin >> id1 >> g1;
        Especie e(id1, g1, k1);
        conjunto.insert(make_pair(id1, e));
    }
    afegir_cjt_dist();
}

string Cjt_Especies::obtener_gen(string &id1)
{
    map<string, Especie>::iterator it = conjunto.find(id1);
    return ((it->second).consultar_gen()) ;
}

void Cjt_Especies::imprime_cjt_especies()
{
    for (map<string, Especie>::iterator it = conjunto.begin(); it != conjunto.end(); ++it) {
        cout << (it->second).consultar_ident() << ' ' << (it->second).consultar_gen() << endl;
    }
}

void Cjt_Especies::tabla_distancias() const
{
    for (map<string, map<string, double> >::const_iterator it1 = map_dist.begin(); it1 != map_dist.end(); ++it1) {
        cout << it1->first << ':';
        for (map<string, double>::const_iterator it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2) {
            cout << ' ' << it2->first << " (" << it2->second << ')';
        }
        cout << endl;
    }
    
}

void Cjt_Especies::inicializa_clusters(Cjt_Clusters &cc)
{
    cc.reiniciar_conjunto();
    for(map<string, Especie>::const_iterator it=conjunto.begin(); it != conjunto.end(); ++it) {
        Cluster cluster(it->first);
        cc.aniadir_cluster(cluster);
    }
    for(map<string, map<string,double> >::iterator it = map_dist.begin(); it != map_dist.end(); ++it) {
        for (map<string, double>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2) {
            cc.aniadir_distancia(it->first, it2->first, it2->second);        
        }
    }
    if (not conjunto.empty()) {
        map<string, Especie>::const_iterator it = --conjunto.end();
        cc.aniadir(it->first);
    }
}
