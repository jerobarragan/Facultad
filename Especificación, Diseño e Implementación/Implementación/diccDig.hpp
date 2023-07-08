#include "tipos.h"

template <typename T>
diccDig<T>::diccDig(): _size(0), raiz(new Nodo()){}

template<typename T>
diccDig<T>::Nodo::Nodo() : siguientes(10, nullptr), definicion(nullptr){}

template<typename T>
std::vector<int> diccDig<T>::digitalizar(int key) const
{
    std::vector<int> digitos{};

    while (key >= 10)
    {
        digitos.push_back(key % 10);
        key /= 10;
    }
    digitos.push_back(key);

    return digitos;
}

template<typename T>
void diccDig<T>::definir(const std::pair<Nat, T> & par)
{
    Nodo* actual{raiz};
    int numero {static_cast<int>(par.first)};
    std::vector<int> digitos{digitalizar(numero)};

    for (auto i = digitos.rbegin(); i != digitos.rend(); ++i)
    {
        if (actual->siguientes[*i] == nullptr)
            actual->siguientes[*i] = new Nodo();
        actual = actual->siguientes[*i];
    }

    if (actual->definicion == nullptr)
    {
        _size++;
        actual->definicion = new T (par.second);
    }
    else
        at(par.first) = par.second;
}

template <typename T>
bool diccDig<T>::definido(const Nat &k) const
{
    Nodo* actual {raiz};
    std::vector<int> digitos {digitalizar(static_cast<int>(k))};

    for (auto it {digitos.rbegin()}; it != digitos.rend(); ++it)
    {
        if (actual->siguientes[*it] == nullptr) return false;
        else actual = actual->siguientes[*it];
    }

    return { actual->definicion != nullptr };
}

template <typename T>
T & diccDig<T>::significado(const Nat &k) const
{
    return at(k);
}

template <typename T>
T & diccDig<T>::at(const Nat &k) const
{
    Nodo* actual {raiz};
    std::vector<int> digitos {digitalizar(static_cast<int>(k))};

    for (auto it = digitos.rbegin(); it != digitos.rend(); ++it)
        actual = actual->siguientes[*it];

    return *actual->definicion;
}

template <typename T>
diccDig<T>::~diccDig()
{
    _destruirNodos(raiz);
    _size = 0;
}

template<typename T>
void diccDig<T>::_destruirNodos(Nodo* nodo)
{
    if (nodo == nullptr) return;

    for (Nodo* hijo : nodo->siguientes) {
        if (hijo != nullptr) _destruirNodos(hijo);
    }

    delete nodo->definicion;
    delete nodo;
}

template <typename T>
diccDig<T>::diccDig(const diccDig<T>& aCopiar) : diccDig() { *this = aCopiar;} // Provisto por la cátedra: utiliza el operador asignación para realizar la copia.


template <typename T>
diccDig<T>& diccDig<T>::operator=(const diccDig<T>& d)
{
    _destruirNodos(raiz);
    raiz = new Nodo();
    _copiarNodo(raiz,d.raiz);
    _size = d._size;

    return *this;
}


template<typename T>
void diccDig<T>::_copiarNodo(Nodo* destino, Nodo* fuente)
{
    if (fuente->definicion != nullptr) destino->definicion = new T (*fuente->definicion);

    for (int i = 0; i < 10; i++)
    {
        if (fuente->siguientes[i] != nullptr)
        {
            destino->siguientes[i] = new Nodo();
            _copiarNodo(destino->siguientes[i], fuente->siguientes[i]);
        }
    }
}