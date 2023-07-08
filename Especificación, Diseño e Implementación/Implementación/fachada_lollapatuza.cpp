#include "fachada_lollapatuza.h"


FachadaLollapatuza::FachadaLollapatuza(const std::set<Persona> &personas, const std::map<IdPuesto, aed2_Puesto> &infoPuestos) : lolla_(convertirPuestos(infoPuestos), personas){ }

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto)
{
    lolla_.vender(idPuesto,persona,producto,cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto)
{
    lolla_.hackear(persona,producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const
{
    return lolla_.gastoPersona(persona);
}

Persona FachadaLollapatuza::mayorGastador() const
{
    return lolla_.masGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const
{
    return lolla_.puestoConMenorStockDeItem(producto);
}

const std::set<Persona> &FachadaLollapatuza::personas() const
{
    return lolla_.personas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const
{
    return lolla_.puestos().at(idPuesto).obtenerStock(producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const
{
    return lolla_.puestos().at(idPuesto).obtenerDescuento(producto, cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const
{
    return lolla_.puestos().at(idPuesto).obtenerGasto(persona);
}

std::set<IdPuesto> FachadaLollapatuza::idsDePuestos() const
{
    std::set<IdPuesto> res {};

    for (std::pair<IdPuesto, puesto> entrada : lolla_.puestos())
        res.insert(entrada.first);

    return res;
}

std::map<IdPuesto, puesto> FachadaLollapatuza::convertirPuestos (const std::map<IdPuesto, aed2_Puesto> &ps) {
    std::map<IdPuesto, puesto> puestos{};
    for (std::pair<IdPuesto, aed2_Puesto> entrada : ps)
    {
        puesto p {puesto(entrada.second.menu, entrada.second.stock, entrada.second.promociones)};
        puestos.insert({entrada.first, p});
    }
    return puestos;
}