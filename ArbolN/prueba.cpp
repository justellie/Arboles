#include <list>
#include <vector>
#include<bits/stdc++.h>
const int MAXNODOS = 20; 
const int MAXHIJOS = 5;
using std::list;
using namespace std;
class Nodo
{
    private:
        int info;
        list<Nodo> *son;
    public:
        Nodo()
        {
            this->info = 0;
            this->son = new list<Nodo>;
        }
        Nodo(int e)
        {
            this->info = e;
            this->son = new list<Nodo>;
        }
        
        void addSon(int n)
        {
            Nodo var = Nodo(n);
            this->son->push_back(var);
        }
        int getInfo()
        {
            return this->info;
        }
        list<Nodo>* getSon()
        {
            return this->son;
        }
};


int main()
{
    Nodo *ptr = new Nodo(1);
    int n_nodos = 1;
    unordered_set<int> numeros_usados;
    ofstream file;
    queue<Nodo *> q;
    file.open("casos.txt");
    n_nodos = 0;
    int hijo;
    Nodo *ptr_hijo;

    q.push(ptr);
    srand(time(NULL));  
    
    int nodos = 1 + rand()%MAXNODOS;
    int nhijos;
    file << nodos + 1<<"\n1\n";

    while(n_nodos < nodos)
    {
       //Generamos un numero aleatorios de hijos para el nodo actual  
        nhijos = rand() % MAXHIJOS;      
        
        nhijos = nhijos + n_nodos > nodos ? nodos - n_nodos : nhijos;
        
        n_nodos += nhijos;
        
        //Se procesa el nodo actual de la cola
        Nodo *act = q.front();
        q.pop();
        
        for(int j = 1; j <= nhijos; j++)
        {
            //Generamos un hijo aleatorio que no este entre los ya usados. 
            do
            {       
                hijo = 1 + rand()%100;
            }
            while(numeros_usados.find(hijo) != numeros_usados.end());
           
            ptr_hijo = new Nodo(hijo);
            act->addSon(hijo); //Se añade el hijo al nodo actual
            numeros_usados.insert(hijo); //El numero lo marcamos como usado
            q.push(ptr_hijo); //Se inserta un puntero debido a que necesitamos una referencia parainsertar luego           
            file << act->getInfo() << " " << hijo << "\n";
        }
        if(!numeros_usados.empty()) numeros_usados.clear();
    }
}