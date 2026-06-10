#pragma once

#include <vector>

class Venta;
class Calificacion;
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
