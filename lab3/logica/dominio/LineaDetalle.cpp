#include "logica/dominio/LineaDetalle.h"
using namespace std;

LineaDetalle::LineaDetalle(Producto* producto, int cantidad, float precioUnitario) : producto(producto), cantidad(cantidad), precioUnitario(precioUnitario) {}

Producto* LineaDetalle::getProducto() const {
    return producto;
}

int LineaDetalle::getCantidad() const {
    return cantidad;
}

float LineaDetalle::getPrecioUnitario() const {
    return precioUnitario;
}

float LineaDetalle::getSubtotal() const {
    return cantidad * precioUnitario;
}
