#include <iostream>
#include "Arbin.h"

using namespace std;
void leer(list<int> &l,const int n);
int main(){

    Arbin<int> arbol;
    list<int> inorden,postorden,preorden;
    int n, i= 0;
	string modo1;
    while(cin >> n) //En esta verificamos si hay EOF de stdin y a la vez se lee el valor su lo hay
    {
		i++;        
		for(int j = 1; j <= 2; j++)
		{
			cin >> modo1;
		    if(modo1 == "PREORDEN")
		    {
		        leer(preorden,n);
		    }
		    else if(modo1 == "INORDEN")
		    {
		       leer(inorden,n);
		    }
		    else
		    {
		       leer(postorden,n);
		    }		
		}
		 !preorden.empty() ? arbol.leerPreorden(preorden,inorden) : arbol.leerPostorden		(postorden,inorden);			
    	cout << "El diametro del arbol #"<< i << " es " << arbol.diametro() <<".\n";
		}
 
    return 0;
}
//Simple funcion utilitaria para leer listas
void leer(list<int> &l, const int n)
{
    int x;
    for(int i = 1; i <= n; i++)
    {  
        cin >> x;
        l.push_back(x);
    }
    
}