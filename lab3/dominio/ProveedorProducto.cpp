#include "ProveedorProducto.h"
using namespace std;

ProveedorProducto::ProveedorProducto(Proveedor* proveedor, Producto* producto,
                                     float precioCompra, const Fecha& fechaEntrega)
    : proveedor(proveedor), producto(producto), precioCompra(precioCompra),
      fechaEntrega(fechaEntrega) {}

Proveedor* ProveedorProducto::getProveedor() const {
    return proveedor;
}

Producto* ProveedorProducto::getProducto() const {
    return producto;
}

float ProveedorProducto::getPrecioCompra() const {
    return precioCompra;
}

Fecha ProveedorProducto::getFechaEntrega() const {
    return fechaEntrega;
}

void ProveedorProducto::setPrecioCompra(float precio) {
    precioCompra = precio;
}
