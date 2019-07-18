#include <iostream>
#include "NodoArbolN.h"
#include "ArbolN.h"
#include <list>

using std::list;
using namespace std;
int main()
{
    
ArbolN<string> arbolito;
arbolito.InsertarRaiz("papa");

arbolito.InsertarElemento("Maria","Luis");
arbolito.InsertarElemento("Maria","Ana");
arbolito.InsertarElemento("Maria","Jose");
arbolito.InsertarElemento("Luis","Miguel");
arbolito.InsertarElemento("Luis","Jesus");
arbolito.InsertarElemento("Ana","Patricia");
arbolito.InsertarElemento("Jose","Alejandra");
arbolito.InsertarElemento("Jose","Carlos");
arbolito.InsertarElemento("Jose","Andreina");
arbolito.primos("Jesus");

/* 
arbolito.InsertarElemento("Luis","Pedro");
arbolito.InsertarElemento("Luis","Ana");
arbolito.InsertarElemento("Luis","Maria");
arbolito.InsertarElemento("Pedro","Alejandra");
arbolito.InsertarElemento("Alejandra","Antonio");
arbolito.InsertarElemento("Alejandra","Carlos");
arbolito.InsertarElemento("Ana","Diana");
arbolito.InsertarElemento("Ana","Jose");
arbolito.InsertarElemento("Diana","Lorena");
arbolito.primos("Lorena");
*/  
  
    

  
    


    

    

}
