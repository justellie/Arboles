#ifndef ARBOLN_H
#define ARBOLN_H
#include <iostream>
#include "NodoArbolN.h"

#include "Listas.h"
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
    public:
        ArbolN();
        void copiar(const ArbolN<Elemento>&);
        bool esVacio();
        Elemento raiz();
        list< ArbolN<Elemento> > hijos();
        void insertarSubarbol(ArbolN<Elemento>);
        void destruirnodos(NodoArbolN<Elemento> *);
        void Vaciar();
        ~ArbolN(){this->Vaciar();};
        void InsertarElemento(const Elemento &padre,const Elemento &e){this->insertar(padre, e);};
        void InsertarElemento(const Elemento &); 
        void esta(Elemento key);
        list<Elemento> Niveles();
        list<Elemento> Preorden();
        list<Elemento> Postorden();
        Elemento obtPadre(Elemento key);





        
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
list< ArbolN<Elemento> >  ArbolN<Elemento>::hijos()
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
            cout<<"Insertado: "<<e<<" Hijo de: "<<padre<<endl;
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
  
  return encontrarNodo(raiz->obtIzq(), key);
}

template <class Elemento>
void ArbolN<Elemento>::encontrarPadre(NodoArbolN<Elemento> *raiz, Elemento key, Elemento& prev, bool &band ){


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

template <class Elemento>
Elemento ArbolN<Elemento>::obtPadre(Elemento key)
{
    Elemento Padre;
    bool logico;

    if(encontrarNodo(this->nodoRaiz,key)!=NULL)
    {
        encontrarPadre(this->nodoRaiz,key,Padre,logico);
    
    }
    return(Encontrado);
}

template <class Elemento >
void ArbolN<Elemento>::recorridoNiveles(list<Elemento> &recorrido)
{
    list<NodoArbolN<Elemento> *> hijos;// Una lista de NODOS que sera por la cual nos vamos a mover para obtener nuestros nodo por nivel
    NodoArbolN<Elemento> *aux;//
    

    hijos.push_back(this->nodoRaiz);//El comportamiento de esta lista es como una cola
    recorrido.push_back(this->nodoRaiz->obtInfo());//Aqui es introducido la informacion de los nodos
 
    //cout<<this->nodoRaiz->obtInfo()<<endl;
    //cout<<" "<<endl;
    
    while(!hijos.empty())//mientras la lista de nodos no sea vacia
    {
        
        aux = hijos.front()->obtIzq();//obtenemos el hijo del nodo que esta en el frente de nuestra lista
        while(aux != NULL)//mientras existan nodos en ese nivel
        {
            hijos.push_back(aux);//encolamos los nodos en la lista de Hijos
            recorrido.push_back(aux->obtInfo());//encolamos la informacion
            //cout<<aux->obtInfo()<<endl;
            aux = aux->obtDer();//nos movemos al hermano
        }
    
        //cout<<" "<<endl;
        hijos.pop_front();// nos movemos al proximo nivel
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



#endif