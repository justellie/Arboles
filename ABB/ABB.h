#ifndef ABB_H
#define ABB_H
#include "../Arbin/Arbin.h"

template <class Elemento>
class ABB : private Arbin<Elemento>
{
private:
    void eliminarMezcla(NodoB<Elemento> *&node);

public:
    void insertar(Elemento e);
    void eliminar(Elemento e);
    bool buscar(Elemento e);
    Elemento minimo();
    Elemento maximo();
    list<Elemento> inorden() const;
    void findAndDeleteByMerging(const Elemento &el);
    void deleteByMerging(NodoB<Elemento> *&node);
};

template <class Elemento>
void ABB<Elemento>::insertar(Elemento e)
{
    NodoB<Elemento> *x, *y, *nuevo;
    x = this->raiz;
    y = NULL;
    while (x != NULL)
    {
        y = x;
        x = e < x->obtInfo() ? x->obtHi() : x->obtHd();
    }
    nuevo = new NodoB<Elemento>(e);
    if (y == NULL)
    {
        this->raiz = nuevo;
    }
    else if (e < y->obtInfo())
    {
        y->modHi(nuevo);
    }
    else
    {
        y->modHd(nuevo);
    }
}
template <class Elemento>
void ABB<Elemento>::eliminar(Elemento e)
{
}

template <class Elemento>
void ABB<Elemento>::deleteByMerging(NodoB<Elemento> *&node)
{
    NodoB<Elemento> *tmp = node;
    if (node != NULL)
    {
        if (!node->obtHd())       // node has no obtHd() child: its obtHi()
            node = node->obtHi(); // child (if any) is attached to its
        // parent;
        else if (node->obtHi() == 0) // node has no obtHi() child: its obtHd()
            node = node->obtHd();    // child is attached to its parent;
        else
        {                             // be ready for merging subtrees;
            tmp = node->obtHi();      // 1. move obtHi()
            while (tmp->obtHd() != 0) // 2. and then obtHd() as far as
                // possible;
                tmp = tmp->obtHd();
            tmp->modHd(node->obtHd());   // 3. establish the link between // the obtHd()most node of the obtHi()
            // subtree and the obtHd() subtree;
            tmp = node;           // 4.
            node = node->obtHi(); // 5.
        }
        delete tmp; // 6.
    }
}
template <class Elemento>
void ABB<Elemento>::findAndDeleteByMerging(const Elemento &el)
{
    NodoB<Elemento> *node = this->raiz, *prev = 0;
    while (node != NULL)
    {
        if (node->obtInfo() == el)
            break;
        prev = node;
        if (el < node->obtInfo())
            node = node->obtHi();
        else
            node = node->obtHd();
    }
    if (node != NULL && node->obtInfo() == el)
        if (node == this->raiz)
            deleteByMerging(this->raiz);
        else if (prev->obtHi() == node)
        {
            prev = prev->obtHi();
            deleteByMerging(prev);
        }
        else
        {
            prev = prev->obtHd();
            deleteByMerging(prev);
        }
    else if (this->raiz != NULL)
        cout << "element" << el << "is not in the tree\n";
    else
        cout << "the tree is empty\n";
}
template <class Elemento>
list<Elemento> ABB<Elemento>::inorden() const
{
    return this->Arbin<Elemento>::inorden();
}
#endif