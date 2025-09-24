#ifndef COLA_H
#define COLA_H

#include <functional>
#include <cstddef>
using namespace std;

template<typename T>
class Cola {
    struct Nodo {
        T dato;
        Nodo* sig;
    };
    Nodo* puntero = nullptr;
    Nodo* ult = nullptr;

    // Recursivos privados
    static void printRecImpl(Nodo* n, function<void(const T&)> printer){
        if(!n) return;
        printer(n->dato);
        printRecImpl(n->sig, printer);
    }
    static size_t sizeRecImpl(Nodo* n){
        return n ? (1 + sizeRecImpl(n->sig)) : 0;
    }
    static void clearRecImpl(Nodo*& n){
        if(!n) return;
        clearRecImpl(n->sig);
        delete n;
        n = nullptr;
    }
    static bool searchRecImpl(Nodo* n, function<bool(const T&)> pred){
        if(!n) return false;
        if(pred(n->dato)) return true;
        return searchRecImpl(n->sig, pred);
    }

public:
    Cola() = default;
    ~Cola(){ clearRec(); }

    bool empty() const { return puntero == nullptr; }

    void enqueue(const T& v){
        Nodo* nuevo = new Nodo{v, nullptr};
        if(!ult) {
            puntero = ult = nuevo;
        }
        else {
            ult->sig = nuevo; ult = nuevo;
        }
    }


    void enqueueFront(const T& v){
        Nodo* nuevo = new Nodo{v, puntero};
        puntero = nuevo;
        if(!ult)
            ult = puntero;
    }

    bool dequeue(T& out){
        if(!puntero)
            return false;

        Nodo* aux = puntero;
        out = aux->dato;
        puntero = puntero->sig;
        if(!puntero)
            ult = nullptr;
        delete aux;
        return true;
    }

    void printRec(function<void(const T&)> printer) const {
        printRecImpl(puntero, printer);
    }
    size_t sizeRec() const {
        return sizeRecImpl(puntero);
    }
    void clearRec() {
        clearRecImpl(puntero);
        ult = nullptr;
    }
    bool searchRec(function<bool(const T&)> pred) const {
        return searchRecImpl(puntero, pred);
    }
};

#endif // COLA_H
