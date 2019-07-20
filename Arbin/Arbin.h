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
    protected:
        NodoB<Elemento> *raiz;
        int peso;
        /*** Estos métodos son recursivos qu necesitan ser privados para funcionar.
         *  Cada uno corresponde al respectivo método público al que hace referencia.  
         ***/
        
        /*Copia los nodos recursivamente de un arbol.*/
        static NodoB<Elemento>* copiarNodos( NodoB<Elemento>* ptr, int &nnodos);
        static int  altura(NodoB<Elemento>* ptr);
        static void vaciar(NodoB<Elemento>* ptr,int &nnodos);
        static void preorden(NodoB<Elemento>* ptr, list<Elemento> &prelist);
        static void postorden(NodoB<Elemento>* ptr, list<Elemento> &postlist);
        static void inorden(NodoB<Elemento>* ptr, list<Elemento> &inlist);
        static NodoB<Elemento>* leerPreIn(list<Elemento> &preorden,list<Elemento> &inorden);
        static NodoB<Elemento>* leerPostIn(list<Elemento> &postorden,list<Elemento> &inorden);
        static void insertarNodo(NodoB<Elemento> *ptr, const Elemento &padre, const Elemento &hijo, bool &insertado);
        static void diametroNodo(NodoB<Elemento> *ptr, int &may, int &diam);
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
        //Insertar hijos asumiendo qe padre exista
        void insertarNodo(const Elemento &padre, const Elemento &hijo);
        //Insertar la raiz
        void insertarNodo(const Elemento &p){ this->raiz = new NodoB<Elemento>(p); this->peso += 1;}
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
        int diametro();
        /*Retorna verdadero si la raiz es Nula, i.e no tiene info ni hijos */
        bool esNulo() const;
        Elemento obtRaiz() const;
        /*Retorna una copia del arbol izquierdo*/
        Arbin<Elemento> obtHi() const;
        /*Retorna una copia del arbol derecho*/
        Arbin<Elemento> obtHd() const;
        /*Numero de elemetos en el arbol*/
        int obtPeso() const;
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
    this->peso = 0;
}
template <class Elemento>
Arbin<Elemento>::Arbin(const Arbin<Elemento> &src)
{
    this->copiar(src);
}
template <class Elemento>
void Arbin<Elemento>::copiar(const Arbin<Elemento> &src)
{
    int n = 0;
    this->raiz = copiarNodos(src.raiz,n);
    this->peso = src.peso;
}
template <class Elemento>
void Arbin<Elemento>::insertarNodo(const Elemento &padre, const Elemento &hijo)
{
    bool insertado = false;
    this->insertarNodo(this->raiz,padre,hijo,insertado);
    if(insertado) this->peso += 1;
}
template <class Elemento>
void Arbin<Elemento>::insertarNodo(NodoB<Elemento> *ptr, const Elemento &padre, const Elemento &hijo, bool &insertado)
{
    NodoB<Elemento> *nuevo;
    if(ptr != NULL && !insertado)
    {
        if(ptr->obtInfo() == padre)
        {
            nuevo = new NodoB<Elemento>(hijo);
            if(ptr->obtHi() == NULL)
            {
                ptr->modHi(nuevo);
            }
            else if(ptr->obtHd() == NULL)
            {
                 ptr->modHd(nuevo);
            }
            insertado = true;
        }
        else
        {
            insertarNodo(ptr->obtHi(),padre,hijo,insertado);
            insertarNodo(ptr->obtHd(),padre,hijo,insertado);
        }
    }
}



template <class Elemento>
int Arbin<Elemento>::obtPeso() const
{
    return this->peso;
}
template <class Elemento>
NodoB<Elemento>* Arbin<Elemento>::copiarNodos(NodoB<Elemento>* ptr,int &nnodos)
{
    NodoB<Elemento>* nuevo;
    
    if(ptr == NULL)
    {
        nuevo = NULL;
    }
    else
    {
        nuevo = new NodoB<Elemento>(ptr->obtInfo());
        nnodos++;
        nuevo->modHd(copiarNodos(ptr->obtHd(),nnodos));
        nuevo->modHi(copiarNodos(ptr->obtHi(),nnodos));
    }
    return nuevo;
    
}

template <class Elemento>
Arbin<Elemento> Arbin<Elemento>::obtHi() const
{
    Arbin<Elemento> hijo_izq;
    int nnodos = 0;
    
    if(this->raiz != NULL)
    {
        hijo_izq.raiz = this->copiarNodos(this->raiz->obtHi(),nnodos);
        hijo_izq.peso = nnodos;
    }
    
    return hijo_izq;
}

template <class Elemento>
Arbin<Elemento> Arbin<Elemento>::obtHd() const
{
    Arbin<Elemento> hijo_der;
    int nnodos = 0;
    if(this->raiz != NULL)
    {
        hijo_der.raiz = this->copiarNodos(this->raiz->obtHd(),nnodos);
        hijo_der.peso = nnodos;
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
    int nnodos = 0;
    this->vaciar(this->raiz,nnodos);
    this->raiz = NULL;
    this->peso = 0;
}

template <class Elemento>
void Arbin<Elemento>::vaciar(NodoB<Elemento>* ptr, int &nnodos)
{
    if(ptr != NULL)
    {
        vaciar(ptr->obtHi(),nnodos);
        vaciar(ptr->obtHd(),nnodos);
        nnodos++;
        delete ptr;
    }
}

template <class Elemento>
void Arbin<Elemento>::insHi(const Arbin<Elemento> &sub)
{
    int nnodos = 0;
    vaciar(this->raiz->obtHi(),nnodos);
    this->peso -= nnodos;
    this->raiz->modHi(copiarNodos(sub.raiz,nnodos));
    this->peso += sub.peso;
}
template <class Elemento>
void Arbin<Elemento>::insHd(const Arbin<Elemento> &sub)
{
    int nnodos = 0;
    vaciar(this->raiz->obtHd(),nnodos);
    this->peso -= nnodos;
    this->raiz->modHd(copiarNodos(sub.raiz,nnodos));
    this->peso += sub.peso;
}

template <class Elemento>
Arbin<Elemento>::~Arbin()
{
    int nnodos;
    this->vaciar(this->raiz,nnodos);
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
    this->peso = preorden.size();
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
void Arbin<Elemento>::leerPostorden(list<Elemento> &postorden,list<Elemento> &inorden)
{
    this->peso = postorden.size();
    this->raiz = leerPostIn(postorden,inorden);
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
template <class Elemento>
int Arbin<Elemento>::diametro()
{
    int diam  = -1, alt = -1;
    diametroNodo(this->raiz,diam,alt);
    return diam;
}

template <class Elemento>
void Arbin<Elemento>::diametroNodo(NodoB<Elemento> *ptr, int &may, int &altura)
{
    int diam, diam_iz = -1, diam_der = -1, alt_izq = -1, alt_der = -1;
    if(ptr == NULL)
    {
        may = -1;
        altura = -1;
    }
    else if(ptr->obtHi() == NULL && ptr->obtHd() == NULL)
    {
        may = 0;
        altura = 0;
    }
    else
    {
        diametroNodo(ptr->obtHi(),diam_iz,alt_izq);
        diametroNodo(ptr->obtHi(),diam_der,alt_der);
        altura = max(alt_izq,alt_der) + 1;
        may = max(alt_izq + alt_der + 2, max(diam_iz,diam_der));
    }
}

#endif