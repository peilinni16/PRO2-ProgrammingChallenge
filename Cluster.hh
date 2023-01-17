/** @file Cluster.hh
    @brief Especificación de Cluster
*/
#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#ifndef NO_DIAGRAM 
#include <iostream>
#include "BinTree.hh"
#include <string>
#endif 

/*
 * Clase Cluster
 */

/** @class Cluster
    @brief Representa el conjunto de características 
    y operaciones de los clústers.

    Contiene operaciones consultoras que devuelven el identificador y la estructura del clúster;
    también una operación de escritura que imprime un clúster.

    Dado que vamos a necesitar inicializar los clusters con elementos directos del Cjt_Especies,
    disponemos de una constructora inicial. Aparte, ofrece otra constructora que fusiona dos clusters,
    tomando por valor una nueva distancia a partir de la dada.


*/

class Cluster {

private:
    /* Un Cluster se representa mediante una estructura arbolescente donde cada uno de sus componentes contiene 
    su propio identificador y su distancia respecto al otro miembro mas cercano. */

    /** @brief Estructura de un cluster. */
    BinTree<pair<string, double> > clust;
    
    /** @brief Operación de escritura de los elementos de un cluster. */
    void imp_cluster(const BinTree<pair<string, double> >& c1) const;

public:

//Constructora
/** @brief Constructora por condición
    \pre <em>cierto</em>
    \post El resultado en un cluster con id "id1" y distancia "0.00".
*/
Cluster(const string &id1);

/** @brief Constructora por condición
    \pre <em>cierto</em>
    \post El resultado es un cluster con una nueva id y la media de las dos distancias como distancia propia.
*/
Cluster(Cluster &c1, Cluster &c2, double &d1);

//Consultora
/** @brief Consulta la id del cluster
    \pre <em>cierto</em>
    \post Retorna el identificador del cluster.
*/
string consulta_id_arbol() const;

//Operación de escritura

/** @brief Consulta cluster
    \pre El parámetro implícito está inicializado.
    \post Devuelve la estructura del clúster.
 */
void aux_imprime_cluster();

};
#endif