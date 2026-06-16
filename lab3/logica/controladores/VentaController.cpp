#include "logica/controladores/VentaController.h"

#include "logica/controladores/AdminController.h"
#include "logica/dominio/Venta.h"

using namespace std;

VentaController::VentaController(
    AdminController& adminController
)
: adminController(adminController)
{
}

VentaController::~VentaController()
{
}

// ===== VENTAS =====

bool VentaController::registrarVenta(
    Venta* venta
)
{
    return true;
}

vector<Calificacion*> VentaController::listarCalificaciones() const {

    return calificaciones;
}

vector<Calificacion*> VentaController::getCalificacionesPorProducto(
    int codigoProducto
) const {
    vector<Calificacion*> calificacionesProducto;

    for (Calificacion* calificacion : calificaciones) {
        Producto* producto = calificacion->getProducto();
        if (producto && producto->getCodigo() == codigoProducto) {
            calificacionesProducto.push_back(calificacion);
        }
    }

    return calificacionesProducto;
}
