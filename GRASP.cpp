
#include "GRASP.h"
#include "Principal.h"

//CONSTRUCTORES Y DESTRUCTORES
//===========================
GRASP::GRASP(const std::string& rutaFichero, float _alpha): Metaheuristica(rutaFichero) {
    bl = new BL(flujo, distancias, tam);
    alpha = _alpha;
}

GRASP::~GRASP() {
    delete bl;
}

//METODOS PROTECTED
//=================
void GRASP::solucion_grasp(unsigned* p) {
    
}

//METODOS PUBLICOS
//================
unsigned long GRASP::ejecutar() {   
    unsigned* p = new unsigned[tam];
    unsigned long costeP;
    unsigned long mejorCoste = 9999999999;
    unsigned evaluacion = 0;
    
    while(evaluacion < 25) {
        solucion_grasp(p);
        costeP = bl->ejecutar(p);
        
        if(costeP < mejorCoste) {
            for(unsigned i = 0; i < tam; i++) {
                solucion[i] = p[i];
            }
            
            mejorCoste = costeP;
        }
        
        evaluacion++;
    }
    
    return mejorCoste;
}
