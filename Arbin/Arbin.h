#ifndef ARBIN_H
#define ARBIN_H
#include <stddef.h>
#include <stdio.h>
#include "NodoB.h"
#include <list>
#include <queue>
using namespace std;
/* */
inline int max(int n1, int n2)
{
    return n1 >= n2 ? n1 : n2;
}

template <class Elemento>
class Arbin
{
    private:
        NodoB<Elemento> *raiz;
        /*** Estos métodos son recursivos qu necesitan ser privados para funcionar.
         *  Cada uno corresponde al respectivo método público al que hace referencia.  
         ***/
        
        /*Copia los nodos recursivamente de un arbol.*/
        static NodoB<Elemento>* copiarNodos( NodoB<Elemento>* ptr);
        static int  altura(NodoB<Elemento>* ptr);
        static void vaciar(NodoB<Elemento>* ptr);
        static void preorden(NodoB<Elemento>* ptr, list<Elemento> &prelist);
        static void postorden(NodoB<Elemento>* ptr, list<Elemento> &postlist);
        static void inorden(NodoB<Elemento>* ptr, list<Elemento> &inlist);
        static NodoB<Elemento>* leerPreIn(list<Elemento> &preorden,list<Elemento> &inorden);
        static NodoB<Elemento>* leerPostIn(list<Elemento> &postorden,list<Elemento> &inorden);

    public:

    /***  Constructores  ***/
        Arbin();
        Arbin(const Arbin<Elemento> &src);

        /***  Modificadores  ***/
        void copiar(const Arbin<Elemento> &src);
        /*Borra el espacio ocupado por el arbol*/
        void vaciar();
        /*Insertar un arbol como subarbol izq. Elimina el subarbol anterior*/
        void insHi(const Arbin<Elemento> &sub);
        /*Insertar un arbol como subarbol der. Elimina el subarbol anterior*/
        void insHd(const Arbin<Elemento> &sub);
        /*Crea el arbol a partir de los recorridos inorden y preorden almacenados en
        * preorden e inorden, las cuales son destruidas.
        */
        void leerPreorden(list<Elemento> &preorden, list<Elemento> &inorden);  
        /*Crea el arbol a partir de los recorridos inorden y postorden almacenados en
        * postoden e inorden, las cuales son destruidas.
        */
        void leerPostorden(list<Elemento> &postorden,list<Elemento> &inorden);
        /*** Verificadores ***/
        
        /*Retorna verdadero si la raiz es Nula, i.e no tiene info ni hijos */
        bool esNulo() const;
        Elemento obtRaiz() const;
        /*Retorna una copia del arbol izquierdo*/
        Arbin<Elemento> obtHi() const;
        /*Retorna una copia del arbol derecho*/
        Arbin<Elemento> obtHd() const;
        
        /*Retorna verdadero si la raiz no tiene hijos */
        bool esHoja() const;
        /*Retonra la altura, es decir el camino mas largo desde la raiz hasta una hoja */
        int altura() const;
        /*Cada uno  retorna una lista con el recorrido particular*/
        list<Elemento> preorden() const;
        list<Elemento> postorden() const;
        list<Elemento> inorden() const;
        list<Elemento> niveles() const;
        /*** Destructor ***/
        ~Arbin();
        Arbin<Elemento> &operator=(const Arbin<Elemento> &t);

};
template <class Elemento>
Arbin<Elemento>::Arbin()
{
    this->raiz = NULL;
}
template <class Elemento>
Arbin<Elemento>::Arbin(const Arbin<Elemento> &src)
{
    this->copiar(src);
}
template <class Elemento>
void Arbin<Elemento>::copiar(const Arbin<Elemento> &src)
{
    this->raiz = copiarNodos(src.raiz);
}

template <class Elemento>
NodoB<Elemento>* Arbin<Elemento>::copiarNodos(NodoB<Elemento>* ptr)
{
    NodoB<Elemento>* nuevo;
    
    if(ptr == NULL)
    {
        nuevo = NULL;
    }
    else
    {
        nuevo = new NodoB<Elemento>(ptr->obtInfo());
        nuevo->modHd(copiarNodos(ptr->obtHd()));
        nuevo->modHi(copiarNodos(ptr->obtHi()));
    }
    return nuevo;
    
}

template <class Elemento>
Arbin<Elemento> Arbin<Elemento>::obtHi() const
{
    Arbin<Elemento> hijo_izq;
    
    if(this->raiz != NULL)
    {
        hijo_izq.raiz = this->copiarNodos(this->raiz->obtHi());
    }
    
    return hijo_izq;
}

template <class Elemento>
Arbin<Elemento> Arbin<Elemento>::obtHd() const
{
    Arbin<Elemento> hijo_der;
    
    if(this->raiz != NULL)
    {
        hijo_der.raiz = this->copiarNodos(this->raiz->obtHd());
    }
   
    return hijo_der;
}
template <class Elemento>
bool Arbin<Elemento>::esHoja() const
{
    return this->raiz->obtHi() == NULL && this->raiz->obtHd() == NULL;
}

template <class Elemento>
int Arbin<Elemento>::altura() const
{
    return max(altura(raiz->obtHi()),altura(raiz->obtHd()));
}

template <class Elemento>
int Arbin<Elemento>::altura(NodoB<Elemento> *ptr)
{
    if(ptr == NULL)
    {
        return 0;
    }
    else
    {
        return max(altura(ptr->obtHd()),altura(ptr->obtHi())) + 1;
    }
    
}

template <class Elemento>
void Arbin<Elemento>::vaciar()
{
    this->vaciar(this->raiz);
    this->raiz = NULL;
}

template <class Elemento>
void Arbin<Elemento>::vaciar(NodoB<Elemento>* ptr)
{
    if(ptr != NULL)
    {
        vaciar(ptr->obtHi());
        vaciar(ptr->obtHd());
        delete ptr;
    }
}

template <class Elemento>
void Arbin<Elemento>::insHi(const Arbin<Elemento> &sub)
{
    vaciar(this->raiz->obtHi());
    this->raiz->modHi(copiarNodos(sub.raiz));
}
template <class Elemento>
void Arbin<Elemento>::insHd(const Arbin<Elemento> &sub)
{
    vaciar(this->raiz->obtHd());
    this->raiz->modHd(copiarNodos(sub.raiz));
}

template <class Elemento>
Arbin<Elemento>::~Arbin()
{
    this->vaciar(this->raiz);
    this->raiz = NULL;
}

template <class Elemento>
list<Elemento> Arbin<Elemento>::preorden() const
{
    list<Elemento> prelist;
    preorden(this->raiz,prelist);
    return prelist;
}

template <class Elemento>
void Arbin<Elemento>::preorden(NodoB<Elemento>* ptr, list<Elemento> &prelist)
{
    if(ptr != NULL)
    {   
        prelist.push_back(ptr->obtInfo());
        preorden(ptr->obtHi(),prelist);
        preorden(ptr->obtHd(),prelist);
    }
}

template <class Elemento>
list<Elemento> Arbin<Elemento>::postorden() const
{
    list<Elemento> postlist;
    postorden(this->raiz,postlist);
    return postlist;
}

template <class Elemento>
void Arbin<Elemento>::postorden(NodoB<Elemento>* ptr, list<Elemento> &postlist)
{
    if(ptr != NULL)
    {   
        postorden(ptr->obtHi(),postlist);
        postorden(ptr->obtHd(),postlist);
        postlist.push_back(ptr->obtInfo());       
    }
}

template <class Elemento>
list<Elemento> Arbin<Elemento>::inorden() const
{
    list<Elemento> inlist;
    inorden(this->raiz,inlist);
    return inlist;
}

template <class Elemento>
void Arbin<Elemento>::inorden(NodoB<Elemento>* ptr, list<Elemento> &inlist)
{
    if(ptr != NULL)
    {   
        inorden(ptr->obtHi(),inlist);
        inlist.push_back(ptr->obtInfo()); 
        inorden(ptr->obtHd(),inlist);      
    }
}

template <class Elemento>
list<Elemento> Arbin<Elemento>::niveles() const
{
    list<Elemento> l;
    queue<NodoB<Elemento>*> q;
    NodoB<Elemento>* aux;
    if(this->raiz != NULL)
    {
        q.push(this->raiz);
        l.push_back(this->raiz->obtInfo());
        while(!q.empty())
        {
            aux = q.front();
            q.pop();
            if(aux->obtHi() != NULL)
            {
                q.push(aux->obtHi());
                l.push_back(aux->obtHi()->obtInfo());
            }
            if(aux->obtHd() != NULL)
            {
                q.push(aux->obtHd());
                l.push_back(aux->obtHd()->obtInfo());
            }
        }
    }
    return l;  
}
template <class Elemento>
void Arbin<Elemento>::leerPreorden(list<Elemento> &preorden,list<Elemento> &inorden)
{
    this->raiz = leerPreIn(preorden,inorden);
}

template <class Elemento>
NodoB<Elemento>* Arbin<Elemento>::leerPreIn(list<Elemento> &preorden,list<Elemento> &inorden)
{
    list<Elemento> izquierda;
    NodoB<Elemento> *nuevo = NULL;

    if(preorden.empty() || inorden.empty())
    {
        return NULL;
    }
    else
    {
        while(preorden.front() != inorden.front())
        {
            izquierda.push_back(inorden.front());
            inorden.pop_front();
        }
        
        nuevo = new NodoB<Elemento>(preorden.front());
        preorden.pop_front();
        inorden.pop_front();
        nuevo->modHi(leerPreIn(preorden,izquierda));
        nuevo->modHd(leerPreIn(preorden,inorden));
         return nuevo;
    }
}

template <class Elemento>
void Arbin<Elemento>::leerPostorden(list<Elemento> &preorden,list<Elemento> &inorden)
{
    this->raiz = leerPostIn(preorden,inorden);
}

template <class Elemento>
NodoB<Elemento>* Arbin<Elemento>::leerPostIn(list<Elemento> &postorden,list<Elemento> &inorden)
{
    list<Elemento> izquierda;
    NodoB<Elemento> *nuevo = NULL;
    if(!postorden.empty() && !inorden.empty())
    {
        while(postorden.back() != inorden.front())
        {
            izquierda.push_back(inorden.front());
            inorden.pop_front();
        }
        
        nuevo = new NodoB<Elemento>(postorden.back());  
        postorden.pop_back();
        inorden.pop_front();
        nuevo->modHd(leerPostIn(postorden,inorden));
        nuevo->modHi(leerPostIn(postorden,izquierda));   
    }
    
    return nuevo;
}

template <class Elemento>
Arbin<Elemento> &Arbin<Elemento>::operator=(const Arbin<Elemento> &t)
{
    this->copiar(t);
}
#endif