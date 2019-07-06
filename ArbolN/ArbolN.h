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
        void insertar(const Elemento &padre,const Elemento &e);
        NodoArbolN<Elemento>* encontrarNodo(NodoArbolN<Elemento> *, Elemento );

    public:
        ArbolN();
        void copiar(const ArbolN<Elemento>&);
        bool esVacio();
        Elemento raiz();
        Lista<ArbolN<Elemento> > hijos();
        void insertarSubarbol(ArbolN<Elemento>);
        void destruirnodos(NodoArbolN<Elemento> *);
        void Vaciar();
        ~ArbolN(){this->Vaciar();};
        void InsertarElemento(const Elemento &padre,const Elemento &e){this->insertar(padre, e);};
        void InsertarElemento(const Elemento &); 
        void esta(Elemento key);



        
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
Lista<ArbolN<Elemento> > ArbolN<Elemento>::hijos()
{
    Lista<ArbolN<Elemento> > L;
    NodoArbolN<Elemento>* aux;
    ArbolN<Elemento> arbolAux;
    aux=this->nodoRaiz->obtIzq();
    while(aux!=NULL)
    {
        arbolAux.nodoRaiz=aux;
        L.insertar(arbolAux,L.obtLongitud());
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
void ArbolN<Elemento>::destruirnodos(NodoArbolN<Elemento> *arb)
{
    if(arb != NULL)
    {
        if(arb->obtDer() != NULL)
        {
            this->destruirnodos(arb->obtDer());
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
    if(this->nodoRaiz != NULL)
    {
        this->destruirnodos(this->nodoRaiz);
        this->nodoRaiz = NULL;
    }
}
template <class Elemento>
void ArbolN<Elemento>::insertar(const Elemento &padre,const Elemento &e)
{
    NodoArbolN<Elemento> *aux = encontrarNodo(this->nodoRaiz,padre);
    NodoArbolN<Elemento> *nuevo;
    if(aux!=NULL)
    {
        nuevo=new NodoArbolN<Elemento>(e);
            if(aux->obtIzq() == NULL)
                
                aux->modIzq(nuevo);
            else
            {
                aux = aux->obtIzq();
                while(aux->obtDer() != NULL)
                    aux = aux->obtDer();
                aux->modDer(nuevo);
            }
            cout<<"Insertado: "<<e<<" Hijo de: "<<padre<<endl;
    }
    else
    {
       aux=this->nodoRaiz;
       nuevo=new NodoArbolN<Elemento>(padre);        
       while(aux->obtDer() != NULL)
       {
            aux = aux->obtDer();
       }        
       aux->modDer(nuevo); 
       this->insertar(padre, e);
    }
}
template <class Elemento>
void ArbolN<Elemento>::InsertarElemento(const Elemento &padre)
{
    
    
    this->nodoRaiz=new NodoArbolN<Elemento>(padre);
    
}
template <class Elemento>
NodoArbolN<Elemento>* ArbolN<Elemento>::encontrarNodo(NodoArbolN<Elemento> *raiz, Elemento key){
  NodoArbolN<Elemento>*encontrado;
  // stop case
  if (raiz==NULL)
  {
       return NULL;
  }
  
  if (raiz->obtInfo()==key)
  {
      return raiz;
  } 
  
  encontrado=encontrarNodo(raiz->obtDer(),key);
  if (  encontrado!= NULL ) 
  {
      return encontrado;
  }
  
  // if not found we recurse on the children
  return encontrarNodo(raiz->obtIzq(), key);
}
template <class Elemento>
void ArbolN<Elemento>::esta(Elemento key)
{
    if(encontrarNodo(this->nodoRaiz,key)!=NULL)
    {
        cout<<"Encontrado el elemento "<< key<<endl;
    
    }
    else
    {
        cout<<"No encontrado el elemento "<< key<<endl;
    }
}
#endif