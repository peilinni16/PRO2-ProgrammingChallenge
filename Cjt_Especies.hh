/** @file Cjt_Especies.hh
    @brief Especificación Cjt_Especies
*/
#ifndef _CJT_ESPECIES_HH_
#define _CJT_ESPECIES_HH_

#include "Especie.hh"
#include "Cjt_Clusters.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <map>
#endif
using namespace std;

/*
 * Clase Cjt_Especies
 */

/** @class Cjt_Especies
    @brief Representa la agrupación de las especies y una serie de operaciones para
    formar este conjunto.

    Contiene diversas operaciones modificadoras para añadir especie y eliminar del conjunto de especies y diversas 
    para añadir una o un conjunto de especies y eliminar de la tabla de distancias. También tiene operaciones consultoras
    para ver la existencia de una especie, consultar una distancia e inicializa clusters consultando todos los elementos 
    del conjunto de especies y de la tabla.

    Dado que neceitaremos rellenar y modificar el parámetro implícito constantemente, disponemos tambien de una creadora
    por defecto para aplicar estas operaciones.
*/
class Cjt_Especies {

private:
/* Un Cjt_Especies lo representan un conjunto de especies con sus respectivos identificadores y una tabla de distancias
  relacionada con el conjunto. */

  /** @brief Tabla de distancias del conjunto de especies. */
  map<string, map<string, double> > map_dist;
  /** @brief Estructura del conjunto de especies. */
  map<string,Especie> conjunto;

public:

//Constructora
/** @brief Creadora por defecto
    \pre <em>cierto</em>
    \post El parámetro implícito no está inicializado.
*/
  Cjt_Especies();

//Modificadores
/** @brief Modifica conjunto de especies eliminando
    \pre La "id1" existe en el parámetro implícito.
    \post El parámetro implícito ya no tiene la especie con id1.
*/
  void elimina_especie(const string &id1);

/** @brief Modifica conjunto de especies añadiendo
    \pre La "id1" no existe en el parámetro implícito.
    \post El parámetro implícito contiene la especie con "id1".
*/
  void crea_especie(const string &id1, const string &g1, int &k1);

/** @brief Calcula valores para la taba de distancias
    \pre "e1" y "e2" están inicializadas.
    \post Devuelve la distancia entra las dos especies.
*/
  double calcular_dist(Especie &e1, Especie &e2);

  /** @brief Modifica tabla de distancias añadiendo
      \pre 'e' no existe en la tabla de distancias.
      \post La tabla de distancias tiene 'e' y sus respectivas distancias.
  */
  void afegir_dist(Especie &e);

  /** @brief Modifica tabla de distancias añadiendo
      \pre La tabla de distancias está vacía.
      \post La tabla de distacias está inicializado con los identificadores del conjunto de especies y sus distancias.
   */
  void afegir_cjt_dist();

  /** @brief Modifica tabla distancias eliminando
      \pre "id1" existe en la tabla de distancias.
      \post El parámetro implícito ya no contiene "id1" ni ninguna distancia relacionada.
  */
  void elimina_dist(const string &id1);


//Consultora
/** @brief Consulta especie
    \pre El parámetro implícito está inicializado
    \post \em cierto: "id1" existe en el conjunto de especies.
          \em falso: "id1" no existe en el conjunto.
*/
  bool existe_especie(const string &id1) const;

/** @brief Consulta distancias 
    \pre "id1" y "id2" existen en el parámetro implícito.
    \post Imprime por el canal de salida estándar la distancia entre "id1" y "id2".
*/
  double distancia(const string &id1, const string &id2);

/** @brief Consulta el conjunto de especies y la tabla de distancias
    \pre <em>cierto</em>
    \post El parámetro explícito queda inicializado y toma por valor los elementos del parámetro implícito.
*/
  void inicializa_clusters(Cjt_Clusters &c);


//Lectura i escriptura
/** @brief Lectura de un conjunto de especies
    \pre Lee en el canal estándar de entrada un entero n>=0 y una secuéncia de n espécies (ident, gen).
         Todas las especies de la entrada tienen identificadores distintos.
    \post Inicializa el parámetro implícito con los atributos adquiridos pos el canal de entrada.
*/
  void lee_cjt_especies(int num_especies, int &k1);

/** @brief Escritura de gen
    \pre  "id1" existe dentro del conjunto de especies.
    \post Imprime en el canal estándar de salida el gen relacionado a "id1".
*/
  string obtener_gen(string &id1);

  /** @brief Escritura del conjunto de especies
      \pre <em>cierto</em>
      \post Imprime en el canal estándar de salida el conjunto de espécies
  */
  void imprime_cjt_especies();

  /** @brief Escritura de la tabla de distancias
      \pre <em>cierto</em>
      \post Imprime en el canal estándar la tabla de distancias del conjunto de espacies.
  */
  void tabla_distancias()const ;

};
#endif
