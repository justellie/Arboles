#ifndef NODO_H
#define NODO_H
#include <iostream>
using namespace std;

//***********************************************************************||| INICIO DEL NODO |||*************************************************************************

template <class T>
class Nodo{

	protected:
//||| ATRIBUTOS |||
		T info;				//Dato del nodo del arbol
		Nodo<T> *HI, *HD;	//Hijo Izquierdo e Hijo Derecho / Hermano Derecho

	public:
//||| CONSTRUCTOR |||
		Nodo<T>();

//||| METODOS |||
		void modInfo(T);		//Modificar informacion del nodo
		void modHI(Nodo<T>*);	//Modificar Hijo Izquierdo
		void modHD(Nodo<T>*);	//Modificar Hijo derecho
		T obtInfo();			//Obtener Informacion del nodo actual
		Nodo<T>* obtHI();		//Obtener Subarbol con el hijo izquierdo
		Nodo<T>* obtHD();		//Obtener Subarbol con el hijo o hermano derecho
};
//*************************************************************************||| FIN DEL NODO |||**************************************************************************



//*************************************************************************| IMPLEMENTACION |****************************************************************************

template <class T>
Nodo<T>::Nodo(){

	this->HI = NULL;
	this->HD = NULL;
}


template <class T>
void Nodo<T>::modInfo(T element){
	this->info = element;
}

template <class T>
void Nodo<T>::modHI(Nodo<T> *p){
	this->HI = p;
}

template <class T>
void Nodo<T>::modHD(Nodo<T> *p){
	this->HD = p;
}

template <class T>
T Nodo<T>::obtInfo(){
	return this->info;
}

template <class T>
Nodo<T>* Nodo<T>::obtHI(){
	return this->HI;
}

template <class T>
Nodo<T>* Nodo<T>::obtHD(){
	return this->HD;
}


#endif
