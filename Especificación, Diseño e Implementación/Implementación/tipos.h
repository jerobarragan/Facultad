#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>
#include <set>

using Persona = int;
using IdPuesto = int;
using Producto = int;
using Nat = unsigned int;
using Stock = std::map<Producto, Nat>;
using Promociones = std::map<Producto, std::map<Nat, Nat>>;
using Menu = std::map<Producto, Nat>;

struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};

#endif //SOLUCION_TIPOS_H
