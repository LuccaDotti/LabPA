#pragma once

#include <vector>

class AdminController;
class Venta;
class Calificacion;

class VentaController
{
private:
    static VentaController* instancia;

    AdminController& adminController;

    VentaController(
        AdminController& adminController
    );

public:
    static VentaController* getInstancia();

    ~VentaController();

    bool registrarVenta(
        Venta* venta
    );

    std::vector<Calificacion*> listarCalificaciones() const;

    std::vector<Calificacion*> getCalificacionesPorProducto(
        int codigoProducto
    ) const;

private:
    std::vector<Calificacion*> calificaciones;
};
