#include "logica/controladores/EmpleadoController.h"
#include "logica/dominio/ClienteRegistrado.h"

EmpleadoController::EmpleadoController(AdminController &adminController) : adminController(adminController) {}

EmpleadoController::~EmpleadoController()
{

    for (Cliente *c : clientes)
        delete c;

    for (OrdenCompra *o : ordenesCompra)
        delete o;
}

// ====================================
// CLIENTES
// ====================================

bool EmpleadoController::agregarCliente(Cliente *cliente)
{
    clientes.push_back(cliente);

    return true;
}

Cliente *EmpleadoController::buscarCliente(int rut) const
{

for (ClienteRegistrado* c : clientes)
{
    if (c->getRut() == rut)
        return c;
}

    return nullptr;
}

vector<Cliente *> EmpleadoController::listarClientes() const
{
    return clientes;
}

// ====================================
// ORDENES
// ====================================

bool EmpleadoController::crearOrdenCompra(OrdenCompra *orden)
{
    ordenesCompra.push_back(orden);

    return true;
}

vector<OrdenCompra *> EmpleadoController::listarOrdenes() const
{
    return ordenesCompra;
}
