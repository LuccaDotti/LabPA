#include "logica/controladores/EmpleadoController.h"

using namespace std;

EmpleadoController::EmpleadoController(
    AdminController& adminController
)
: adminController(adminController)
{
}

EmpleadoController::~EmpleadoController()
{
    for (ClienteRegistrado* c : clientes)
        delete c;

    for (OrdenCompra* o : ordenesCompra)
        delete o;
}

// ====================================
// CLIENTES REGISTRADOS
// ====================================

bool EmpleadoController::agregarCliente(
    ClienteRegistrado* cliente
)
{
    clientes.push_back(cliente);

    return true;
}

ClienteRegistrado* EmpleadoController::buscarCliente(
    int rut
) const
{
    for (ClienteRegistrado* c : clientes)
    {
        if (c->getRut() == rut)
            return c;
    }

    return nullptr;
}

vector<ClienteRegistrado*> EmpleadoController::listarClientes() const
{
    return clientes;
}

// ====================================
// ORDENES DE COMPRA
// ====================================

bool EmpleadoController::crearOrdenCompra(
    OrdenCompra* orden
)
{
    ordenesCompra.push_back(orden);

    return true;
}

vector<OrdenCompra*> EmpleadoController::listarOrdenes() const
{
    return ordenesCompra;
}
