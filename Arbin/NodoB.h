#ifndef NODOB_H
#define NODOB_H
#include <stddef.h>
template <class Elemento>
class NodoB
{
private:
   Elemento info;
   NodoB* hi;
   NodoB* hd;
public:
    NodoB();
    NodoB(Elemento e);
    NodoB* obtHd();
    NodoB* obtHi();
    Elemento obtInfo();
    void modHi(NodoB<Elemento> *ptr);
    void modHd(NodoB<Elemento> *ptr);
    void modInfo(Elemento e);
};

template <class Elemento>
NodoB<Elemento>::NodoB()
{
    this->hi = NULL;
    this->hd = NULL;
}

template <class Elemento>
NodoB<Elemento>::NodoB(Elemento e)
{
    this->info = e;
    this->hi = NULL;
    this->hd = NULL;
}

template <class Elemento>
NodoB<Elemento>* NodoB<Elemento>::obtHd()
{
    return this->hd;
}

template <class Elemento>
NodoB<Elemento>* NodoB<Elemento>::obtHi()
{
    return this->hi;
}

template <class Elemento>
Elemento NodoB<Elemento>::obtInfo()
{
    return this->info;
}

template <class Elemento>
void NodoB<Elemento>::modHd(NodoB<Elemento>* ptr)
{
    this->hd = ptr;
}

template <class Elemento>
void NodoB<Elemento>::modHi(NodoB<Elemento>* ptr)
{
    this->hi = ptr;
}

template <class Elemento>
void NodoB<Elemento>::modInfo(Elemento e)
{
    this->info = e;
}
#endif