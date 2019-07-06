#include <iostream>
#include "NodoArbolN.h"
#include "ArbolN.h"
#include "Listas.h"
using namespace std;
int main()
{
    
    ArbolN<int> arbolito;
    arbolito.esta(1);
    arbolito.InsertarElemento(1);
    arbolito.InsertarElemento(2,88);
    arbolito.esta(1);
    arbolito.InsertarElemento(1,6);
    arbolito.esta(6);
    arbolito.InsertarElemento(1,7);
    arbolito.InsertarElemento(6,8);
    arbolito.InsertarElemento(7,3);
    arbolito.esta(2);
    arbolito.InsertarElemento(8,4);

    

    

}
