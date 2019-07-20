#include <iostream>
#include "Arbin.h"
#include<bits/stdc++.h>

using namespace std;
ifstream file;
// template <class Elemento>
void mostrar(const list<int> &l);
void leer(list<int> &l,const int n);
int main(){

    Arbin<int> tree, tree2,tree3;
    list<int> path,inorden,postorden,preorden;
    int n;
    char x;
    string modo1, modo2;
    file.open("casos.txt");
    file >> n;
    string in = "INORDEN", pre =  "PREORDEN";
    cout << modo1;
    n = 7;
    for(int i = 1; i<= 1; i++)
    {
        // cin >> modo1;
        // if(modo1.compare(pre) == 0)
        // {
            // leer(preorden,n);
        // }
        // else if((modo1.compare(in) == 0))
        // {
            leer(inorden,n);
        // }
        // else
        // {
            leer(postorden,n);
        // }
        //  cout << modo1;
    }

    !preorden.empty() ? tree.leerPreorden(preorden,inorden) : tree.leerPostorden(postorden,inorden);

    cout << "\n" << tree.diametro() << "\n";
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


void leer(list<int> &l, const int n)
{
    int x;
    for(int i = 1; i <= n; i++)
    {  
        file>> x;
        l.push_back(x);
    }
    
}