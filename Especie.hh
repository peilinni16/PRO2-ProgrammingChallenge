/** @file Especie.hh
    @brief Especificación de una classe Especie
*/
#ifndef _ESPECIE_HH_
#define _ESPECIE_HH_

#ifndef NO_DIAGRAM
#include <string>
#include <map>
#endif
using namespace std;

/*
 * Clase Especie
 */

/** @class Especie
    @brief Representa el conjunto de características y operaciones de
    las especies.

    Ofrece tres operaciones consultoras que devuelven el identificador, el gen y 
    la cadena kmer del parámetro implícito. 
    También contiene una operación modificadora que crea la cademna kmer.

    Dado que vamos a necesitar hacer operaciones con las especies, tenemos una constructora que forma 
    una Especie mediante uns identificador, un gen y un natural k para formar los kmeros.
*/

class Especie {
   
private:
  /* Una Especie se representa mediante un identificador, un gen y una cadena
    de kmer. */

  /** @brief Identificador de la especie. */
  string identificador;
  /** @brief Gen de la especie.*/
  string gen;
  /** @brief Cadena de kmer de la especie*/
  map<string,int> kmer;

public:

//Constructora
/** @brief Constructora con condición
    \pre id1.size() > 0  and  g1.size() > 0.
    \post Crea una especie con ident "id1" y gen "g1".
*/
Especie(const string &id1, const string &g1, int &k);


//Consultoras
/** @brief Consulta el identificador
    \pre <em>cierto</em>
    \post El resultado es el identificador del parámetro implícito.
*/
string consultar_ident() ;

/** @brief Consulta el gen
    \pre <em>cierto</em>
    \post El resultado es el gen del parámetro implícito.
*/
string consultar_gen();

/** @brief Consulta la cadena \em kmer del 
    \pre <em>cierto</em>
    \post El resultado son los kmeros del parámetro.
*/
map<string, int> consultar_kmer() const;

//Modficadora
/** @brief Calcula kmer
    \pre <em>cierto</em>
    \post El resultado es la cadena de k-meros
*/
void calc_kmer(const string &g1, int &k1);

};
#endif
