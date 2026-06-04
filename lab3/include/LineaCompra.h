#pragma once
#include "Producto.h"
#include "ProveedorProducto.h"
using namespace std;

class OrdenCompra;

class LineaCompra {
public:
    LineaCompra(Producto* producto, ProveedorProducto* proveedorProducto,
                int cantidad, float precioUnitario);

    OrdenCompra* getOrdenCompra() const;
    Producto* getProducto() const;
    ProveedorProducto* getProveedorProducto() const;
    int getCantidad() const;
    float getPrecioUnitario() const;
    float getSubtotal() const;

    void setCantidad(int cantidad);
    void setOrdenCompra(OrdenCompra* orden);

private:
    OrdenCompra* ordenCompra;
    Producto* producto;
    ProveedorProducto* proveedorProducto;
    int cantidad;
    float precioUnitario;
};
