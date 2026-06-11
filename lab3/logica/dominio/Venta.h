#pragma once

#include <vector>

#include "logica/dominio/Fecha.h"
#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/LineaDetalle.h"

using namespace std;

class Venta
{
private:

    Fecha fecha;

    vector<LineaDetalle*> lineas;

    // Lista de ventas
    vector<Venta*> ventas;

public:

    Venta(
        const Fecha& fecha
    );

    ~Venta();

    Fecha getFecha() const;

    void agregarLineaDetalle(
        LineaDetalle* linea
    );

    const vector<LineaDetalle*>& getLineas() const;

    float getTotal() const;

    vector<Venta*> getVentas() const;

    void agregarVenta(
        Venta* venta
    );
};
