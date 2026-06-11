#include "logica/controladores/VentaController.h"

#include "logica/controladores/AdminController.h"
#include "logica/dominio/Venta.h"

using namespace std;

VentaController::VentaController(AdminController& adminController) : adminController(adminController)
{
}

VentaController::~VentaController() {

    for (Venta* v : ventas)
        delete v;
}

// ===== VENTAS =====

bool VentaController::registrarVenta(Venta* venta)
{

    ventas.push_back(venta);

    return true;
}

vector<Venta*> VentaController::listarVentas() const {

    return ventas;
}
