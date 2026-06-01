#pragma once
#include "DtFecha.h"
#include "Proveedor.h"
#include "Producto.h"
using namespace std;

class ProveedorProducto
{
public:
    ProveedorProducto(Proveedor *proveedor, Producto *producto, float precioCompra, const DtFecha &fechaEntrega);

    Proveedor *getProveedor() const;
    Producto *getProducto() const;
    float getPrecioCompra() const;
    DtFecha getFechaEntrega() const;

    void setPrecioCompra(float precio);

private:
    Proveedor *proveedor;
    Producto *producto;
    float precioCompra;
    DtFecha fechaEntrega;
};
