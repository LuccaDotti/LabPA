#include "LineaCompra.h"
using namespace std;

LineaCompra::LineaCompra(Producto *producto, int cantidad) : producto(producto), cantidad(cantidad) {}

Producto *LineaCompra::getProducto() const
{
    return producto;
}
int LineaCompra::getCantidad() const
{
    return cantidad;
}
void LineaCompra::setCantidad(int cantidad)
{
    this->cantidad = cantidad;
}
