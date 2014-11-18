
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
unsigned long GRASP::calcularUmbral(unsigned long max, unsigned long min, bool mejor_max) {
    long int umbral;
    
    if(!mejor_max)
        umbral = min + alpha * (max - min);
    else 
        umbral = max - alpha * (max - min);
    
    return umbral;    
}

unsigned long GRASP::calculaPotencialUnidad(unsigned i) {
    unsigned long potencial = 0;
    for(unsigned j = 0; j < tam; j++) {
        potencial += flujo[i][j] + flujo[j][i];
    }
    
    return potencial;
}

unsigned long GRASP::calculaPotencialLocalizacion(unsigned i) {
    unsigned long potencial = 0;
    for(unsigned j = 0; j < tam; j++) {
        potencial += distancias[i][j] + distancias[j][i];
    }
    
    return potencial;
}

void GRASP::solucion_grasp(unsigned* p) {
    bool* asignados_u = new bool[tam];
    bool* asignados_d = new bool[tam];
    
    //ETAPA 1
    unsigned long* pu = new unsigned long[tam];
    unsigned long* pd = new unsigned long[tam];   
    
    unsigned long min_pu = 999999999;
    unsigned long min_pd = 999999999;
    unsigned long max_pu = 0;
    unsigned long max_pd = 0;
    
    unsigned long umbral_u;
    unsigned long umbral_d;
    
    vector<unsigned> asignados;
    vector<unsigned> lrc_u;
    vector<unsigned> lrc_d;
    
    //CALCULO DE POTENCIALES Y OBTENCION DE MINIMOS Y MAXIMOS
    if(Principal::debug)
        cout << "Calculando potenciales..." << endl;
    for(unsigned i = 0; i < tam; i++) {
        asignados_u[i] = false; asignados_d[i] = false;
        
        pu[i] = calculaPotencialUnidad(i);
        
        if(pu[i] < min_pu) {
            min_pu = pu[i];            
        }
        
        if(pu[i] > max_pu) {
            max_pu = pu[i];
        }
        
        pd[i] = calculaPotencialLocalizacion(i);
        
        if(pd[i] < min_pd) {
            min_pd = pd[i];            
        }
        
        if(pd[i] > max_pd) {
            max_pd = pd[i];
        }
    }
    
     if(Principal::debug) {
        cout << "Minimos:" << endl;
        cout << "u: " << min_pu << " d: " << min_pd << endl;

        cout << "Maximos:" << endl;
        cout << "u: " << max_pu << " d: " << max_pd << endl;
     }
    
    //UMBRALES
    if(Principal::debug)
        cout << "Calculo de umbrales..." << endl;
    umbral_u = calcularUmbral(max_pu, min_pu, true);
    umbral_d = calcularUmbral(max_pd, min_pd);    
    
     if(Principal::debug) {
        cout << "Umbrales:" << endl;
        cout << "u: " << umbral_u << " d: " << umbral_d << endl;
     }
    
    //CONSTRUCCION DE LAS LRCs
    if(Principal::debug)
        cout << "Construyendo LRCs..." << endl;
    
    for(unsigned i = 0; i < tam; i++) {
        if(pu[i] >= umbral_u) {
            lrc_u.push_back(i);
        }
        
        if(pd[i] >= umbral_d) {
            lrc_d.push_back(i);
        }
    }
    
    if(Principal::debug)
       cout << "LRC u: " << lrc_u.size() << " LRC d: " << lrc_d.size() << endl;
    
    unsigned u1, u2;
    unsigned l1, l2;
    
    
    u1 = rand() % lrc_u.size();
    do {
     u2 = rand() % lrc_u.size();
    } while(u1 == u2);

    l1 = rand() % lrc_d.size();  
    if(lrc_d.size() > 1) {
       do {
        l2 = rand() % lrc_d.size();
       } while(l1 == l2);
    }
    
    if(Principal::debug) {
        cout << "Asignando..." << endl;
        cout << lrc_u[u1] << " con " << lrc_d[l1] << endl;
        
        if(lrc_d.size() > 1)
            cout << lrc_u[u2] << " con " << lrc_d[l2] << endl;   
    }
    
    p[lrc_u[u1]] = lrc_d[l1];
    asignados.push_back(lrc_u[u1]);
    asignados_u[lrc_u[u1]] = true;
    asignados_d[lrc_d[l1]] = true;

    if(lrc_d.size() > 1) {
        p[lrc_u[u2]] = lrc_d[l2];
        asignados.push_back(lrc_u[u2]);
        asignados_u[lrc_u[u2]] = true;
        asignados_d[lrc_d[l2]] = true;
    }
    
    if(Principal::debug)
        cout << "Etapa 1, completada" << endl;
    
    //ETAPA 2    
    unsigned long minCoste;
    unsigned long maxCoste;   
    unsigned long umbral;
    unsigned long* costes = new unsigned long[tam];
    vector<unsigned> lrc;
    unsigned seleccion;
    
    if(Principal::debug)
        cout << "Inicio etapa 2" << endl;
    
    for(unsigned i = 0; i < tam; i++) {      
        if(asignados_u[i]) continue; 
        
        minCoste = 999999999;
        maxCoste = 0;
        
        //COSTES
        for(unsigned j = 0; j < tam; j++) {                         
            if(asignados_d[j]) continue;         
            
            costes[j] = obtenerCoste(p, asignados, i, j);
            
            if(Principal::debug)
                cout << "Coste: " << costes[j] << endl;
            
            if(costes[j] < minCoste) minCoste = costes[j];
            if(costes[j] > maxCoste) maxCoste = costes[j];
        }
        
        if(Principal::debug)
            cout << "Min coste: " << minCoste << " Max coste: " << maxCoste << endl;
        
        //UMBRAL
        umbral = calcularUmbral(maxCoste, minCoste);        
        if(Principal::debug)
            cout << "Umbral: " << umbral << endl;
        
        //LRC
        for(unsigned j = 0; j < tam; j++) {
            if(asignados_d[j]) continue;
            
            if(costes[j] >= umbral) {
                lrc.push_back(j);
            }
        }
        
        if(Principal::debug)
         cout << "LRC: " << lrc.size() << endl;
        
        //SELECCION
        seleccion = rand() % lrc.size();
        if(Principal::debug)
         cout << "Asigna a " << i << " la loc: " << lrc[seleccion] << endl;
        
        p[i] = lrc[seleccion];
        asignados_u[i] = true;
        asignados.push_back(i);
        asignados_d[lrc[seleccion]] = true;
        
        lrc.clear();
    }
    
    delete [] costes;
    
    delete [] asignados_u;
    delete [] asignados_d;
    
    delete [] pu;
    delete [] pd; 
    
    if(Principal::debug)
        cout << "Solucion GRASP obtenida" << endl;
}

unsigned long GRASP::obtenerCoste(unsigned* p, vector<unsigned> asignados, unsigned i, unsigned j) {
    unsigned long coste = 0;
    
    for(unsigned k = 0; k < asignados.size(); k++) {       
        coste += (flujo[i][asignados[k]] * distancias[j][p[asignados[k]]]);
    }
    
    return coste;
}

//METODOS PUBLICOS
//================
unsigned long GRASP::ejecutar() {    
    unsigned* p = new unsigned[tam];
    unsigned long costeP;
    unsigned long mejorCoste = 999999999;
    unsigned evaluacion = 0;    
    unsigned sinMejora = 0;
    unsigned tamEval;      
    
    if(tamEval <= 25) tamEval = 300-10*tam;
    else tamEval = tam*0.7; 
    
    while(evaluacion < tamEval) {      
        solucion_grasp(p);        
        costeP = bl->ejecutar(p);
        
        if(costeP < mejorCoste) {
            for(unsigned i = 0; i < tam; i++) {
                solucion[i] = p[i];
            }
            
            mejorCoste = costeP;
            sinMejora = 0;
            alpha = 0.2;
        } else {
            sinMejora++;
            if(sinMejora > 20) {
                alpha = 0.5;
            }
        }
        
        evaluacion++;
    }      
   
    return mejorCoste;     
}
