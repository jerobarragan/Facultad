
#ifndef TP_LOLLA_DICCDIG_H
#define TP_LOLLA_DICCDIG_H

#include <vector>
#include "tipos.h"

template<typename T>
class diccDig {
public:
    diccDig();
    diccDig(const diccDig<T>& aCopiar);
    diccDig& operator=(const diccDig& d);
    ~diccDig();
    void definir(const std::pair<Nat , T>&);
    bool definido(const Nat &k) const;
    T & significado(const Nat& k) const;
    T & at(const Nat &k) const;
private:

    struct Nodo {
        std::vector<Nodo*> siguientes;
        T* definicion;
        Nodo();
    };
    Nodo* raiz;
    int _size;
    void _destruirNodos(Nodo* nodo);
    void _copiarNodo(Nodo* destino, Nodo* fuente);
    //bool _esHijoInutil(Nodo* nodo);
    std::vector<int> digitalizar (int key) const;
};

#include "diccDig.hpp"


#endif //TP_LOLLA_DICCDIG_H
