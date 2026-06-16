#pragma once

class Venta;
class AdminController;

using namespace std;

class VentaController {

private:

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

    vector<Calificacion*> getCalificacionesPorProducto(
        int codigoProducto
    ) const;
};
