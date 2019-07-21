#include "Arbin.h"
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    Arbin<int> tree, tree2, tree3;
    int n,padre,hijo,m;
    ifstream file;
    ofstream sal;
    list<int> in, pre, post;
    sal.open("in.txt");
    file.open("casos.txt");
    file >> m;
    srand(time(NULL));
    for(int j= 1; j<= m; j++)
    {
        file >> n;
        file >> padre;
        tree.insertarNodo(padre);
        for(int i = 1; i <= n-1; i++)
        {
            file >> padre >> hijo;
            tree.insertarNodo(padre,hijo);
        }
        j > 1 ? sal <<"\n" << n : sal << n;
        in = tree.inorden();
        if(rand()%2 == 0)
        {
            sal << "\nINORDEN ";
            for(auto it = in.begin(); it != in.end(); it++)
            {
                sal << *it << " ";
            }
            if(rand() % 2 == 0)
            {
                pre = tree.preorden();
                sal << "\nPREORDEN ";
                for(auto it = pre.begin(); it != pre.end(); it++)
                {
                    sal << *it << " ";
                }
            }
            else{
                pre = tree.postorden();
                sal << "\nPOSTORDEN ";
                for(auto it = pre.begin(); it != pre.end(); it++)
                {
                    sal << *it << " ";
                }
            }
        }
        else
        {
            if(rand() % 2 == 0)
            {
                pre = tree.preorden();
                sal << "\nPREORDEN ";
                for(auto it = pre.begin(); it != pre.end(); it++)
                {
                    sal << *it << " ";
                }
            }
            else{
                pre = tree.postorden();
                sal << "\nPOSTORDEN ";
                for(auto it = pre.begin(); it != pre.end(); it++)
                {
                    sal << *it << " ";
                }
            }
            sal << "\nINORDEN ";
            for(auto it = in.begin(); it != in.end(); it++)
            {
                sal << *it << " ";
            }
        }
    }    
}