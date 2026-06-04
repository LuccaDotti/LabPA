#include "LineaCompra.h"
#include "OrdenCompra.h"
using namespace std;

LineaCompra::LineaCompra(Producto* producto, ProveedorProducto* proveedorProducto,
                         int cantidad, float precioUnitario)
    : ordenCompra(nullptr), producto(producto), proveedorProducto(proveedorProducto),
      cantidad(cantidad), precioUnitario(precioUnitario) {}

OrdenCompra* LineaCompra::getOrdenCompra() const {
    return ordenCompra;
}

Producto* LineaCompra::getProducto() const {
    return producto;
}

ProveedorProducto* LineaCompra::getProveedorProducto() const {
    return proveedorProducto;
}

int LineaCompra::getCantidad() const {
    return cantidad;
}

float LineaCompra::getPrecioUnitario() const {
    return precioUnitario;
}

float LineaCompra::getSubtotal() const {
    return cantidad * precioUnitario;
}

void LineaCompra::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

void LineaCompra::setOrdenCompra(OrdenCompra* orden) {
    this->ordenCompra = orden;
}
