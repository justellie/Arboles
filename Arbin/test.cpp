#include <iostream>
#include "Arbin.h"

using namespace std;

// template <class Elemento>
void mostrar(const list<char> &l);
void leer(list<char> &l,const int n);
int main(){

    Arbin<char> tree, tree2,tree3;
    list<char> path,inorden,postorden;
    int n;
    char x;
    
    cin >> n;
    leer(postorden,n);
    leer(inorden,n);
    
    tree.leerPostorden(postorden,inorden);
    path = tree.niveles();
    mostrar(path);
    tree2 = tree.obtHi();
    tree3 = tree.obtHd();
    inorden = tree2.inorden();
    mostrar(inorden);
    inorden = tree3.inorden();
    mostrar(inorden);
    return 0;
}


// template <class Elemento>
void mostrar(const list<char> &l)
{
    cout << "\n";
    for(list<char>::const_iterator it = l.begin(); it != l.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\n";
}


void leer(list<char> &l, const int n)
{
    char x;
    for(int i = 1; i <= n; i++)
    {  
        cin >> x;
        l.push_back(x);
    }
    
}