#ifndef TP_LOLLA_LOLLAPATUZA_H
#define TP_LOLLA_LOLLAPATUZA_H
#include <set>
#include <map>
#include "tipos.h"
#include "puesto.h"

class lollapatuza
{
    public:
        lollapatuza(const std::map<IdPuesto, puesto> &ps, const std::set<Persona>& as);
        lollapatuza& operator=(const lollapatuza& l);
        void vender(const IdPuesto &pi, const Persona &a, const Producto &item, const Nat &cant);
        void hackear(const Persona &a, const Producto &item);
        Nat gastoPersona(const Persona &a) const;
        Persona masGasto() const;
        IdPuesto puestoConMenorStockDeItem(const Producto &item) const;
        const std::set<Persona>& personas() const;
        const std::map<IdPuesto, puesto>& puestos() const;
        /* Funciones que se usaban para las precondiciones, no se implementan en el codigo
         * bool pertenecePersona(Persona a);
         * bool pertenecePuesto(IdPuesto pi);
         * bool vendenAlMismoPrecio(std::map<IdPuesto, puesto*>);
        */

private:
    struct infoPersona
    {
        Nat gastoPersona;
        std::map<Producto, std::map<IdPuesto, std::pair<Nat, puesto*>>> comprasSinDescuento;
    };

    std::map<IdPuesto, puesto> _puestos;
    /*
     * solo lo usábamos para vender para luego eventualmente poner la dirección del puesto en infoPersonas y acceder en
     * O(1) al puesto, ahora directamente en infoPersonas se guarda el mismo puntero al puesto que se crea al vender,
     * que también permite acceder en O(1) al puesto y nos ahorramos un diccLog y una búsqueda en el mismo en cada venta
     * std::map<IdPuesto, puesto*> _itPuestos;
    */

    std::set<Persona> _conjPersonas;
    std::map<Persona, infoPersona> _personas;
    std::map<std::pair<int, Persona>, Persona> _masGastadores;
};


#endif //TP_LOLLA_LOLLAPATUZA_H