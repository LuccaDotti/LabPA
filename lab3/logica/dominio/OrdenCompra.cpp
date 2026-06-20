#include "logica/dominio/OrdenCompra.h"
int OrdenCompra::proximoId = 1;
using namespace std;

OrdenCompra::OrdenCompra(
    Fecha *fechaEmision,
    EstadoOrden estado,
    Proveedor *proveedor)
{
    this->fechaEmision = fechaEmision;
    this->estado = estado;
    this->proveedor = proveedor;
    this->id = proximoId++;
}

OrdenCompra::~OrdenCompra()
{
}

int OrdenCompra::getId() const
{
    return id;
}

void OrdenCompra::setId(int id)
{
    this->id = id;
}

Fecha *OrdenCompra::getFechaEmision() const
{
    return fechaEmision;
}

void OrdenCompra::setFechaEmision(
    Fecha *fechaEmision)
{
    this->fechaEmision = fechaEmision;
}

EstadoOrden OrdenCompra::getEstado() const
{
    return estado;
}

void OrdenCompra::setEstado(
    EstadoOrden estado)
{
    this->estado = estado;
}

Proveedor *OrdenCompra::getProveedor() const
{
    return proveedor;
}

void OrdenCompra::setProveedor(
    Proveedor *proveedor)
{
    this->proveedor = proveedor;
}

vector<LineaCompra *> OrdenCompra::getLineasCompra() const
{
    return lineasCompra;
}

void OrdenCompra::agregarLineaCompra(
    LineaCompra *lineaCompra)
{
    lineasCompra.push_back(
        lineaCompra);
}
