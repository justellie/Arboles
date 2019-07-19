#include <iostream>
#include "NodoArbolN.h"
#include "ArbolN.h"
#include <list>
#include<bits/stdc++.h>

using std::list;
using namespace std;
int main()
{
    
    ArbolN<int> arbolito;
    int n,padre,hijo;
    ifstream file;
    file.open("casos.txt");
    file >> n;
    file >> padre;
    arbolito.InsertarRaiz(padre);
    for(int i = 1; i <= n-1; i++)
    {
        file >> padre >> hijo;
        arbolito.InsertarElemento(padre,hijo);
    }
    auto l = arbolito.Preorden();
    cout << "\n";
    for(auto it = l.begin(); it != l.end();it++)
    {
        cout <<*it<<" ";
    }
    /*
    arbolito.InsertarElemento(1,2);
    arbolito.InsertarElemento("Maria",3);
    arbolito.InsertarElemento("Maria",4);
    arbolito.InsertarElemento(2,5);
    arbolito.InsertarElemento(2,6);
    arbolito.InsertarElemento(3,7);
    arbolito.InsertarElemento(4,8);
    arbolito.InsertarElemento(4,"9");
    arbolito.InsertarElemento(4,"10");
    arbolito.primos(6);

    arbolito.InsertarRaiz(1);
    arbolito.InsertarElemento(1,2);
    arbolito.InsertarElemento(1,3);
    arbolito.InsertarElemento(1,4);
    arbolito.InsertarElemento(2,5);
    arbolito.InsertarElemento(2,6);
    arbolito.InsertarElemento(3,7);
    arbolito.InsertarElemento(4,8);
    arbolito.InsertarElemento(4,9);
    arbolito.InsertarElemento(4,10);
    arbolito.primos(6);
   
    */
    cout << "\n"<< arbolito.altura();
}
