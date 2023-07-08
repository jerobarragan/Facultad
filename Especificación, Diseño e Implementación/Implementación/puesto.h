#ifndef TP_LOLLA_PUESTO_H
#define TP_LOLLA_PUESTO_H

#include <list>
#include <map>
#include "tipos.h"
#include "diccDig.h"

struct infoPromo {
    Nat minN;
    Nat maxN;
    diccDig<Nat> descuentos;
};

struct infoVentas {
    std::list<Nat> ventasConDescuento;
    std::list<Nat> ventasSinDescuento;
};


class puesto {
    public:
        puesto(Menu  menu, Stock& stock, const Promociones &promos);
        Nat obtenerDescuento(const Producto &i, const Nat &cant) const;
        Nat obtenerGasto(const Persona &a) const;
        Nat vender(const Persona &a, const Producto &i, const Nat &cant);
        void olvidarItem(const Persona &a, const Producto &i);
        Nat precio(const Producto &i);
        Nat obtenerStock(const Producto &i) const;
        bool estaEnElMenu(const Producto &i) const;
        //bool consumioSinPromo(Persona a, Producto i); La función no se usa; se usaba para chequear precondiciones

    private:
    Menu _menu;
        Stock _stock;
        std::map<Producto, infoPromo> _promociones;
        std::map<Persona, Nat> _gastos;
        std::map<Persona, std::map<Producto, infoVentas> > _ventas;
        static Nat aplicarDescuento(Nat, Nat);
};

#endif
