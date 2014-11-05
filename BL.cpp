
#include "BL.h"
#include "Principal.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================

BL::BL(unsigned** f, unsigned** d, unsigned t) { 
    tam = t;
    flujo = f;
    distancias = d;
    
    dlb = new bool[tam];   
}

BL::~BL(){
    solucion = 0;
    delete [] dlb;
}

//MÉTODOS PROTECTED
//=================

//Implementación del algoritmo de búsqueda local
unsigned long BL::ejecutar(unsigned* p) {
   if(!p) {
        if(Principal::debug)
            std::cout << "Generando solucion..." << std::endl;

        //Comenzamos generando una solución aleatoria...
        solucion = new unsigned[tam];
       generarSolucion();
    } else {
        //Asignamos la solucion actual a la permutación.
        solucion = p;
    }
   
   for(unsigned i = 0; i < tam; i++)
        dlb[i] = false;

   if(Principal::debug) {
        std::cout << "SOLUCION INICIAL";
        for(unsigned i = 0; i < tam; i++) {
            if(!i%tam)
                std::cout << std::endl;
            std::cout << solucion[i] << " ";
        }

        std::cout << std::endl;
        std::cout << "Coste inicial: " << calculaCoste()
                  << std::endl;
    }

   if(Principal::debug)
    std::cout << "Iniciando busqueda local..." << std::endl;

    //Procedemos a iterar por el espacio de búsqueda
    unsigned evaluaciones = 0; //Contador de evaluaciones
    bool mejora; //Flag para indicar si hemos encontrado mejora en el entorno
    bool finBusqueda = false; //Flag que indicará si la búsqueda debe terminar, por
                              //no encontrar mejoría en todo el entorno

    while(evaluaciones < 10000) {
        //Generamos y evaluamos los vecinos
        for(unsigned i = 0; i < tam; i++) {
            if(!dlb[i]) { //Si la posición está marcada en dlb, ignoramos
                mejora = false;

                for(unsigned j = 0; j < tam; j++) {
                    if(i==j)
                        continue;

                    if(mejoraCambio(solucion, i, j)) { //Si el vecino mejora, actualizamos
                        if(Principal::debug)
                            std::cout << "Intercambio " << i << " a " << j
                                     << " mejora, actualizando..." << std::endl;

                        dlb[i] = false;
                        dlb[j] = false;
                        mejora = true;

                        intercambiar(solucion, i,j);
                        break;
                    }
                }

                if(!mejora) { //No se encontró mejora para la posición i, actualizamos dlb
                    if(Principal::debug)
                        std::cout << i << " no mejora, actualizando dlb..."
                                  << std::endl;
                    dlb[i] = true;

                    if(i == tam-1) { //Terminamos de explorar y no hay mejoras, fin de la búsqueda
                        if(Principal::debug)
                            std::cout << "Sin mejora en el entorno, fin de la busqueda..."
                                      << std::endl;

                        finBusqueda = true;
                    }
                } else {
                    break;
                }
            }
        }    
        
        evaluaciones++;
        
        if(finBusqueda)
            break;
    }

    unsigned long costeFinal = calculaCoste();
    
    if(Principal::debug) {
        std::cout << "SOLUCION";
        for(unsigned i = 0; i < tam; i++) {
            if(!i%tam)
                std::cout << std::endl;
            std::cout << solucion[i] << " ";
        }

        std::cout << std::endl;
        std::cout << "Coste: " << costeFinal
                  << std::endl;
    }

    if(p)
        solucion = 0;
    
    return costeFinal;
}


