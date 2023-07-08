#include <utility>
#include "lollapatuza.h"

//Generador equivalente iCrearLolla
lollapatuza::lollapatuza(const std::map<IdPuesto, puesto> &ps, const std::set<Persona>& as) : _puestos(ps), _conjPersonas(as) /*Copia de conjLineal O(A)*/
{
    for (Persona idPersona : _conjPersonas)
    {
        _personas.insert({idPersona, infoPersona {0, {}}});
        _masGastadores.insert({{0, idPersona}, idPersona});
    }
}

lollapatuza &lollapatuza::operator=(const lollapatuza &l)
{
    _puestos = l._puestos;
    _conjPersonas = l._conjPersonas;
    _personas = l._personas;
    _masGastadores = l._masGastadores;

    return *this;
}

void lollapatuza::vender(const IdPuesto &pi, const Persona &a, const Producto &item, const Nat &cant)
{
    puesto& puestoP {_puestos.at(pi)};
    Nat gastoVenta {puestoP.vender(a, item, cant)};

    infoPersona& info {_personas.at(a)};
    Nat gastoActual {info.gastoPersona};

    Nat nuevoGasto {gastoActual + gastoVenta};
        // Actualizar masGastadores
    _masGastadores.erase({-gastoActual, a});
    _masGastadores.insert({{-nuevoGasto, a}, a});
    info.gastoPersona = nuevoGasto;

    if (!puestoP.obtenerDescuento(item, cant))
    {
        if (!info.comprasSinDescuento.count(item))
            info.comprasSinDescuento.insert({item,{}});
        std::map<IdPuesto, std::pair<Nat, puesto*>>& comprasHackeables {info.comprasSinDescuento.at(item)};

        if (!comprasHackeables.count(pi))
            comprasHackeables.insert({pi ,{0,&puestoP}});

        Nat& cantidadHackeable {comprasHackeables.at(pi).first};
        cantidadHackeable += cant;
    }
}

void lollapatuza::hackear(const Persona &a, const Producto &item)
{
    infoPersona& info {_personas.at(a)};
    std::map<IdPuesto,std::pair<Nat, puesto*>>& puestosHackeables {info.comprasSinDescuento.at(item)};
    auto itMin {puestosHackeables.begin()};
    IdPuesto id_puesto {itMin->first};
    puesto* itPuesto {itMin->second.second};

    Nat precioItem {itPuesto->precio(item)};
    Nat& gastoActual {info.gastoPersona};
    _masGastadores.erase({-gastoActual,a});

    gastoActual -= precioItem;
    _masGastadores.insert({{-gastoActual, a}, a});

    itPuesto->olvidarItem(a,item);

    Nat& itemsHackeables {itMin->second.first};
    --itemsHackeables;

    if (! itemsHackeables)
        puestosHackeables.erase(id_puesto);
}

Nat lollapatuza::gastoPersona(const Persona &a) const
{
    return _personas.at(a).gastoPersona;
}

Persona lollapatuza::masGasto() const
{
    return _masGastadores.begin()->second; //devuelve el que más gastó con menor id.
}

IdPuesto lollapatuza::puestoConMenorStockDeItem(const Producto &item) const
{
    IdPuesto id_puestoMenorStock {_puestos.begin()->first};
    puesto puestoMenorStock {_puestos.begin()->second};
    Nat menorStock {(puestoMenorStock.estaEnElMenu(item)) ? puestoMenorStock.obtenerStock(item): UINT32_MAX};

    for (std::pair<IdPuesto, puesto> entrada : puestos())
    {
        IdPuesto& id_puestoActual {entrada.first};
        puesto& puestoActual {entrada.second};

        if (puestoActual.estaEnElMenu(item) &&
            (puestoActual.obtenerStock(item) < menorStock ||
             (puestoActual.obtenerStock(item) == menorStock && id_puestoActual < id_puestoMenorStock) ) )
        {
            id_puestoMenorStock = id_puestoActual;
            menorStock = puestoActual.obtenerStock(item);
        }
    }

    return id_puestoMenorStock;
}

const std::set<Persona>& lollapatuza::personas() const
{
    return _conjPersonas;
}

const std::map<IdPuesto, puesto>& lollapatuza::puestos() const
{
    return _puestos;
}