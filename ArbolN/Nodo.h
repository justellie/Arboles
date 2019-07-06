#ifndef NODO_H
#define NODO_H
#include <iostream>

template <class Elemento>
class Nodo
{
	//Atributos
	private:
		Elemento info;//el campo que almacena el valor del nodo
		Nodo<Elemento> *prox;//el campo que apunta al siguiente nodo
	//Metodos
	public:
		Nodo();
		Nodo(Elemento e);
		Nodo(Elemento e, Nodo<Elemento> *p);
		Elemento obtInfo();
		Nodo<Elemento>* obtProx();
		void modInfo(Elemento e);
		void modProx(Nodo<Elemento> *p);
};


template <class Elemento>
Nodo<Elemento>::Nodo()
{
	Elemento *aux = new Elemento;
	this->info = *aux;
	this->prox = NULL;
}

template <class Elemento>
Nodo<Elemento>::Nodo(Elemento e)
{
	this->info = e;
	this->prox = NULL;
}

template <class Elemento>
Nodo<Elemento>::Nodo(Elemento e, Nodo<Elemento> *p)
{
	this->info = e;
	this->prox = p;
}

template<class Elemento>
Elemento Nodo<Elemento>::obtInfo()
{
  return this->info;
}


template <class Elemento>
Nodo<Elemento>* Nodo<Elemento>::obtProx()
{
	return this->prox;
}

template <class Elemento>
void Nodo<Elemento>::modInfo(Elemento e)
{
	this->info = e;
}

template <class Elemento>
void Nodo<Elemento>::modProx(Nodo<Elemento> *p)
{
	this->prox = p;
}
#endif