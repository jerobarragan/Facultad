#include <utility>

#include "puesto.h"

puesto::puesto(Menu  menu, Stock& stock, const Promociones &promos) : _menu(std::move(menu)), _stock(stock), _gastos(), _ventas(), _promociones()
{
    for (std::pair <Producto, std::map<Nat, Nat>> entrada : promos)
    {
        diccDig<Nat> descuentos {};
        Nat maxN {};

        for (std::pair <Nat, Nat> desc: entrada.second)
        {
            descuentos.definir({desc.first,desc.second});
            maxN = desc.first;
        }

        Nat minN {entrada.second.begin()->first};
        Nat ultimoDescuento {descuentos.significado(minN)};

        for (Nat j = minN; j <= maxN; ++j)
        {
            if (!descuentos.definido(j))
                descuentos.definir({j,ultimoDescuento});
            else
                ultimoDescuento = descuentos.significado(j);
        }

        Producto item {entrada.first};
        _promociones.insert({item,infoPromo{minN, maxN, diccDig<Nat>(descuentos)}});
    }
}

Nat puesto::obtenerDescuento(const Producto &i, const Nat &cant) const
{
    if(!_promociones.count(i) )
        return 0;

    const infoPromo& infoP {_promociones.at(i)};

    if(infoP.maxN <= cant)
        return infoP.descuentos.significado(infoP.maxN);
    else if(infoP.minN <= cant)
        return infoP.descuentos.significado(cant);
    else
        return 0;
}

Nat puesto::obtenerGasto(const Persona &a) const
{
    return (_gastos.count(a)) ? _gastos.at(a) : 0;
}

Nat puesto::vender(const Persona &a, const Producto &i, const Nat &cant)
{
    Nat precioSinDescuento {_menu[i] * cant};
    Nat desc {obtenerDescuento(i, cant)};
    Nat gasto {aplicarDescuento(precioSinDescuento, desc)};

    if (!_gastos.count(a))
        _gastos.insert({a,0});
    _gastos.at(a) += gasto;
    _stock[i] -= cant;

    if (!_ventas.count(a))
        _ventas.insert({a,std::map<Producto, infoVentas>{}});
    std::map<Producto, infoVentas>& historial {_ventas.at(a)};

    if (!historial.count(i))
        historial.insert({i, infoVentas{}});
    infoVentas& itemHistorial {historial.at(i)};

    if (!desc)
        itemHistorial.ventasSinDescuento.push_front(cant);
    else
        itemHistorial.ventasConDescuento.push_front(cant);

    return gasto;
}

void puesto::olvidarItem(const Persona &a, const Producto &i)
{
    _gastos.at(a) -= _menu.at(i);
    ++_stock.at(i);

    std::map<Producto, infoVentas>* historial {&_ventas.at(a)};
    infoVentas& itemHistorial {historial->at(i)};
    Nat& cantidadConsumida{itemHistorial.ventasSinDescuento.front()};

    if (cantidadConsumida == 1)
        itemHistorial.ventasSinDescuento.pop_front();
    else
        --cantidadConsumida;
}

Nat puesto::precio(const Producto &i)
{
    return _menu[i];
}

Nat puesto::obtenerStock(const Producto &i) const
{
    return _stock.at(i);
}

bool puesto::estaEnElMenu(const Producto &i) const
{
    return _menu.count(i);
}

Nat puesto::aplicarDescuento(Nat precioSinDescuento, Nat desc)
{
    return (precioSinDescuento * (100 - desc) / 100);
}