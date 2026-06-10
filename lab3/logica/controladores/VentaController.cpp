#include "logica/controladores/VentaController.h"

#include "logica/controladores/AdminController.h"
#include "logica/dominio/Venta.h"
#include "logica/dominio/Calificacion.h"

using namespace std;

VentaController::VentaController(
    AdminController& adminController
)
: adminController(adminController)
{
}

VentaController::~VentaController() {

    for (Venta* v : ventas)
        delete v;

    for (Calificacion* c : calificaciones)
        delete c;
}

// ===== VENTAS =====

bool VentaController::registrarVenta(
    Venta* venta
) {

    ventas.push_back(venta);

    return true;
}

vector<Venta*> VentaController::listarVentas() const {

    return ventas;
}

// ===== CALIFICACIONES =====

bool VentaController::agregarCalificacion(
    Calificacion* calificacion
) {

    calificaciones.push_back(calificacion);

    return true;
}

vector<Calificacion*> VentaController::listarCalificaciones() const {

    return calificaciones;
}
