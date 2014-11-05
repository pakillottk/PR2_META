/*
 * File:   Greedy.h
 * Author: Fasgort
 *
 * Created on 5 de octubre de 2014, 12:40
 */

#ifndef GRASP_H
#define	GRASP_H

#include <iostream>
#include <string>
#include <climits>

#include "Metaheuristica.h"
#include "BL.h"
using namespace std;

/*
 *      Clase que contiene la funcionalidad del
 *      algoritmo Greedy.
 */
class GRASP : public Metaheuristica {
	private:
	BL* bl; //Instancia de la BL
    public:
        GRASP(const std::string& rutaFichero);
        virtual ~GRASP();

        virtual unsigned long ejecutar();
        static void alg_greedy(unsigned* s, unsigned** f, unsigned** d, unsigned tam);
};

#endif	/* GRASP_H */

