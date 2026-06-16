#pragma once
#include "logica/dominio/Fecha.h"
#include "logica/dominio/Proveedor.h"
#include "logica/dominio/Producto.h"
using namespace std;

class ProveedorProducto {
public:
    ProveedorProducto(Proveedor* proveedor, Producto* producto, float precioCompra, const Fecha& fechaEntrega);

    Proveedor* getProveedor() const;
    Producto* getProducto() const;
    float getPrecioCompra() const;
    Fecha getFechaEntrega() const;

    void setPrecioCompra(float precio);

private:
    Proveedor* proveedor;
    Producto* producto;
    float precioCompra;
    Fecha fechaEntrega;
};
