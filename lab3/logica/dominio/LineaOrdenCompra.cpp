#include "logica/dominio/Calificacion.h"
#include "logica/dominio/LineaOrdenCompra.h"
using namespace std;

LineaOrdenCompra::LineaOrdenCompra(Producto* producto, int cantidad, float precioUnitario)

    : ordenCompra(nullptr), producto(producto),cantidad(cantidad), precioUnitario(precioUnitario) {}

OrdenCompra* LineaOrdenCompra::getOrdenCompra() const {
    return ordenCompra;
}

Producto* LineaOrdenCompra::getProducto() const {
    return producto;
}


int LineaOrdenCompra::getCantidad() const {
    return cantidad;
}

float LineaOrdenCompra::getPrecioUnitario() const {
    return precioUnitario;
}

float LineaOrdenCompra::getSubtotal() const {
    return cantidad * precioUnitario;
}

void LineaOrdenCompra::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

void LineaOrdenCompra::setOrdenCompra(OrdenCompra* orden) {
    this->ordenCompra = orden;
}
