#pragma once
#include "Producto.h"
using namespace std;

class LineaDetalle {
public:
    LineaDetalle(Producto* producto, int cantidad, float precioUnitario);

    Producto* getProducto() const;
    int getCantidad() const;
    float getPrecioUnitario() const;
    float getSubtotal() const;

private:
    Producto* producto;
    int cantidad;
    float precioUnitario;
};
