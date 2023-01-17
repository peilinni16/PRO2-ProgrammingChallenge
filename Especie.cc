/** @file Especie.cc
    @brief Implementación de la clase Especie
 */

#include "Especie.hh"
using namespace std;

Especie::Especie(const string &id1, const string &g1, int &k1) 
{
    identificador = id1;
    gen = g1;
    calc_kmer(g1, k1);
}

void Especie::calc_kmer(const string &g1, int &k) 
{
  for (int i = 0; i < (g1.size()-k+1); ++i) {
    string aux = g1.substr(i, k);
  
    pair<map<string, int>::iterator, bool> repe;
    repe = kmer.insert(make_pair(aux, 1));
    if (not repe.second) ++(repe.first->second);    
    }
}

string Especie::consultar_ident() 
{
    return identificador;
}

string Especie::consultar_gen() 
{
    return gen;
}

map<string, int> Especie::consultar_kmer() const
{
    return kmer;
}

