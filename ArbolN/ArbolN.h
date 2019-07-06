#ifndef ARBOLN_H
#define ARBOLN_H
#include <iostream>
#include "NodoArbolN.h"

#include "Listas.h"
using namespace std;

template  <class Elemento>
class ArbolN 
{
    private:
        NodoArbolN<Elemento> *nodoRaiz;
        NodoArbolN<Elemento>* copiarNodos(NodoArbolN<Elemento>* p);
    public:
        ArbolN();
        void copiar(const ArbolN<Elemento>&);
        bool esVacio();
        Elemento raiz();
        Lista<ArbolN<Elemento>> hijos();
        void insertarSubarbol(ArbolN<Elemento>);
        void destruirNodos(NodoArbolN<Elemento> *);
        void Vaciar();
        ~ArbolN(){this->Vaciar();};


        
};
template <class Elemento>
ArbolN<Elemento>::ArbolN()
{
    this->nodoRaiz=NULL;
}
template <class Elemento>
NodoArbolN<Elemento>* ArbolN<Elemento>::copiarNodos(NodoArbolN<Elemento>* p)
{
    NodoArbolN<Elemento>* nuevoNodo;
    if(p==NULL)
    {
        return(NULL);
    }
    else
    {
        nuevoNodo= new NodoArbolN<Elemento>;
        nuevoNodo->modInfo(p->obtInfo());
        nuevoNodo->modIzq(copiarNodos(p->obtIzq()));
        nuevoNodo->modDer(copiarNodos(p->obtDer()));
        return(nuevoNodo);
    }
}
template <class Elemento>
void ArbolN<Elemento>::copiar(const ArbolN<Elemento>& a)
{
    this->nodoRaiz=copiarNodos(a->nodoRaiz);
}
template <class Elemento>
void ArbolN<Elemento>::copiar(const ArbolN<Elemento>& a)
{
    this->nodoRaiz=copiarNodos(a->nodoRaiz);
}
template <class Elemento>
bool ArbolN<Elemento>::esVacio()
{
    return(this->nodoRaiz==NULL);
}
template <class Elemento>
Elemento ArbolN<Elemento>::raiz()
{
    return(this->nodoRaiz->obtInfo());
}
template <class Elemento>
Lista<ArbolN<Elemento>> ArbolN<Elemento>::hijos()
{
    Lista<ArbolN<Elemento>> L;
    NodoArbolN<Elemento>* aux;
    ArbolN<Elemento> arbolAux;
    aux=this->nodoRaiz->obtIzq();
    while(aux!=NULL)
    {
        arbolAux.nodoRaiz=aux;
        L.insertar(arbolAux,L.longitud());
        aux=aux->obtDer();
    }
    return(L);
} 
template <class Elemento>
void ArbolN<Elemento>::insertarSubarbol(ArbolN<Elemento> subarbol)
{
    NodoArbolN<Elemento>* aux;
    if((this->nodoRaiz)->obtIzq()!=NULL)
    {
        this->nodoRaiz->modIzq(copiarNodos(subarbol.nodoRaiz));
    }
    else
    {
        aux=this->nodoRaiz->obtIzq();
        while(aux->obtDer()!=NULL)
        {
            aux=aux->obtDer();
        }
        aux->modDer(copiarNodos(subarbol.nodoRaiz));
    }

}
template <class Elemento>
void ArbolN<Elemento>::destruirNodos(NodoArbolN<Elemento> *arb)
{
    if(arb != NULL)
    {
        if(arb->obtDer() != NULL)
        {
            this->destruirnodos(arb->obtHd());
        }
        if(arb->obtIzq() != NULL)
        {
            this->destruirnodos(arb->obtIzq());
        }
        delete arb;
        arb = NULL;
    }
}
template <class Elemento>
void ArbolN<Elemento>::Vaciar()
{
    if(this->raiz != NULL)
    {
        this->destruirnodos(this->raiz);
        this->nodoRaiz = NULL;
    }
}


#endif