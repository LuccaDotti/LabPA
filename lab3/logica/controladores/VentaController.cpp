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
