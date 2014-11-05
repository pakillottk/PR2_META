/*
 * File:   BL.h
 * Author: Fco. Gázquez
 *
 * Created on 5 de octubre de 2014, 12:44
 */

#ifndef BL_H
#define	BL_H

#include <iostream>
#include <string>
#include <bitset>

#include "Metaheuristica.h"

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo de Búsqueda Local.
 */
class BL : public Metaheuristica {
    protected:
        bool* dlb; //Vector binario, don't look bits
        
    public:
        BL(unsigned** f, unsigned** d, unsigned t);
        virtual ~BL();

        virtual unsigned long ejecutar(unsigned* p);
};

#endif	/* BL_H */

