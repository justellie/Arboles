#include <iostream>
#include "NodoArbolN.h"
using namespace std;
int main()
{
    NodoArbolN<int> a;
    a.modInfo(5);
    cout<<a.obtInfo()<<endl;

}
