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
        float alpha;
        
        void solucion_grasp(unsigned* p);
    public:
        GRASP(const std::string& rutaFichero, float _alpha = 0.3);
        virtual ~GRASP();

        virtual unsigned long ejecutar();       
};

#endif	/* GRASP_H */

