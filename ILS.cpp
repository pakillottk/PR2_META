
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
    unsigned intercambios = rand() % sublista/2;
    unsigned* afectados = new unsigned[sublista];
    
    unsigned r, s;
    bool* asignados = new bool[sublista];
    
    if(Principal::debug) {
        cout << "Mutando desde pos: " << init << endl;
        cout << "Intercambios: " << intercambios << endl;
    }
    
    for(unsigned i = 0; i < sublista; i++) {
        afectados[i] = (init+i)%tam;       
        asignados[i] = false;
    }
    
    if(Principal::debug)
        cout << "Intercambiando..." << endl;
    
    for(unsigned i = 0; i < intercambios; i++) {
        if(Principal::debug)
            cout << "Intercambio " << i+1 << endl;
        
        r = rand() % sublista;
        do{
            s = rand() % sublista;
        } while(r == s || (asignados[r] && asignados[s]));
        
        intercambiar(p, afectados[r], afectados[s]);
        asignados[r] = true;
        asignados[s] = true;
    }
    
    delete [] afectados;
    
    return calculaCoste(p);
}

unsigned long ILS::ejecutar() {
    unsigned* s = new unsigned[tam];
    unsigned* s2 = new unsigned[tam];
    unsigned* s3 = new unsigned[tam];
    
    unsigned long costeS;
    unsigned long costeS2;
    unsigned long costeS3;
    
    unsigned evaluaciones = 0;
    
    if(Principal::debug)
     cout << "Generando solucion..." << endl;
    
    generarSolucion(solucion);
    
    if(Principal::debug)
        cout << "Aplicando bl..." << endl;   
    
    costeActual = bl->ejecutar(solucion);
    
    if(Principal::debug)
        cout << "Coste actual: " << costeActual << endl;
    
    for(unsigned i = 0; i < tam; i++)
        s[i] = solucion[i];
    
    costeS = costeActual;
    
    if(Principal::debug)
     cout << "Iniciando bucle..." << endl;
    
    while(evaluaciones < 24) {     
        if(Principal::debug)
            cout << "EVALUACION: " << evaluaciones << endl;
        
        for(unsigned i = 0; i < tam; i++)
            s2[i] = s[i];
        
        if(Principal::debug)
         cout << "Mutando solucion..." << endl;
        
        costeS2 = mutar(s2);
        
        if(Principal::debug)
            cout << "Coste, sol. mutada: " << costeS2 << endl;
        
        for(unsigned i = 0; i < tam; i++)
            s3[i] = s2[i];
        
        if(Principal::debug)
            cout << "Aplicando busqueda local..." << endl;
        costeS3 = bl->ejecutar(s3);
        
        if(Principal::debug)
            cout << "Coste optimizado: " << costeS3 << endl; 
        
        if(costeS3 < costeS) {
            for(unsigned i = 0; i < tam; i++)
                s[i] = s3[i];
            
            costeS = costeS3;
        }
        
        if(costeS < calculaCoste()) {
            for(unsigned i = 0; i < tam; i++)
                solucion[i] = s[i];
            
            costeActual = costeS;
        }
        
        evaluaciones++;
    }
    
    delete [] s;
    delete [] s2;
    delete [] s3;
    
    return costeActual;
}