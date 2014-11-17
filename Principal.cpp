
#include "Principal.h"


//VARIABLES ESTÁTICAS
//===================
bool Principal::debug = false;

//CONSTRUCTORES Y DESTRUCTORES
//===========================
Principal::Principal(): metaheuristica(0) {
   /*
    //Activación del modo debug
    activarDebug();

    //Definición del fichero
    elegirFichero();

    //Elección de algoritmo
    elegirAlgoritmo();

    //Elección de semilla
    elegirSemilla();    
    * */
}

Principal::~Principal() {
    if(metaheuristica)
        delete metaheuristica;
}

//MÉTODOS PROTECTED
//=================
void Principal::activarDebug(){
     char d;

     do {
        std::cout << "El modo debug mostrara, por pantalla, informacion adicional"
                  << " sobre la ejecucion"<< std::endl <<"del programa..."
                  << std::endl << "Desea activar el modo debug?"
                  << " (s/n): ";
        std::cin >> d;
        std::cout << std::endl;
    }while(d != 's' && d != 'n');

    if(d == 's')
        Principal::debug = true;
}

void Principal::elegirFichero() {    
    fstream f;
    string ruta;
    
    do {
        std::cout << "Nombre del fichero (sin extension): " << std::flush;
        getline(std::cin >> std::ws, fichero);
        std::cout << std::endl;
        
        ruta = "./DAT/" + fichero + ".dat";
        f.open ( ruta.c_str() , std::ios::in);
        if(!f.is_open())
            cout << "No existe el fichero: " << fichero << ".dat" << endl;
    } while(!f.is_open());
    
    f.close();
}

void Principal::elegirAlgoritmo() {
    unsigned short opcion;
    
    do {
        cout << "Seleccione algoritmo: " << endl;
        cout << "1.GRASP" << endl
             << "2.ILS" << endl << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;
    } while (opcion < 1 || opcion > 2);
    
    switch(opcion) {
        case 1:
            tipo = ALG_GRASP;
        break;
        
        case 2:
            tipo = ALG_ILS;
        break;
    }
}

void Principal::elegirSemilla() {
    std::cout << "Introduzca la semilla: ";
    std::cin >> semilla;
    std::cout << std::endl;

    srand(semilla);
}

void Principal::construirAlgoritmo() {  
    if(metaheuristica)
        delete metaheuristica;
    
    //Instanciación de la metaheurística
    switch(tipo) {
        case ALG_GRASP:
             metaheuristica = new GRASP("./DAT/" + fichero + ".dat");
        break;
        
        case ALG_ILS:
             metaheuristica = new ILS("./DAT/" + fichero + ".dat");
        break;
    }  
    
    
}



void Principal::ejecutarAlgoritmo() {
    unsigned long coste;
    double tiempo;
    Timer timer;
    
    construirAlgoritmo();
    
    timer.start();
    coste = metaheuristica->ejecutar();
    timer.stop();    
   
    tiempo = timer.getElapsedTimeInMilliSec();
 
    cout << "Coste: " << coste << endl;  
   
    cout << "Tiempo (ms): " << tiempo << endl;
    
    cout << endl;
    
    cout << "Guardando resultados..." << endl;
    guardarResultados(coste, tiempo);
    cout << "Resultados almacenados" << endl;
    cout << endl;
}

void Principal::guardarResultados(unsigned long costeObtenido, unsigned tiempo) {
    fstream f;
    string ruta = "./RESULTADOS/" + fichero + ".txt";
    
    f.open(ruta.c_str(), ios::out | ios::app);
    
    f << "Algoritmo: " << tipo_str() << "\r\n";
    f << "Semilla: " << semilla << "\r\n";
    f << "Coste: " << costeObtenido << "\r\n";   
    
    f << "Tiempo (ms): " << tiempo  << "\r\n"; 
    f << "\r\n";
    f.close();
}

string const Principal::tipo_str() {
    switch(tipo) {
        case ALG_GRASP:
            return "GRASP";
        break;
        
        case ALG_ILS:
            return "ILS";
        break;
    }
}

//MÉTODOS PUBLIC
//==============

void Principal::iniciarMenu() {
    string ficheros[20] ={"Els19",
                        "Chr20a",
                        "Chr25a",
                        "Nug25",
                        "Bur26a",
                        "Bur26b",
                        "Tai30a",
                        "Tai30b",
                        "Esc32a",
                        "Kra32",
                        "Tai35a",
                        "Tai35b",
                        "Tho40",
                        "Tai40a",
                        "Sko42",
                        "Sko49",
                        "Tai50a",
                        "Tai50b",
                        "Tai60a",
                        "Lipa90a"};
    
    Tipo_Algoritmo tipos[2] = {ALG_GRASP, ALG_ILS};
    
    semilla = 1;
    srand(semilla);
    unsigned long coste;
    double tiempo;
    Timer timer;
    
    for(unsigned i = 0; i < 20; i++) {
        fichero = ficheros[i];
        cout << "Fichero: " << fichero << endl;
        
        for(unsigned j = 0; j < 2; j++) {
            tipo = tipos[j];          
            cout << "Algoritmo: " << tipo_str() << endl;
            ejecutarAlgoritmo();
        }
        
        cout << endl;
    }
    
    cout << "FICHEROS ANALIZADOS" << endl;

    /*
    unsigned short int opcion;

    do {

        cout << "//////////////////////////////////////////////////////////////////" << endl;
        cout << "///////////////////Metaheuristicas - Practica 1///////////////////" << endl;
        cout << "//////////////////////////////////////////////////////////////////" << endl << endl;

        cout << "Algoritmo: " << tipo_str() << endl;
        cout << "Fichero: " << fichero << ".dat" << endl;
        cout << "Semilla: " << semilla << endl << endl;

        cout << "¿Que desea hacer?" << endl << endl;

        cout << "1. Ejecutar algoritmo" << endl;
        cout << "2. Cambiar algoritmo" << endl;
        cout << "3. Cambiar fichero" << endl;
        cout << "4. Cambiar semilla" << endl;
        cout << "5. Cerrar el programa" << endl << endl;

        do {
            cout << "Opcion: ";
            cin >> opcion;
            skipline(cin);
            cout << endl;
        } while (opcion < 1 || opcion > 5);

        switch (opcion) {
            case 1:
            {
                ejecutarAlgoritmo();
                break;
            }
            case 2:
            {
                elegirAlgoritmo();
                break;
            }
            case 3:
            {
                elegirFichero();
                break;
            }
            case 4:
            {
                elegirSemilla();
                break;
            }
            case 5:
            {
                exit(0);
                break;
            }
        }

    } while (true);
     
     */
}
