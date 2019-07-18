#include <iostream>
#include "NodoArbolN.h"
#include "ArbolN.h"
#include <list>

using std::list;
using namespace std;
int main()
{
    
    ArbolN<long int> arbolito,arbolito2;
    arbolito.InsertarRaiz(0);
    long int i,j;
    for(i=1;i<100;i++)
    {
        for(j=i*6;j<100;j++)
        {
            arbolito.InsertarElemento(i,j);
        }
    }
    for(i=37;i<100;i++)
    {
        for(j=i*6;j<100;j++)
        {
            arbolito.InsertarElemento(i,j);
        }
    }
    for(i=60;i<100;i++)
    {
        for(j=i*6;j<100;j++)
        {
            arbolito.InsertarElemento(i,j);
        }
    }
    arbolito2=arbolito;
    cout<<(arbolito2==arbolito)<<endl;

   
    //arbolito.primos("Jesus");
  
    


    

    

}
