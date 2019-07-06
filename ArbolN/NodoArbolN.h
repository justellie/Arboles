#ifndef NODOARBOLN_H
#define NODOARBOLN_H
#include <iostream>
using namespace std;

template  <class Elemento>

class NodoArbolN 
{
    private:
        Elemento info;
        NodoArbolN<Elemento> *hijoIzq, *hnoDer;
    public:
        NodoArbolN();
        NodoArbolN(Elemento e , NodoArbolN<Elemento> *i, NodoArbolN<Elemento>*d);
        void modInfo(Elemento e );
        void modIzq(NodoArbolN<Elemento> *i);
        void modDer(NodoArbolN<Elemento> *d);
        Elemento obtInfo();
        NodoArbolN<Elemento>* obtIzq();
        NodoArbolN<Elemento>* obtDer();    
    
};
template <class Elemento>
NodoArbolN<Elemento>::NodoArbolN()
{
	Elemento *aux = new Elemento;
	this->info = *aux;
	this->hijoIzq = NULL;
    this->hnoDer = NULL;
}

template <class Elemento>
NodoArbolN<Elemento>::NodoArbolN(Elemento e, NodoArbolN<Elemento> *i, NodoArbolN<Elemento> *d)
{
	this->info = e;
	this->hijoIzq = i;
    this->hnoDer = d;
}

template<class Elemento>
Elemento NodoArbolN<Elemento>::obtInfo()
{
  return this->info;
}


template <class Elemento>
NodoArbolN<Elemento>* NodoArbolN<Elemento>::obtIzq()
{
	return this->hijoIzq;
}
template <class Elemento>
NodoArbolN<Elemento>* NodoArbolN<Elemento>::obtDer()
{
	return this->hnoDer;
}

template <class Elemento>
void NodoArbolN<Elemento>::modInfo(Elemento e)
{
	this->info = e;
}

template <class Elemento>
void NodoArbolN<Elemento>::modIzq(NodoArbolN<Elemento> *i)
{
	this->hijoIzq = i;
}
template <class Elemento>
void NodoArbolN<Elemento>::modDer(NodoArbolN<Elemento> *d)
{
	this->hnoDer = d;
}


#endif