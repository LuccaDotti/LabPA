#pragma once
#include <vector>
#include "DtFecha.h"
#include "Estado.h"
#include "LineaCompra.h"
#include "Proveedor.h"
using namespace std;

class OrdenCompra {
public:
    OrdenCompra(const DtFecha& fechaEmision, Proveedor* proveedor);

    DtFecha getFechaEmision() const;
    Estado getEstado() const;
    void setEstado(Estado estado);

    Proveedor* getProveedor() const;

    void agregarLineaCompra(LineaCompra* linea);
    const vector<LineaCompra*>& getLineas() const;

private:
    DtFecha fechaEmision;
    Estado estado;
    Proveedor* proveedor;
    vector<LineaCompra*> lineas;
};
