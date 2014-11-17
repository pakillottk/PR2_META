
#include "ILS.h"
#include "Principal.h"

ILS::ILS(const string& rutaFichero): Metaheuristica(rutaFichero) {
    sublista = tam/4;
    bl = new BL(flujo, distancias, tam);
}

ILS::~ILS() {   
    delete bl;   
}

unsigned long ILS::mutar(unsigned* p) {
    unsigned init = rand() % tam;  
    unsigned intercambios = (rand() % tam/3) + (2*tam)/3;
    unsigned* afectados = new unsigned[sublista];
    
    unsigned r, s;
    
    if(Principal::debug) {
        cout << "Mutando desde pos: " << init << endl;
        cout << "Intercambios: " << intercambios << endl;
    }
    
    for(unsigned i = 0; i < sublista; i++) {
        afectados[i] = (init+i)%tam;      
    }
    
    if(Principal::debug)
        cout << "Intercambiando..." << endl;
    
    for(unsigned i = 0; i < intercambios; i++) {
        if(Principal::debug)
            cout << "Intercambio " << i+1 << endl;
        
        r = rand() % sublista;
        do{
            s = rand() % sublista;      
        } while(r == s);
        
        intercambiar(p, afectados[r], afectados[s]);
    }
    
    delete [] afectados;
    
    return calculaCoste(p);
}

unsigned long ILS::ejecutar() {
    unsigned* s2 = new unsigned[tam];
    unsigned long costeS2;
    unsigned tamEval = tam*0.7;
    
    if(tamEval <= 25) tamEval = 300-10*tam;
    
    unsigned evaluaciones = 0;
    
    if(Principal::debug)
     cout << "Generando solucion..." << endl;
    
    generarSolucion(solucion);
    
    if(Principal::debug)
        cout << "Aplicando bl..." << endl;   
    
    costeActual = bl->ejecutar(solucion);
    
    if(Principal::debug)
        cout << "Coste actual: " << costeActual << endl;
    
    if(Principal::debug)
     cout << "Iniciando bucle..." << endl;
    
    while(evaluaciones < tamEval) {     
        if(Principal::debug)
            cout << "EVALUACION: " << evaluaciones << endl;
        
        for(unsigned i = 0; i < tam; i++)
            s2[i] = solucion[i];
        
        if(Principal::debug)
         cout << "Mutando solucion..." << endl;
        
        mutar(s2);
        
        if(Principal::debug)
            cout << "Aplicando busqueda local..." << endl;
        costeS2 = bl->ejecutar(s2);
        
        if(Principal::debug)
            cout << "Coste optimizado: " << costeS2 << endl; 
        
        if(costeS2 < costeActual) {
            for(unsigned i = 0; i < tam; i++)
                solucion[i] = s2[i];
            
            costeActual = costeS2;
        }
        
        evaluaciones++;
    }   

    delete [] s2;
    
    return costeActual;
}