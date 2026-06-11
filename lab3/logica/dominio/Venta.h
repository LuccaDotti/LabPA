#pragma once

#include <vector>

#include "logica/dominio/Fecha.h"
#include "logica/dominio/LineaDetalle.h"

using namespace std;

class ClienteRegistrado;

class Venta
{
private:

    Fecha fecha;

    ClienteRegistrado* cliente;

    vector<LineaDetalle*> lineas;

    // Lista de ventas
    vector<Venta*> ventas;

public:

    Venta(
        const Fecha& fecha,
        ClienteRegistrado* cliente
    );

    ~Venta();

    Fecha getFecha() const;

    ClienteRegistrado* getCliente() const;

    void setCliente(
        ClienteRegistrado* cliente
    );

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
