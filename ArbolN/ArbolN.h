#ifndef ARBOLN_H
#define ARBOLN_H
#include <iostream>
#include "NodoArbolN.h"
#include <list>
#include <string>

using std::string;
using std::list;
using namespace std;

template  <class Elemento>
class ArbolN 
{
    private:
        NodoArbolN<Elemento> *nodoRaiz;
        NodoArbolN<Elemento>* copiarNodos(NodoArbolN<Elemento>* p);
        void insertar(const Elemento &padre,const Elemento &e);
        NodoArbolN<Elemento>* encontrarNodo(NodoArbolN<Elemento> *, Elemento );
        void recorridoNiveles(list<Elemento> &);
        void recorridoPreorden(NodoArbolN<Elemento> *, list<Elemento> &);
        void recorridoPostorden(NodoArbolN<Elemento> *, list<Elemento> &);
        void encontrarPadre(NodoArbolN<Elemento> *, Elemento , Elemento& , bool &);
        int  cantidadHijos(NodoArbolN<Elemento>* ) const;
        void destruirnodos(NodoArbolN<Elemento> *);
        Elemento obtPadre(Elemento key) ;
        int altura(NodoArbolN<Elemento> *) const;
        bool esIgual(NodoArbolN<Elemento> *, NodoArbolN<Elemento> *); 
        /*Impresion */
        void printHijosNivel(NodoArbolN<Elemento>* Nodo);
        void printHijosNodo(NodoArbolN<Elemento>* Nodo);


    public:
        /*Constructor */
        ArbolN();
        /*Metodo de copiado */
        void copiar(const ArbolN<Elemento>&);
        /*Metodos funcionales */
        bool esVacio() const ; 
        int altura() const;
        bool esta(Elemento key) const ;
        bool esIgual(const ArbolN<Elemento> &); 
        Elemento raiz();
        /*Metodos de vaciado */
        void Vaciar();
        ~ArbolN(){this->Vaciar();};
        /*Metodos de insertado */
        void InsertarElemento(const Elemento &padre,const Elemento &e){this->insertar(padre, e);};
        void InsertarRaiz(const Elemento &); 
        void insertarSubarbol(ArbolN<Elemento>);
        /*Metodos de recorrido */
        list< ArbolN<Elemento> > hijos() const;
        list<Elemento> Niveles();
        list<Elemento> Preorden() ;
        list<Elemento> Postorden() ;
        /*Operadores */
        bool operator==(const ArbolN<Elemento> &a);
        void operator=(const ArbolN<Elemento> &a);
        void primos(Elemento);






        
};
/* **********************************************************CONSTRUCTOR******************************************* */
template <class Elemento>
ArbolN<Elemento>::ArbolN()
{
    this->nodoRaiz=NULL;
}
/*******************************************************ALGORITMOS DE COPIADO************************************** */
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
    this->nodoRaiz=copiarNodos(a.nodoRaiz);
}
/****************************ALGORITMOS DE FUNCIONALIDADES******************************************************** */
template <class Elemento>
bool ArbolN<Elemento>::esVacio() const
{
    return(this->nodoRaiz==NULL);
}
template <class Elemento>
Elemento ArbolN<Elemento>::raiz() 
{
    return(this->nodoRaiz->obtInfo());
}




template <class Elemento>
int ArbolN<Elemento>::cantidadHijos(NodoArbolN<Elemento>* Nodo) const
{
    int cont=0;
    NodoArbolN<Elemento> * aux;
    if(Nodo!=NULL)
    {
        aux=Nodo;
        aux=aux->obtIzq();
        cont+=1;
        while(aux!=NULL)
        {
            cont+=1;
            aux=aux->obtDer();
        }
        cont-=1;

    }
    else
    {
        cont=-1;
    }
    return(cont);
    
} 

template <class Elemento>
void ArbolN<Elemento>::printHijosNodo(NodoArbolN<Elemento>* Nodo) 
{
    
    NodoArbolN<Elemento> * aux;
    if(Nodo!=NULL)
    {
        aux=Nodo;
        aux=aux->obtIzq();
        
        while(aux!=NULL)
        {
            cout<<aux->obtInfo()<<", ";
            aux=aux->obtDer();
        }
        

    }    
} 
template <class Elemento>
void ArbolN<Elemento>::printHijosNivel(NodoArbolN<Elemento>* Nodo) 
{
    Elemento p;
    NodoArbolN<Elemento> * aux, *padre;
    bool band=false;
    p=this->obtPadre(Nodo->obtInfo());
    padre=this->encontrarNodo(this->nodoRaiz,p);
    if(padre!=NULL)
    {
        while(padre!=NULL)
        {
            aux=padre;
            aux=aux->obtIzq();
        
            while(aux!=NULL)
            {   
                
                if((aux != Nodo)&& (aux->obtIzq()!=NULL))  
                {   
                    this->printHijosNodo(aux);          
                    cout<<"Hijos((as) de "<<aux->obtInfo()<<")"<<endl;
                    band=true;
                }
                aux=aux->obtDer();
                
            }
            padre=padre->obtDer();
        }
        if(!band)
        {
            cout<<"No tiene primos"<<endl;
        } 
    }
       
} 








template <class Elemento>
list< ArbolN<Elemento> >  ArbolN<Elemento>::hijos() const
{
    list <ArbolN<Elemento> > L;
    NodoArbolN<Elemento>* aux;
    ArbolN<Elemento> arbolAux;
    aux=this->nodoRaiz->obtIzq();
    while(aux!=NULL)
    {
        arbolAux.nodoRaiz=aux;
        L.push_back(arbolAux);
        aux=aux->obtDer();
    }
    return(L);
} 


template <class Elemento>
int ArbolN<Elemento>::altura() const
{
	return this->altura(this->nodoRaiz);
}

template <class Elemento>
int ArbolN<Elemento>::altura(NodoArbolN<Elemento> *a) const
{
	NodoArbolN<Elemento> *h;
	int mayor, aux;

	if(a == NULL)
		return 0;
	else if(a->obtIzq() == NULL)
		return 1;
	else
	{
		mayor = altura(a->obtIzq());
		h = a->obtIzq()->obtIzq();
		while(h != NULL)
		{
			aux = altura(h);
			h = h->obtDer();
			if(aux > mayor)
				mayor = aux;
		}
		return mayor + 1;
	}
}



template <class Elemento>
bool ArbolN<Elemento>::operator==(const ArbolN<Elemento> &a)
{
	return this->esIgual(a);
}

template <class Elemento>
bool ArbolN<Elemento>::esIgual(NodoArbolN<Elemento> *a, NodoArbolN<Elemento> *b) 
{
	if(a == NULL && b == NULL)
		return true;
	else if((a == NULL && b != NULL) || (a != NULL && b == NULL))
		return false;
	else if(a->obtInfo() != b->obtInfo())
		return false;
	else
		return this->esIgual(a->obtIzq(), b->obtIzq()) && this->esIgual(a->obtDer(), b->obtDer());
}

template <class Elemento>
bool ArbolN<Elemento>::esIgual(const ArbolN<Elemento> &a) 
{
	return this->esIgual(this->nodoRaiz, a.nodoRaiz);
}
template <class Elemento>
void ArbolN<Elemento>::operator=(const ArbolN<Elemento> &a)
{
	if(this != &a)
	{
		this->Vaciar();
		this->copiar(a);
	}
}

template <class Elemento>
bool ArbolN<Elemento>::esta(Elemento key) const
{
    return(encontrarNodo(this->nodoRaiz,key)==NULL);
   
}
/*********************************************************ALGORITMOS DE VACIADO************************************************************************* */

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
/*************************************************ALGORITMOS DE INSERTADO****************************************************** */

template <class Elemento>
void ArbolN<Elemento>::insertar(const Elemento &padre,const Elemento &e)
{
    NodoArbolN<Elemento> *aux = encontrarNodo(this->nodoRaiz,padre);//busca el nodo padre
    NodoArbolN<Elemento> *nuevo;
    if(aux!=NULL)//si el nodo padre existe
    {
        nuevo=new NodoArbolN<Elemento>(e);//crea el nuevo elemento
            if(aux->obtIzq() == NULL)//si es el primer hijo de ese nodo entonces lo añado 
                
                aux->modIzq(nuevo);
            else//sino me muevo lo mas posible hasta la derecha y lo inserto junto a los demas hermanos
            {
                aux = aux->obtIzq();
                while(aux->obtDer() != NULL)
                    aux = aux->obtDer();
                aux->modDer(nuevo);
            }
    }
    else
    {//sino 
       aux=this->nodoRaiz;//
       nuevo=new NodoArbolN<Elemento>(padre);//creo el nodo padre 
            if(aux->obtIzq() == NULL)//si es el primer hijo de ese nodo entonces lo añado   
                aux->modIzq(nuevo);
            else//sino me muevo lo mas posible hasta la derecha y lo inserto junto a los demas hermanos
            {
                aux = aux->obtIzq();
                while(aux->obtDer() != NULL)
                    aux = aux->obtDer();
                aux->modDer(nuevo);
            }
       this->insertar(padre, e);//hago el llenado
    }
}
template <class Elemento>
void ArbolN<Elemento>::InsertarRaiz(const Elemento &padre)
{
    
    
    this->nodoRaiz=new NodoArbolN<Elemento>(padre);
    
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
/**************************************************ALGORITMOS DE BUSQUEDA**********************************************/
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
  
  return encontrarNodo(raiz->obtIzq(), key);
}

template <class Elemento>
void ArbolN<Elemento>::encontrarPadre(NodoArbolN<Elemento> *raiz, Elemento key, Elemento& prev, bool &band ) 
{
    if (raiz!=NULL)
    {
        if (raiz->obtInfo()==key)
        {  
              band=true;
        } 
    
        encontrarPadre(raiz->obtDer(),key,prev,band);
        if ( !band ) 
        {
            prev=raiz->obtInfo();
            encontrarPadre(raiz->obtIzq(),key,prev,band);     
        }
  
    }     
}


template <class Elemento>
Elemento ArbolN<Elemento>::obtPadre(Elemento key) 
{
    Elemento Padre;
    bool logico;
    Padre=this->nodoRaiz->obtInfo();

    if(encontrarNodo(this->nodoRaiz,key)!=NULL)
    {
        encontrarPadre(this->nodoRaiz,key,Padre,logico);
    
    }
    return(Padre);
}


/*************************************************** ALGORITMOS DE RECORRIDO *****************************************************************/
template <class Elemento >
void ArbolN<Elemento>::recorridoNiveles(list<Elemento> &recorrido)
{
    list<NodoArbolN<Elemento> *> hijos;             // Una lista de NODOS que sera por la cual nos vamos a mover para obtener nuestros nodo por nivel
    NodoArbolN<Elemento> *aux;
    

    hijos.push_back(this->nodoRaiz);                //El comportamiento de esta lista es como una cola
    recorrido.push_back(this->nodoRaiz->obtInfo());//Aqui es introducido la informacion de los nodos
 
    
    while(!hijos.empty())                          //mientras la lista de nodos no sea vacia
    {
       
        aux = hijos.front()->obtIzq();            //obtenemos el hijo del nodo que esta en el frente de nuestra lista
        while(aux != NULL)                       //mientras existan nodos en ese nivel
        {

            hijos.push_back(aux);               //encolamos los nodos en la lista de Hijos
            recorrido.push_back(aux->obtInfo());//encolamos la informacion
            aux = aux->obtDer();                //nos movemos al hermano
        }
        
        hijos.pop_front();                      // nos movemos al proximo nivel
    }
}

template <class Elemento>
list<Elemento> ArbolN<Elemento>::Niveles() 
{
    list<Elemento> niveles;
    if(this->nodoRaiz != NULL)
        this->recorridoNiveles(niveles);
     return niveles;
}


template <class Elemento>
void ArbolN<Elemento>::recorridoPreorden(NodoArbolN<Elemento> *raiz, list<Elemento> &preorden)
{
    if(raiz != NULL)
    {
        preorden.push_back(raiz->obtInfo());
        recorridoPreorden(raiz->obtHi(), preorden);
        recorridoPreorden(raiz->obtHd(), preorden);
    }
}

template <class Elemento>
list<Elemento> ArbolN<Elemento>::Preorden() 
{
    list<Elemento> preorden;

    this->recorridoPreorden(this->nodoRaiz, preorden);

    return preorden;
}
template <class Elemento>
void ArbolN<Elemento>::recorridoPostorden(NodoArbolN<Elemento> *raiz, list<Elemento> &post)
{
    if(raiz != NULL)
    {
        recorridoPostorden(raiz->obtHi(), post);
        post.push_back(raiz->obtInfo());
        recorridoPostorden(raiz->obtHd(), post);
    }
}

template <class Elemento>
list<Elemento> ArbolN<Elemento>::Postorden() 
{
    list<Elemento> post;

    this->recorridoPostorden(this->nodoRaiz, post);

    return post;
}








template <class Elemento >
void ArbolN<Elemento>::primos(Elemento e)
{
 NodoArbolN<Elemento> *nPadre;
 Elemento p;
 p=this->obtPadre(e);
 
 nPadre=this->encontrarNodo(this->nodoRaiz,p);
  cout<<"Los primos de "<<e<<" Son: "<<endl;
 this->printHijosNivel(nPadre);
    
}






















































#endif