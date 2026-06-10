#pragma once
#include <vector>
#include "Fecha.h"
#include "Cliente.h"
#include "LineaDetalle.h"
using namespace std;

class Venta {
public:
    Venta(const Fecha& fecha, Cliente* cliente);

    Fecha getFecha() const;
    Cliente* getCliente() const;

    void agregarLineaDetalle(LineaDetalle* linea);
    const vector<LineaDetalle*>& getLineas() const;

    float getTotal() const;

private:
    Fecha fecha;
    Cliente* cliente;
    vector<LineaDetalle*> lineas;
};
