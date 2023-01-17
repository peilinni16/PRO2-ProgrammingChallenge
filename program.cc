/** @mainpage

  Evolución de Especies.

  Programa principal que simula la evolución de las especies según lo similares que sean. 
  El usuario tiene una lista de comandos disponibles que le permite seleccionar diversas operaciones. 
  El programa contiene múltiples módulos donde están implementadas esas funciones que llevan a cabo las operaciones requeridas. Cada uno contiene sus funciones que permiten modificar el conjunto siempre que el usuario lo requiera sea añadiendo o eliminando una o un conjunto de especies o calculando sus respectivas distancias.
*/

/** @file program.cc
    @brief Programa principal para el ejercicio <em>Evolución de las Especies</em>.

    Los datos leídos determinan la operación que quiere ejecutar el usuario. Como estos datos de operación 
    son del tipo string, el usuario seleccionará la operación introduciendo una string dentro de las disponibles.
    Dependiendo de la operación se necesitarán unos datos u otros.             
*/
#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif
using namespace std;

#include "Cjt_Especies.hh"

int main (){

  Cjt_Especies cjt_esp;
  Cjt_Clusters clusts;

  string op; //código de operación
  int nesp; //número de especies
  int k;  //tamaño de subcadenas de gen

  cin >> k;

  string ident, gen; //identidad y gen

  cin >> op;
  while (op != "fin"){

    if (op == "crea_especie"){
        cout << '#' << ' ' << op ;      
        cin >> ident >> gen ;
        cout << ' ' << ident << ' ' << gen << endl;

        if (not cjt_esp.existe_especie(ident)){
            cjt_esp.crea_especie(ident, gen, k);
        }
        else cout << "ERROR: La especie " << ident << " ya existe." << endl;
        cout << endl;
    }

    else if (op == "obtener_gen"){
        cout << '#' << ' ' << op ;
        cin >> ident;
        cout << ' ' << ident << endl;

        if (cjt_esp.existe_especie(ident)){
            string gen_aux;
            gen_aux = cjt_esp.obtener_gen(ident);
            cout << gen_aux << endl;
        } 
        else cout << "ERROR: La especie " << ident << " no existe." << endl;
        cout << endl;
    }

    else if (op == "distancia") {
      cout << '#' << ' ' << op << ' ';
      string ident2;
      cin >> ident >> ident2;
      cout << ident << ' ' << ident2 << endl;
      if (cjt_esp.existe_especie(ident) and cjt_esp.existe_especie(ident2)) {
          cout << cjt_esp.distancia(ident, ident2) << endl;
      }
      else if (cjt_esp.existe_especie(ident) and not cjt_esp.existe_especie(ident2)) {
          cout << "ERROR: La especie " << ident2 << " no existe." << endl;
      }
      else if (not cjt_esp.existe_especie(ident) and cjt_esp.existe_especie(ident2)) {
          cout << "ERROR: La especie " << ident << " no existe." << endl;
      }
      else {
          cout << "ERROR: La especie " << ident << " y la especie " << ident2 << " no existen." << endl;
      } 
      cout << endl;
    }

    else if (op == "elimina_especie"){
        cout << '#' << ' ' << op ;
        cin >> ident;
        cout << ' ' << ident << endl;

        if (cjt_esp.existe_especie(ident)){
            cjt_esp.elimina_especie(ident);
        }
        else cout << "ERROR: La especie " << ident << " no existe." << endl;
        cout << endl;
    }

    else if (op == "existe_especie"){
        cout << '#' << ' ' << op ;
        cin >> ident;
        cout << ' ' << ident << endl;
        if (cjt_esp.existe_especie(ident)) cout << "SI" << endl;
        else cout << "NO" << endl;
        cout << endl;
    }

    else if (op == "lee_cjt_especies"){
        cin >> nesp;
        cjt_esp.lee_cjt_especies(nesp, k);
        cout << '#' << ' ' << op << endl;
        cout << endl;
    }

    else if (op == "imprime_cjt_especies"){
        cout << '#' << ' ' << op << endl;
        cjt_esp.imprime_cjt_especies();
        cout << endl;
    }

    else if (op == "tabla_distancias"){
        cout << '#' << ' ' << op << endl;
        cjt_esp.tabla_distancias();
        cout << endl;
    }

    else if (op == "inicializa_clusters"){
      cout << '#' << ' ' << op << endl;
      cjt_esp.inicializa_clusters(clusts);
      clusts.imprime_clust_distancias();
      cout << endl;
    }

    else if (op == "ejecuta_paso_wpgma"){
      cout << '#' << ' ' << op << endl;
      if (clusts.es_posible()) {
        clusts.ejecuta_paso_wpgma();
        clusts.imprime_clust_distancias();
      }
      else cout << "ERROR: num_clusters <= 1" << endl;
      cout << endl;
    }

    else if (op == "imprime_cluster"){
      cin  >> ident;
      cout << '#' << ' ' << op << ' ' << ident << endl;
      if (clusts.existe_cluster(ident)){
        clusts.imprime_cluster(ident);
      }
      else cout << "ERROR: El cluster " << ident << " no existe." << endl;
      cout << endl;
    }

    else if (op == "imprime_arbol_filogenetico") {
      cout << '#' <<' ' << op << endl;
      cjt_esp.inicializa_clusters(clusts);
      if (not clusts.vacio()) {
        clusts.imprime_arbol_filogenetico();
        cout << endl;
      }
      else {
        cout << "ERROR: El conjunto de clusters es vacio." << endl;
      }
      cout << endl;
    }
    cin >> op;
  }
}
