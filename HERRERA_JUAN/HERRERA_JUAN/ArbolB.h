#ifndef ARBOLB_H
#define ARBOLB_H
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <list> 
#include <iterator> 
#include "Nodo.h"
using namespace std;

//***********************************************************************||| INICO ARBOL BINARIO |||*************************************************************************
template <class T>
class ArbolB{

	protected:
//||| ATRIBUTOS |||
		Nodo<T> *raiz;
		int peso, arcos;

//||| METODOS PROTEGIDOS |||

		//| IMPLEMENTACION BASE |
		void copiar(Nodo<T> *base, Nodo<T> **copia, int &cont); 	//Copiar Arbol
		void vaciar(Nodo<T> *act, int &cont);						//Vaciar Arbol
		void obtAltura(Nodo<T> *act, int &result);					//Obtener altura arbol
	
		//| LLENADO |
		void llenarPreIn(Nodo<T> **act, list <T> &pre, list <T> in);
		void llenarPostIn(Nodo<T> **act, list <T> &post, list <T> in);
		
		//| RECORRIDOS |
		void postorden(Nodo<T> *act, list <T> &result);
		void preorden(Nodo<T> *act, list <T> &result);		
		void inorden(Nodo<T> *act, list <T> &result);	

		//| APUNTADORES |
		void apuntadorA(T element, Nodo<T> *act, Nodo<T> **result, bool &encontrado);	
		void apuntadorAlPadre(T element, Nodo<T> *act, Nodo<T> **result, bool &encontrado, bool &marcado);

		//| IMPRESION |
		void printPostorden(Nodo<T> *act); 	
		void printPreorden(Nodo<T> *act);		
		void printInorden(Nodo<T> *act);
		void print(Nodo<T> *p, int id);

		//| METODO PARTICULAR DE EJERCICIO |
		void obtDiametro(Nodo<T> *act, int &mayor, int &result);

	public:
//||| METODOS PRUBLICOS |||

		//| CONSTRUCTORES |
		ArbolB();
		ArbolB(const ArbolB<T> &base);

		//| METODOS BASE |
		T obtRaiz();
		int obtPeso();
		int obtArcos();
		int obtAltura();
		int obtAltura(T element);
		bool esNulo();
		bool esHoja();
		void insertarRaiz(T);
		void insertarHI(const ArbolB<T> &a);
		void insertarHD(const ArbolB<T> &a);
		void copiar(const ArbolB<T> &base);
		void vaciar();
		ArbolB<T> obtHI();
		ArbolB<T> obtHD();

		//| METODOS UTILITARIOS |
		void nuevoVertice(T padre, bool HI_HD, T nuevo);
		void insertarHI(T);
		void insertarHD(T);

		//| LLENADO |
		void llenarPreIn(list <T> pre, list <T> in);
		void llenarPostIn(list <T> post, list <T> in);

		//| RECORRIDOS |
		list <T> postorden();
		list <T> preorden();
		list <T> inorden();

		//| IMPRESION |
		void printPostorden();
		void printPreorden();
		void printInorden();
		void print();

		//| SOBRECARGA DE OPERADORES |
		ArbolB<T> operator =(const ArbolB<T> &base);

		//| ELIMINAR ARBOL |
		~ArbolB();

		//| METODO PARTICULAR DE EJERCICIO |
		int obtDiametro();
};
//***********************************************************************||| FIN ARBOL BINARIO |||*************************************************************************


///***************************************************************************| APUNTADORES |****************************************************************************

template <class T>
void ArbolB<T>::apuntadorA(T element, Nodo<T> *act, Nodo<T> **result, bool &encontrado){

	if(act!=NULL && !encontrado){

		if(element==act->obtInfo()){

			encontrado=true;
			*result=act;

		}else{

			this->apuntadorA(element, act->obtHI(), result, encontrado);
			this->apuntadorA(element, act->obtHD(), result, encontrado);
		}
	}
}

template <class T>
void ArbolB<T>::apuntadorAlPadre(T element, Nodo<T> *act, Nodo<T> **result, bool &encontrado, bool &marcado){
	
	if(act!=NULL){

		if(act->obtInfo()==element){
			encontrado=true;
		
		}else{

			this->apuntadorAlPadre(element, act->obtHI(), result, encontrado, marcado);

			if(!encontrado){
				this->apuntadorAlPadre(element, act->obtHD(), result, encontrado, marcado);
			}

			if(encontrado && !marcado){

				marcado=true;
				*result=act;
			}
		}
	}
}

//*******************************************************************************| CONSTRUCTORES |****************************************************************************

template <class T>
ArbolB<T>::ArbolB(){		//Creacion arbol nulo
	
	this->peso=0;
	this->arcos=0;
	this->raiz=NULL;
}

template <class T>
ArbolB<T>::ArbolB(const ArbolB<T> &base){		//Creacion arbol desde una base
	
	this->raiz=NULL;
	this->peso=0;
	this->arcos=0;
	this->copiar(base);
}


//********************************************************************************| METODOS BASE |****************************************************************************

template <class T>
T ArbolB<T>::obtRaiz(){
	return this->raiz->obtInfo();
}

template <class T>
int ArbolB<T>::obtPeso(){	
	return this->peso;
}

template <class T>
int ArbolB<T>::obtArcos(){
	return this->arcos;
}

template <class T>
int ArbolB<T>::obtAltura(){

	int result;
	this->obtAltura(this->raiz, result);
	return result;
}

template <class T>
int ArbolB<T>::obtAltura(T element){

	int result;
	Nodo<T> *aux;
	bool band;

	this->apuntadorA(element, this->raiz, &aux, band);
	this->obtAltura(aux, result);
	return result;
}

template <class T>
bool ArbolB<T>::esNulo(){
	return this->raiz==NULL;
}

template <class T>
bool ArbolB<T>::esHoja(){		//Señalar que es hoja si la raiz no es nula y no posee hijos
	return this->raiz!=NULL && this->raiz->obtHI()==NULL && this->raiz->obtHD()==NULL;
}

template <class T>
void ArbolB<T>::obtAltura(Nodo<T> *act, int &result){
	int alturaI, alturaD;

	if(act!=NULL){

		this->obtAltura(act->obtHI(), alturaI);
		this->obtAltura(act->obtHD(), alturaD);
		result=max(alturaI, alturaD);
		result += 1;
	
	}else{

		result=-1;
	}
}

template <class T>
void ArbolB<T>::insertarRaiz(T element){

	if(this->raiz==NULL){

		this->raiz=new Nodo<T>;
		this->raiz->modInfo(element);
		this->raiz->modHD(NULL);
		this->raiz->modHI(NULL);
		this->peso=1;

	}else{

		this->raiz->modInfo(element);
	}
}

template <class T>
void ArbolB<T>::insertarHI(const ArbolB<T> &a){

	Nodo<T> *aux, *padre;
	int numero=0;

	padre=this->raiz;
	this->copiar(a.raiz, &aux, numero);

	this->peso += numero;
	numero=0;

	vaciar(padre->obtHI(), numero);

	this->peso -= numero;
	this->arcos=this->peso -1;

	padre->modHI(aux);

}

template <class T>
void ArbolB<T>::insertarHD(const ArbolB<T> &a){

	Nodo<T> *aux, *padre;
	int numero=0;

	padre=this->raiz;
	this->copiar(a.raiz, &aux, numero);

	this->peso += numero;
	numero=0;

	vaciar(padre->obtHD(), numero);

	this->peso -= numero;
	this->arcos=this->peso -1;

	padre->modHD(aux);

}

template <class T>
void ArbolB<T>::copiar(const ArbolB<T> &base){

	Nodo<T> *aux;
	int n;

	n=0;
	this->copiar(base.raiz, &(aux), n);

	this->vaciar();
	this->raiz=aux;

	this->peso=base.peso;
	this->arcos=this->peso - 1;

}

template <class T>
void ArbolB<T>::copiar(Nodo<T> *base, Nodo<T> **copia, int &cont)
{
	Nodo<T> *nuevo, *aux;

	if(base==NULL){

		(*copia)=NULL;
	
	}else{

		nuevo=new Nodo<T>;
		nuevo->modInfo(base->obtInfo());
		(*copia)=nuevo;

		this->copiar(base->obtHI(), &aux, cont);
		(*copia)->modHI(aux);
		this->copiar(base->obtHD(), &aux, cont);
		(*copia)->modHD(aux);

		cont++;
	}
}

template <class T>
void ArbolB<T>::vaciar(Nodo<T> *act, int &cont){

	if(act!=NULL){

		this->vaciar(act->obtHI(), cont);
		this->vaciar(act->obtHD(), cont);
		delete act;
		cont++;
	}
}

template <class T>
void ArbolB<T>::vaciar(){

	int num=0;

	if(!this->esNulo()){
		this->vaciar(this->raiz, num);
	}
}

template <class T>
ArbolB<T> ArbolB<T>::obtHI(){

	ArbolB<T> result;
	Nodo<T> *aux;
	int cont=0;

	this->copiar(this->raiz->obtHI(), &(aux), cont);

	result.raiz=aux;
	result.peso=cont;
	result.arcos=cont - 1;

	return result;
}

template <class T>
ArbolB<T> ArbolB<T>::obtHD(){

	ArbolB<T> result;
	Nodo<T> *aux;
	int cont=0;

	this->copiar(this->raiz->obtHD(), &(aux), cont);

	result.raiz=aux;
	result.peso=cont;
	result.arcos=cont - 1;

	return result;
}


//**************************************************************************| METODOS UTILITARIOS |****************************************************************************

template <class T>
void ArbolB<T>::nuevoVertice(T padre, bool HI_HD, T nuevo){

	Nodo<T> *aux, *aux2;
	bool bandera=false;
	int cont=0;

	this->apuntadorA(padre, this->raiz, &aux, bandera);

	if(bandera){

		aux2=new Nodo<T>;
		aux2->modInfo(nuevo);
		aux2->modHD(NULL);
		aux2->modHI(NULL);

		if(HI_HD){

			this->vaciar(aux->obtHI(), cont);
			aux->modHI(aux2);

		}else{

			this->vaciar(aux->obtHD(), cont);
			aux->modHD(aux2);
		}

		this->peso -= cont;
		this->peso++;
		this->arcos++;
	}
}

template <class T>
void ArbolB<T>::insertarHI(T element){

	Nodo<T> *nuevo, *act;

	if(this->raiz!=NULL){
		act=this->raiz;

		if(act->obtHI()==NULL){

			nuevo=new Nodo<T>;
			nuevo->modInfo(element);
			nuevo->modHI(NULL);
			nuevo->modHD(NULL);

			act->modHI(nuevo);

			this->arcos += 1;
			this->peso += 1;

		}else{

			act=act->obtHI();
			act->modInfo(element);
		}

	}
}

template <class T>
void ArbolB<T>::insertarHD(T element){

	Nodo<T> *nuevo, *act;

	if(this->raiz!=NULL){
		act=this->raiz;

		if(act->obtHD()==NULL){

			nuevo=new Nodo<T>;
			nuevo->modInfo(element);
			nuevo->modHI(NULL);
			nuevo->modHD(NULL);

			act->modHD(nuevo);

			this->arcos += 1;
			this->peso += 1;
		
		}else{

			act=act->obtHD();
			act->modInfo(element);
		}

	}
}
//*******************************************************************************| LLENADO |****************************************************************************

template <class T>
void ArbolB<T>::llenarPreIn(Nodo<T> **act, list <T> &pre, list <T> in){

	Nodo<T> *nuevo, *aux;
	list <T> aux2;
	T element;

	if(!in.empty()){

		element=pre.front();
		nuevo=new Nodo<T>;
		nuevo->modInfo(element);
		pre.pop_front();

		aux2=in;		//Sublista desde el inicio hasta el elemento - 1
		
		while(aux2.back()!=element){
			aux2.pop_back();
		}
		aux2.pop_back();

		this->llenarPreIn(&aux, pre, aux2);
		nuevo->modHI(aux);

		aux2=in;		//Sublista desde el elemento+1 hasta el final
		
		while(aux2.front()!=element){
			aux2.pop_front();
		}
		aux2.pop_front();

		this->llenarPreIn(&aux, pre, aux2);
		nuevo->modHD(aux);

		*act=nuevo;
	}else{
		*act=NULL;
	}
	aux2.clear();
}

template <class T>
void ArbolB<T>::llenarPreIn(list <T> pre, list <T> in){

	Nodo<T> *aux;
	this->llenarPreIn(&aux, pre, in);
	this->raiz=aux;
	this->peso=pre.size();
	this->arcos=this->peso -1;
}

template <class T>
void ArbolB<T>::llenarPostIn(Nodo<T> **act, list <T> &post, list <T> in){

	Nodo<T> *nuevo, *aux;
	list <T> aux2;
	T element;
	int pos;

	if(!in.empty()){

		element=post.front();
		nuevo=new Nodo<T>;
		nuevo->modInfo(element);
		post.pop_front();

		aux2=in;		//Sublista desde el elemento+1 hasta el final
		
		while(aux2.front()!=element){
			aux2.pop_front();
		}
		aux2.pop_front();

		this->llenarPostIn(&aux, post, aux2);
		nuevo->modHD(aux);


		aux2=in;		//Sublista desde el inicio hasta el elemento - 1
		
		while(aux2.back()!=element){
			aux2.pop_back();
		}
		aux2.pop_back();


		this->llenarPostIn(&aux, post, aux2);
		nuevo->modHI(aux);

		*act=nuevo;

	}else{

		*act=NULL;
	}
	aux2.clear();
}

template <class T>
void ArbolB<T>::llenarPostIn(list <T> post, list <T> in){

	Nodo<T> *aux;

	post.reverse();

	this->llenarPostIn(&aux, post, in);

	this->raiz=aux;
	this->peso=post.size();
	this->arcos=this->peso - 1;
}


//***************************************************************************| RECORRIDOS |****************************************************************************

template <class T>
void ArbolB<T>::postorden(Nodo<T> *act, list <T> &result){

	if(act!=NULL){

		this->postorden(act->obtHI(), result);
		this->postorden(act->obtHD(), result);
		result.push_front(act->obtInfo());
	}
}

template <class T>
list <T> ArbolB<T>::postorden(){

	list <T> result;

	this->postorden(this->raiz, result);

	result.reverse();

	return result;
}

template <class T>
void ArbolB<T>::preorden(Nodo<T> *act, list <T> &result){

	if(act!=NULL){

		result.push_front(act->obtInfo());
		this->preorden(act->obtHI(), result);
		this->preorden(act->obtHD(), result);
	}
}

template <class T>
list <T> ArbolB<T>::preorden(){

	list <T> result;

	this->preorden(this->raiz, result);

	result.reverse();

	return result;
}

template <class T>
void ArbolB<T>::inorden(Nodo<T> *act, list <T> &result){

	if(act!=NULL){

		this->inorden(act->obtHI(), result);
		result.push_front(act->obtInfo());
		this->inorden(act->obtHD(), result);
	}
}

template <class T>
list <T> ArbolB<T>::inorden(){

	list <T> result;

	this->inorden(this->raiz, result);

	result.reverse();

	return result;
}

//************************************************************************| IMPRESION |****************************************************************************

template <class T>
void ArbolB<T>::printPostorden(){

	this->printPostorden(this->raiz);
	cout << endl;
}

template <class T>
void ArbolB<T>::printPostorden(Nodo<T> *act){

	if(act!=NULL){

		this->printPostorden(act->obtHI());
		this->printPostorden(act->obtHD());
		cout << act->obtInfo() << " ";
	}
}

template <class T>
void ArbolB<T>::printPreorden(){

	this->printPreorden(this->raiz);
	cout << endl;
}

template <class T>
void ArbolB<T>::printPreorden(Nodo<T> *act){

	if(act!=NULL){

		cout << act->obtInfo() << " ";
		this->printPreorden(act->obtHI());
		this->printPreorden(act->obtHD());
	}
}

template <class T>
void ArbolB<T>::printInorden(){
	this->printInorden(this->raiz);
	cout << endl;
}

template <class T>
void ArbolB<T>::printInorden(Nodo<T> *act){

	if(act!=NULL){

		this->printInorden(act->obtHI());
		cout << act->obtInfo() << " ";
		this->printInorden(act->obtHD());
	}
}

template <class T>
void ArbolB<T>::print(Nodo<T> *p, int id){

    if(p!=NULL){

        if(p->obtHD()){
            print(p->obtHD(), id+4);
        }
        if (id){
        	cout << setw(id) << ' ';
        }
        if (p->obtHI()){
			cout<<" /\n" << setw(id) << ' ';
		}

		cout<< p->obtInfo() << "\n ";

        if(p->obtHI()){
            cout << setw(id) << ' ' <<" \\\n";
            print(p->obtHI(), id+4);
        }
    }
}

template <class T>
void ArbolB<T>::print(){
	print(this->raiz, 0);
}


//************************************************************************| SOBRECARGA DE OPERADORES |*********************************************************

template <class T>
ArbolB<T> ArbolB<T>::operator =(const ArbolB<T> &base){

	Nodo<T> *aux;
	int cont=0;


	this->vaciar();
	this->copiar(base.raiz, &aux, cont);
	this->raiz=aux;
	this->peso=base.peso;
	this->arcos=base.arcos;

	return *(this);
}


//*******************************************************************************| ELIMINAR ARBOL |*********************************************************

template <class T>
ArbolB<T>::~ArbolB(){
	this->vaciar();
}


//***********************************************************************| METODO PARTICULAR DE EJERCICIO |*************************************************

template <class T>
int ArbolB<T>::obtDiametro(){		//Llamada publica del metodo que establece las condiciones iniciales del recorrido
	
	if(this->esNulo()){
		return -1;
	}

	int result = 0, mayor = 0;
	this->obtDiametro(this->raiz, mayor, result);
	return result;
}

template <class T>
void ArbolB<T>::obtDiametro(Nodo<T> *act, int &mayor, int &result){

	int mayorI, mayorD;

	if(!act){
		mayor = 0;
	}
	else{

		this->obtDiametro(act->obtHI(), mayorI, result);	//Se obtienen los diametros de los hijos
		this->obtDiametro(act->obtHD(), mayorD, result);

		if(mayorI > mayorD) 								//Se ve cual diametro es mayor y se usa dicho diametro
			mayor = mayorI;
		else
			mayor = mayorD;

		mayor ++;											//Se aumenta en uno al estar agregando al nodo actual

		if(mayorI + mayorD + 1 > result)					//Se crea un nuevo diametro para comparar y se asigna si es el mayor hasta el momento
			result = mayorI + mayorD;
	}
}


#endif