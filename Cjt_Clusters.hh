/** @file Cjt_Clusters.hh
    @brief Especificación Cjt_Clusters
*/
#ifndef _CJT_CLUSTERS_HH_
#define _CJT_ESPECIES_HH_

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <string>
#include "BinTree.hh"
#endif

/*
 * Clase Cjt_Clusters
 */

/** @class Cjt_Clusters
    @brief Representa el ciclo evolutivo de los clusters según la diferencia de distancias entre estos.

    Contiene: operaciones consultoras que devuelven la distancia mínima y sus respectivos identificadores, 
    el tamaño del conj_clust, la existencia de un cluster dentro del conjunto y si el conjunto es vacío.
    También tiene modificadoras que añaden y eliminan los diferentes clusters ya evolucionados y fusionados del \em conj_clust,
    recalcula las nuevas distancias del \em clust_dist y borrando aquellas de clusters eliminados y 
    una para reiniciar el parámetro implícito.
    Y, por último, operaciones de escritura que imprimen un clúster dado un identificador, el árbol filogenético final y 
    la tabla de distancias \em clust_dist.
 */

class Cjt_Clusters {

private: 
    /* Un Cjt_Clusters se representa mediante su conjunto de clusters y
    una tabla que registra las distancias entre los elementos del conjunto de clusters.*/

    /** @brief Conjunto de clusters formado por un identificador y un Cluster.*/
    map<string, Cluster> conj_clust;
    /** @brief Tabla de distancias del conjunto.*/
    map<string, map<string, double > > clust_dist;

public:

//Constructora
/** @brief Constructora por defecto
    \pre <em>cierto</em>
    \post El parámetro implícito no está inicializado : conj_clust.size() = 0 y clust_dist.size() = 0.
 */
Cjt_Clusters();

//Consultoras
/** @brief Consulta la distancia mínima
    \pre El conjunto de distancias no es vacío.
    \post Retorna la distancia mínima del conjunto.
*/
void busca_minimo(string &id1, string &id2, double &d1);

/** @brief Consulta tamaño de conjunto de clusters
    \pre <em>cierto</em>
    \post \em cierto: conj_clust.size() > 1.
          \em falso: conj_clust.size() <= 1.
*/
bool es_posible() const;

/** @brief Consulta clúster
    \pre El parámetro implícito está inicializado.
    \post \em cierto: existe clúster con "id1" en el parámetro implícito.
          \em falso: no existe clúster con "id1".
*/
bool existe_cluster(const string &id1) const;

/** @brief Consulta tamaño tabla de distancias
    \pre <em>cierto</em>
    \post \em cierto: la tabla de distancias no está inicializada.
          \em falso: la tabla de distancias está inicializada.
*/
bool vacio() const;


//Modificadoras
/** @brief Modifica conjunto de clusters
    \pre El clúster "c1" no existe en el conjunto de clusters.
    \post El conjunto de clusters ya tiene un clúster "c1".
 */
void aniadir_cluster(const Cluster &c1);

/** @brief Modifica tabla de distancias
    \pre La fila de distancias "d1" no existe en la tabla de distancias.
    \post La tabla de distancias tiene la fila de distancias "d1".
*/
void aniadir_distancia(const string &id1, const string &id2, const double &d1);

/** @brief Modifica tabla de distancias
    \pre L
    \post La tabla de distancias tiene una fila más.
 */
void aniadir(const string &id1);
/** @brief Modifica el parámetro implícito
    \pre El parámetro implícito tiene más de un elemento.
    \post Los elementos del parámetro implícito han sido modificados.
*/
void ejecuta_paso_wpgma();

/** @brief Modifica el parámetro implícito
    \pre <em>cierto</em>
    \post El parámetro implícito queda vacío, no inicializado.
*/
void reiniciar_conjunto();

/** @brief Modifica los elementos del parámetro implícito
    \pre "id1" y "id2" ya existen dentro del parámetro implícito.
    \post En el conjunto de clusters se ha insertado un nuevo cluster y se eliminan los que lo han formado.
          En tabla de distancias se ha insertado una nueva fila con el cluster creado y se han eliminado todas las distancias respecto el par de clusters que lo forman.
*/
void actualiza_cjt_clusters(string &id1, string &id2, double &d1);

/** @brief Modifica tabla de distancias
    \pre "id1" y "id2" existen dentro del parámetro implícito.
    \post En la tabla de distancias se ha insertado una nueva fila con el cluster creado y sus distancias respecto a los demás clusters y se han eliminado todas las distancias respecto el par de clusters que forman al nuevo cluster.
*/
void recalcular_distancias(string &id1, string &id2);


//Operaciones de Escritura
/** @brief Escribe clúster
    \pre "id1" existe en el parámetro implícito.
    \post Imprime por el canal de salida estándar el clúster con ID "id1" y, en el caso de que tenga, los ID's de los clusters lo forman.
 */
void imprime_cluster(const string &id1);

/** @brief Escribe árbol filogenético
    \pre <em>cierto</em>
    \post Imprime por el canal de salida estándar el clúster formado por todos los clusters del conjunto inicial, imprimiendo a su vez estos clusters.
 */
void imprime_arbol_filogenetico();

/** @brief Escribe tabla de distancias
    \pre El parámetro implícito está inicializado.
    \post Imprime por el canal de salida estándar el contenido de la tabla de distancias.
 */
void imprime_clust_distancias() const;


};
#endif


