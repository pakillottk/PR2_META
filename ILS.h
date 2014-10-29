/*
 * File:   ILS.h
 * Author: Fco Gázquez
 *
 * Created on 29 de octubre de 2014, 11:34
*/

#ifndef ILS_H
#define	ILS_H

#include "Metaheuristica.h"

#include <iostream>
using namespace std;

class ILS : Metaheuristica {
	private:
	BL* bl; //Instancia de la BL
	
	public:
		ILS(const string& rutaFichero);
		virtual ~ILS();

		unsigned long ejecutar();
};

#endif	/* ILS_H */