/** @file Cluster.cc
    @brief Implementación de la clase Cluster
 */
#include "Cluster.hh"
using namespace std;

Cluster::Cluster(const string &id1)
{
    clust = BinTree<pair<string, double> >(make_pair(id1, 0.00));
}

Cluster::Cluster(Cluster &c1, Cluster &c2, double &d1)
{
    string padre = c1.consulta_id_arbol() +  c2.consulta_id_arbol();
    clust = BinTree<pair<string, double> >(make_pair(padre, d1/2), c1.clust, c2.clust);
}

void Cluster::aux_imprime_cluster(){
    imp_cluster(clust);
}

string Cluster::consulta_id_arbol() const {
    return clust.value().first;
}

void Cluster::imp_cluster(const BinTree<pair<string, double> >& c1) const {
    if (c1.left().empty()){
        cout << '[' << c1.value().first << ']';
    }
    else {
        cout <<'[' << '(' << c1.value().first << ',' << ' ' << c1.value().second << ')' << ' ';
        imp_cluster(c1.left());
        imp_cluster(c1.right());
        cout << ']' ;
    }
}