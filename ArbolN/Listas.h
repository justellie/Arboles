#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"
#include <iostream>
using namespace std;



template<class Elemento>
class Lista
{

protected:
	//*****************|| ATRIBUTOS ||********************//	
	Nodo<Elemento> *cabeza;				 // La cabeza apunta al inicio de la lista mientras que la cola apunta al fin de la lista para asi hacer mas rapido el insertado al final de la misma
	int longitud;								// Indica la logitud de la cola
public:
	//*****************|| Constructores ||********************//
	 Lista();									 // No recibe ningun parametro
	//*****************|| Destructores||********************//
	~ Lista();
	//*****************|| Metodo Publicos||********************//
	void copiar(const Lista<Elemento>&); 
	bool esVacia();
	int  obtLongitud(); 
	void insertar(Elemento, const int&); 	  //Inserta un elemento segun posicion 
	Elemento consultar(const int&); 	     // retorna el elemento en la posicion (pos) de la Lista
	void print(); 
	void printCriminal();
	void eliminar(int pos);						    //Imprime los valores de una lista
	Elemento menor();
	Elemento mayor();
	void ordenar(bool ascendete);//Ordena de forma ascendente y descendente
	void modificar(Elemento,int);
	bool esta(Elemento); 																		// devuelve si un elemento esta o no	
	void vaciar(); 
	//void mezclarOrdenada(Lista<Elemento>&,Lista<Elemento>&);
	
};

template<class Elemento>
Lista<Elemento>::Lista(){ 
	this->cabeza=NULL;
	this->longitud=0;

}
template<class Elemento>
bool Lista<Elemento>::esVacia(){
	return this->cabeza==NULL;
}
template<class Elemento>
int Lista<Elemento>::obtLongitud(){
	return this->longitud;
}
template<class Elemento>
void Lista<Elemento>::insertar(Elemento e, const int& pos){
	Nodo<Elemento> *nuevo,*aux;
	int i;

	if(pos<0||pos>this->longitud+1)//Si la posicion no es valida lanza un mensaje
	{
		cout<<"Posicion no valida"<<endl;
	}
	else
	{
		nuevo= new Nodo<Elemento>;//De ser la posicion valida se crea un nuevo nodo y se añade el elemento en el campo respectivo
		nuevo->modInfo(e);
		if(pos==0)//Si la posicion es 0
		{
			nuevo->modProx(this->cabeza);//Se apunta el nuevo nodo a la cabeza 
			this->cabeza=nuevo;//Y la cabeza al nuevo nodo
		}
		else//Si no 
		{
			aux=this->cabeza;//Apunta al inicio de la lista
			for(i=1;i<pos;i++)//Me muevo una posicion hasta llegar a la posicion requerida
			{
				aux=(aux->obtProx());
			}
			nuevo->modProx(aux->obtProx());//apunto el nuevo nodo al nodo que corresponde al siguiente del actual
			aux->modProx(nuevo);//apunto el actual al nuevo nodo
			
		}
		this->longitud = this->longitud + 1;//Se suma uno a la logitud
	}

}
template<class Elemento>
Elemento Lista<Elemento>::consultar(const int& pos){
	Nodo<Elemento> *aux;
	int i;
	Elemento resp;

	if (pos<0||pos>this->longitud+1)
	{
		cout<<"Posicion no valida"<<endl;
	}
	else
	{
		aux=this->cabeza;//Apunta al inicio de la lista
		for(i=0;i<pos;i++)//Me muevo una posicion hasta llegar a la posicion requerida
		{
			aux=(aux->obtProx());
		}
		resp=aux->obtInfo();
	}
	return(resp);	
}
template <class Elemento>
void Lista<Elemento>::print()
{
	Nodo<Elemento>* aux;

	aux = this->cabeza;
	while(aux != NULL)
	{
		cout << aux->obtInfo() << " ";
		aux = aux->obtProx();
	}
	cout << endl;
}
template <class Elemento>
void Lista<Elemento>::printCriminal()
{
	Nodo<Elemento>* aux;

	aux = this->cabeza;
	while(aux != NULL)
	{
		cout <<"|" <<aux->obtInfo() << "|"<<"->";
		aux = aux->obtProx();
	}
	cout <<"NULL"<< endl;
}

template <class Elemento>
Elemento Lista<Elemento>::mayor()
{
	Nodo<Elemento> *aux;
	Elemento may;

	aux = this->cabeza;
	may = aux->obtInfo();
	aux = aux->obtProx();

	while(aux!=NULL)
	{
		if(aux->obtInfo()>may)
		{
			may = aux->obtInfo();
		}
		aux = aux->obtProx();
	}

	return may;
}

template <class Elemento>
Elemento Lista<Elemento>::menor()
{
	Nodo<Elemento> *aux;
	Elemento men;

	aux = this->cabeza;
	men = aux->obtInfo();
	aux = aux->obtProx();

	while(aux!=NULL)
	{
		if(aux->obtInfo()<men)
		{
			men = aux->obtInfo();
		}
		aux = aux->obtProx();
	}

	return men;
}

template <class Elemento>
void Lista<Elemento>::ordenar(bool ascendete)//Este algoritmo es como el algoritmo de ordenamiento burbuja
{
	Nodo<Elemento> *aux1, *aux2;
	Elemento elemento;
	int i, j;

	if(ascendete)
	{
		for(i=0;i<this->longitud -1 ;i++)
		{
			aux1 = this->cabeza;
			aux2 = aux1->obtProx();

			for(j=0; j < (this->longitud - i -1); j++)
			{
				if(aux1->obtInfo() > aux2->obtInfo())
				{
					elemento = aux1->obtInfo();
					aux1->modInfo(aux2->obtInfo());
					aux2->modInfo(elemento);
				}
				aux1 = aux2;
				aux2 = aux2->obtProx();
			}
		}
	}
	else
	{
		for(i=0;i<this->longitud -1;i++)
		{
			aux1 = this->cabeza;
			aux2 = aux1->obtProx();

			for(j=0; j < (this->longitud - i -1); j++)
			{
				if(aux1->obtInfo() < aux2->obtInfo())
				{
					elemento = aux1->obtInfo();
					aux1->modInfo(aux2->obtInfo());
					aux2->modInfo(elemento);
				}
				aux1 = aux2;
				aux2 = aux2->obtProx();
			}
		}
	}
}

template <class Elemento>
void Lista<Elemento>::eliminar(int pos)
{
	Nodo<Elemento> *aux, *aux2;
	int i;

	if(pos < 0 || pos >= this->longitud+1)
	{
		return;
	}
	else
	{
		aux = this->cabeza;

		if(pos == 0)
		{
			this->cabeza = aux->obtProx();
			delete aux;
		}
		else
		{
			for(i = 1; i < pos; i++)
			{
				aux = aux->obtProx();
			}
			
			aux2 = aux->obtProx();
			aux->modProx(aux2->obtProx());
		
			delete aux2;
		}
		this->longitud = this->longitud - 1;
	}
}



template <class Elemento>
void Lista<Elemento>::modificar(Elemento e, int pos)
{
	Nodo<Elemento> *p;
	int i;

	if(pos>=0 && pos < this->longitud)
	{
		p = this->cabeza;
		for(i=0;i<pos;i++)
		{
			p = p->obtProx();
		}
		p->modInfo(e);
	}
	else
	{
		"** ERROR DE INDICES EN MODIFICAR UN ELEMENTO DE LA SIGUIENTE LISTA ** -> ";
		this->print();
	}
}

template <class Elemento>
bool Lista<Elemento>::esta(Elemento e)
{
	Nodo<Elemento>* aux;
	bool result;

	aux = this->primero;
	result = false;

	while(!result && aux != NULL)
	{
		if(aux->obtInfo() == e)
		{
			result = true;
		}
		else
		{
			aux = aux->obtProx();
		}
	}

	return result;
}

template <class Elemento>
void Lista<Elemento>::vaciar()
{
  Nodo<Elemento> *aux;

  aux = this->cabeza;
  while(this->cabeza!= NULL)
  {
    this->cabeza= (this->cabeza)->obtProx();
    delete aux;
    aux = this->cabeza;
  }

  	this->longitud = 0;

}



template <class Elemento>
Lista<Elemento>::~Lista()
{
	this->vaciar();
} 
#endif