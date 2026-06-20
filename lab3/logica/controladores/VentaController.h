#pragma once

#include <vector>
#include "logica/dominio/Calificacion.h"
#include "logica/dominio/Direccion.h"
#include "logica/controladores/tipoRetorno.h"
using namespace std;

class Venta;
class Calificacion;
class AdminController;

class VentaController {

private:
    AdminController& adminController;
    vector<Calificacion*> calificaciones;

public:

    VentaController(
        AdminController& adminController
    );

    ~VentaController();

    TipoRet calificarProducto(int codigoProducto, int calificacion, string comentario);

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
