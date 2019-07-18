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
        Elemento obtPadre(Elemento key) const;
        int altura(NodoArbolN<Elemento> *) const;



    public:
        ArbolN();
        void copiar(const ArbolN<Elemento>&);
        bool esVacio() const ; 
        int altura() const;
        bool esta(Elemento key) const ;
        Elemento raiz() const;
        void Vaciar();
        ~ArbolN(){this->Vaciar();};
        void InsertarElemento(const Elemento &padre,const Elemento &e){this->insertar(padre, e);};
        void InsertarRaiz(const Elemento &); 
        void insertarSubarbol(ArbolN<Elemento>);
        list< ArbolN<Elemento> > hijos() const;
        list<Elemento> Niveles();
        list<Elemento> Preorden() const;
        list<Elemento> Postorden() const;
        //void primos(Elemento );
        






        
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
    this->nodoRaiz=copiarNodos(a->nodoRaiz);
}
/****************************ALGORITMOS DE FUNCIONALIDADES******************************************************** */
template <class Elemento>
bool ArbolN<Elemento>::esVacio() const
{
    return(this->nodoRaiz==NULL);
}
template <class Elemento>
Elemento ArbolN<Elemento>::raiz() const
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
bool ArbolN<Elemento>::esta(Elemento key) const
{
    return(encontrarNodo(this->nodoRaiz,key)==NULL);
   
}

template <class Elemento>
Elemento ArbolN<Elemento>::obtPadre(Elemento key) const
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
            cout<<aux->obtInfo()<<endl;
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
list<Elemento> ArbolN<Elemento>::Preorden() const
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
list<Elemento> ArbolN<Elemento>::Postorden() const
{
    list<Elemento> post;

    this->recorridoPostorden(this->nodoRaiz, post);

    return post;
}






/* 

template <class Elemento >
void ArbolN<Elemento>::primos(Elemento key)
{
    list<NodoArbolN<Elemento> *> hijos;// Una lista de NODOS que sera por la cual nos vamos a mover para obtener nuestros nodo por nivel
    NodoArbolN<Elemento> *aux,*nodopadre,*nodoAbuelo ,*final;//Apuntadores auxiliares
    int nivel, auxN;            //contadores de nivel
    Elemento padre, abuelo;                        //auxiliares para obtener el nodo padre y el abuelo
    padre=this->obtPadre(key);
    abuelo=this->obtPadre(padre);
    cout<<"Padre: "<<padre<<endl;
    cout<<"Abuelo "<<abuelo<<endl;
    nodopadre=this->encontrarNodo(this->nodoRaiz,padre);//
    nodoAbuelo=this->encontrarNodo(this->nodoRaiz,abuelo);
    hijos.push_back(nodoAbuelo);                    //El comportamiento de esta lista es como una cola. Inicializamos el nodo con el abuelo ya que es el ancestro comun de todos los tios
    nivel=0;                                        //llegaremos hasta el tercer nivel puesto que al tercer nivel se encuentran los primos
    while(!hijos.empty())//mientras la lista de nodos no sea vacia y el nivel sea menor a 2
    {
        auxN=this->cantidadHijos(hijos.front());//obtenemos la cantidad de hijos del Abuelo
        aux = hijos.front()->obtIzq();//obtenemos el hijo del nodo que esta en el frente de nuestra lista
        while(aux != NULL)//mientras existan hijos de ese nodo en el que nos encontramos
        {
            //if(aux==nodopadre)//como queremos obviar los nodos hijos del padre eso nos dejara unicamente con los nodos primos y tios
            //{
            //    aux = aux->obtDer();//nos movemos al hermano cuando llegamos al nodo padre
            //}
            hijos.push_back(aux);//encolamos el en la lista de Hijos
            //if(nivel==1)//si el nodo esta en el nivel 1 significa que es un primo asi que lo imprimimos
            //{
                cout<<aux->obtInfo()<<", ";
                cout<< "Auxiliar de nivel "<<auxN<<" ";
                cout<< "Nivel: "<<nivel<<" ";
            //}
            final=aux;//obtenemos este puntero para saber quien es el hijo del nodo 
            aux = aux->obtDer();//nos movemos al hermano
            if(hijos.front()==nodoAbuelo)//si nos encontramos al nivel 0,es decir el nivel 1 
            {
                if(auxN==1)//cuando solo nos quede un valor en el contador de hijos aumentamos el nivel 
                {
                    nivel+=1;
                }
                auxN-=1;//restamos uno al contador
            }
        }
        //if(nivel>0)
        //{
            //cout<<"Hijos de "<< this->obtPadre(final->obtInfo())<<endl;// decimos de quien es hijo los nodos que acabos de ver
        //}
        hijos.pop_front();// nos movemos al proximo nivel
        if(auxN==1)//cuando solo nos quede un valor en el contador de hijos aumentamos el nivel 
            {
                nivel+=1;      
            }
        auxN-=1;  
        cout<<"Ese fue el nivel: "<<nivel<<endl;
          
       
    }
}
*/





















































#endif