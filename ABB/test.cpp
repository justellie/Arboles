#include <iostream>
#include<bits/stdc++.h>
#include "ABB.h"
using namespace std;
int main()
{
    ABB<int> t;
    int n, x;
    srand(time(NULL));
    for(int i = 1; i <= 5; i++)
    {
        t.insertar(rand()%100);
    }
    auto l = t.inorden();
    cout << "\n";
    for(list<int>::const_iterator it = l.begin(); it != l.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\n";
    cin >> n;
    t.findAndDeleteByMerging(n);
    l = t.inorden();
    cout << "\n";
    for(list<int>::const_iterator it = l.begin(); it != l.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\n";
}