#include "Arbin.h"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    Arbin<int> tree, tree2, tree3;
    int n,padre,hijo;
    ifstream file;
    file.open("casos.txt");
    file >> n;
    file >> padre;
    tree.insertarNodo(padre);
    for(int i = 1; i <= n-1; i++)
    {
        file >> padre >> hijo;
        tree.insertarNodo(padre,hijo);
    }
    
    list<int> t = tree.inorden();
    
    tree2 = tree.obtHi();
    tree3 = tree.obtHd();
    
    list<int> in2 = tree3.inorden();
    n = 0;
    cout << "\n";
    list<int> l2;
    for(auto it = t.begin(); *it != 1; it++)
    {
        ;
    }
    cout << "\n\n";
    for(auto it = in2.begin(); it != in2.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\n"<<tree3.obtPeso() << " " << n;

}