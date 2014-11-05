/*
 * File:   ILS.h
 * Author: Fco Gázquez
 *
 * Created on 29 de octubre de 2014, 11:34
*/

#ifndef ILS_H
#define	ILS_H

#include "Metaheuristica.h"
#include "BL.h"
#include <iostream>
using namespace std;

class ILS : public Metaheuristica {
    protected:
        BL* bl; //Instancia de la BL
        unsigned long costeActual;
        unsigned sublista;

        unsigned long mutar(unsigned* p);

    public:
        ILS(const string& rutaFichero);
        virtual ~ILS();
        unsigned long ejecutar();
};

#endif	/* ILS_H */