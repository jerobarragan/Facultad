#ifndef FACHADA_LOLLAPATUZA_H
#define FACHADA_LOLLAPATUZA_H

#include <set>
#include <map>
#include "tipos.h"
#include "lollapatuza.h"


class FachadaLollapatuza {
public:
    FachadaLollapatuza(const std::set<Persona>& personas, const std::map<IdPuesto, aed2_Puesto>& infoPuestos);

    void registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto);
    void hackear(Persona persona, Producto producto);

    Nat gastoTotal(Persona persona) const;
    Persona mayorGastador() const;
    IdPuesto menorStock(Producto producto) const;

    const std::set<Persona>& personas() const;

    // Operaciones para obtener información de los puestos
    Nat stockEnPuesto(IdPuesto idPuesto, const Producto& producto) const;
    Nat descuentoEnPuesto(IdPuesto idPuesto, const Producto& producto, Nat cantidad) const;
    Nat gastoEnPuesto(IdPuesto idPuesto, Persona persona) const;

    /**
     * Devuelve el conjunto de los los ids de todos los puestos;
    */
    std::set<IdPuesto> idsDePuestos() const;

private:
    lollapatuza lolla_;
    std::map<IdPuesto, puesto> convertirPuestos (const std::map<IdPuesto, aed2_Puesto> &ps);
};

#endif
