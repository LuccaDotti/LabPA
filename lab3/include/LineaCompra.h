#pragma once
#include "Producto.h"
using namespace std;

class LineaCompra {
public:
    LineaCompra(Producto* producto, int cantidad);

    Producto* getProducto() const;
    int getCantidad() const;
    void setCantidad(int cantidad);

private:
    Producto* producto;
    int cantidad;
};
