#include <iostream>
#include "ArbolB.h"

void llenado(list<int> &, int);


//***********************************************************************||| INICIO DEL CALCULO DEL DIAMETRO |||*************************************************************************
int main () {

    ArbolB<int> A;
    list<int> l1, l2;
    int result, n, cont;
    string orden1, orden2;
    cont=0;

    while(cin >> n){                //Mientras siga recibiendo peso

        cont++;

        cin >> orden1;              //Se toma las listas del arbol
        llenado(l1, n);
        cin >> orden2;
        llenado(l2, n);

        if (orden1 =="PREORDEN")    //Se busca que tipo de listas son y se crea el arbol
            A.llenarPreIn(l1,l2);

        else if(orden1 =="POSTORDEN")
            A.llenarPostIn(l1, l2);

        else if(orden2 =="PREORDEN")
            A.llenarPreIn(l2,l1);

        else
            A.llenarPostIn(l2,l1);
        
        result=A.obtDiametro();     //Se calcula el diametro en ArbolB.h

        cout<<"El diametro del arbol #"<<cont<<" es "<< result <<"."<<endl; //Se imprime el resultado

        l1.clear(); //Se vacian las listas para tomar dos nuevas en la proxima iteracion
        l2.clear();
    }
    
    return 0;
}

//***********************************************************************||| FIN DEL CALCULO DEL DIAMETRO |||*************************************************************************


//*********************************************************************************| IMPLEMENTACION |********************************************************************************

void llenado(list<int> & lista, int n){

    int i, valor;

    for (i=0; i<n; i++){    //Recorrido de la fila del archivo con los valores
        cin>>valor;
        lista.push_back(valor);
    }
}