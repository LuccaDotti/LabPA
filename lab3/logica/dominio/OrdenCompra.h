#pragma once

#include <vector>

using namespace std;

class Fecha;
class Proveedor;
class LineaCompra;

enum EstadoOrden
{
    PENDIENTE,
    RECIBIDA,
    CANCELADA
};

class OrdenCompra
{
private:
    Fecha* fechaEmision;
    EstadoOrden estado;

    Proveedor* proveedor;

    vector<LineaCompra*> lineasCompra;

    // Lista de todas las órdenes de compra
    vector<OrdenCompra*> ordenesCompra;

public:
    OrdenCompra(
        Fecha* fechaEmision,
        EstadoOrden estado,
        Proveedor* proveedor
    );

    ~OrdenCompra();

    Fecha* getFechaEmision() const;
    void setFechaEmision(
        Fecha* fechaEmision
    );

    EstadoOrden getEstado() const;
    void setEstado(
        EstadoOrden estado
    );

    Proveedor* getProveedor() const;
    void setProveedor(
        Proveedor* proveedor
    );

    vector<LineaCompra*> getLineasCompra() const;

    void agregarLineaCompra(
        LineaCompra* lineaCompra
    );

    vector<OrdenCompra*> getOrdenesCompra() const;

    void agregarOrdenCompra(
        OrdenCompra* ordenCompra
    );
};
