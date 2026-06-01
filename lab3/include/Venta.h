#pragma once
#include <vector>
#include "DtFecha.h"
#include "Cliente.h"
#include "LineaDetalle.h"
using namespace std;

class Venta {
public:
    Venta(const DtFecha& fecha, Cliente* cliente);

    DtFecha getFecha() const;
    Cliente* getCliente() const;

    void agregarLineaDetalle(LineaDetalle* linea);
    const vector<LineaDetalle*>& getLineas() const;

    float getTotal() const;

private:
    DtFecha fecha;
    Cliente* cliente;
    vector<LineaDetalle*> lineas;
};