#include <list>
#include <vector>
#include<bits/stdc++.h>
const int MAXNODOS = 20; 
const int MAXHIJOS = 3;
using std::list;
using namespace std;

int main()
{
    int padre = 1, n_nodos = 0, nodos, hijo, nhijos, i = 0, act;
    bool hoja = false; //para que el padre tenga 1 o mas hijos
    unordered_set<int> numeros_usados; //contenedor para los numeros usados en una rama
    ofstream file;
    queue<int> q;
     
    file.open("casos.txt");
    q.push(padre);
    
    srand(time(NULL));   
    nodos = 1 + rand()%MAXNODOS;
    file << nodos + 1<<"\n1\n";
  
   while(n_nodos < nodos)
    {
       //Generamos un numero aleatorios de hijos para el nodo actual  
        //Nos hemos quedado sin nodos que procesar, procesamos el anterior
        if(q.empty()) q.push(act); 
        nhijos = rand() % MAXHIJOS;
        nhijos = nhijos + n_nodos > nodos ? nodos - n_nodos : nhijos;
        
        n_nodos += nhijos;
        
        //Se procesa el nodo actual de la cola
        act = q.front();
        q.pop();
        
        for(int j = 1; j <= nhijos; j++)
        {
            //Generamos un hijo aleatorio que no este entre los ya usados. 
            do
            {       
                hijo = 1 + rand()%100;
            }
            while(numeros_usados.find(hijo) != numeros_usados.end());
            numeros_usados.insert(hijo); //El numero lo marcamos como usado
            q.push(hijo); //Se inserta un puntero debido a que necesitamos una referencia parainsertar luego           
            file << act << " " << hijo << "\n";
        }
        if(!numeros_usados.empty()) numeros_usados.clear();
        i++;
    }
    if(n_nodos < nodos)
    {
        cout << "\nUps ha habido un problema, por favor sustiuye el primer valor del archivo por" << i;
    }
}