#pragma once

#include <vector>

#include "logica/dominio/Venta.h"
#include "logica/dominio/Calificacion.h"

class AdminController;

using namespace std;

class VentaController {

private:

    vector<Venta*> ventas;
    vector<Calificacion*> calificaciones;

    AdminController& adminController;

public:

    VentaController(
        AdminController& adminController
    );

    ~VentaController();

    bool registrarVenta(
        Venta* venta
    );

    vector<Venta*> listarVentas() const;

    bool agregarCalificacion(
        Calificacion* calificacion
    );

    vector<Calificacion*> listarCalificaciones() const;
};
