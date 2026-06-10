#pragma once
#include <vector>
#include "lofica/dominio/Fecha.h"
#include "logica/dominio/Cliente.h"
#include "logica/dominio/LineaDetalle.h"
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
