#include <iostream>
#include "NodoArbolN.h"
#include "ArbolN.h"
#include "Listas.h"
#include <list>

using std::list;
using namespace std;
int main()
{
    
    ArbolN<int> arbolito;
    int padre;
    arbolito.esta(1);
    arbolito.InsertarElemento(1);
    arbolito.InsertarElemento(2,88);
    arbolito.InsertarElemento(2,45);
    arbolito.InsertarElemento(2,878);
    arbolito.esta(1);
    arbolito.InsertarElemento(1,6);
    arbolito.esta(6);
    arbolito.InsertarElemento(1,7);
    arbolito.InsertarElemento(6,8);
    arbolito.InsertarElemento(6,800);
    arbolito.InsertarElemento(7,3);
    arbolito.esta(2);
    arbolito.InsertarElemento(8,4);
    arbolito.primos(45);
  
    


    

    

}
