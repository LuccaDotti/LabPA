#include "OrdenCompra.h"
using namespace std;

OrdenCompra::OrdenCompra(const DtFecha &fechaEmision, Proveedor *proveedor) : fechaEmision(fechaEmision), estado(Estado::PENDIENTE), proveedor(proveedor) {}

DtFecha OrdenCompra::getFechaEmision() const
{
    return fechaEmision;
}
Estado OrdenCompra::getEstado() const
{
    return estado;
}
void OrdenCompra::setEstado(Estado e)
{
    estado = e;
}

Proveedor *OrdenCompra::getProveedor() const
{
    return proveedor;
}

void OrdenCompra::agregarLineaCompra(LineaCompra *linea)
{
    lineas.push_back(linea);
}
const vector<LineaCompra *> &OrdenCompra::getLineas() const
{
    return lineas;
}
