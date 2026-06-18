#include "logica/controladores/EmpleadoController.h"
#include "logica/dominio/ClienteRegistrado.h"
#include "logica/controladores/tipoRetorno.h"

EmpleadoController::EmpleadoController(AdminController &adminController) : adminController(adminController) {}

EmpleadoController::~EmpleadoController()
{

    for (ClienteRegistrado *c : clientes)
        delete c;

    for (OrdenCompra *o : ordenesCompra)
        delete o;
}

// ====================================
// CLIENTES
// ====================================

TipoRet EmpleadoController::registrarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia, float totalFacturado)
{
    if (buscarCliente(rut) != nullptr)
    {
        return TipoRet::ERROR_CLIENTE_EXISTENTE;
    }

    Direccion direccion(nroPuerta, calle, ciudad);
    ClienteRegistrado *cliente = new ClienteRegistrado(rut, direccion, correo, nombreCompleto, contrasenia, totalFacturado);
    clientes.push_back(cliente);

    return TipoRet::OK;
}

TipoRet EmpleadoController::modificarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia)
{
    if (buscarCliente(rut) == nullptr)
    {
        return TipoRet::ERROR_CLIENTE_INEXISTENTE;
    }

    for (int x = 0; x < clientes.size(); x++)
    {
        if (clientes[x]->getCorreo() == correo && clientes[x]->getRut() != rut)
        {
            return TipoRet::ERROR_CORREO_EXISTENTE;
        }
    }

    ClienteRegistrado *cliente = buscarCliente(rut);
    cliente->setNombreCompleto(nombreCompleto);
    cliente->setCorreo(correo);
    cliente->setDireccion(Direccion(nroPuerta, calle, ciudad));
    cliente->setContrasenia(contrasenia);

    return TipoRet::OK;
}

TipoRet EmpleadoController::registrarVenta(int rut, int codigoProducto, int cantidad)
{
    if (buscarCliente(rut) == nullptr)
    {
        return TipoRet::ERROR_CLIENTE_INEXISTENTE;
    }

    for (int x = 0; x < productos.size(); x++)
    {
        if (productos[x]->getCodigo() == codigoProducto)
        {
            return TipoRet::ERROR_PRODUCTO_INEXISTENTE;
        }
    }

    return TipoRet::OK;
}

ClienteRegistrado *EmpleadoController::buscarCliente(int rut) const
{

    for (ClienteRegistrado *c : clientes)
    {
        if (c->getRut() == rut)
            return c;
    }

    return nullptr;
}

vector<ClienteRegistrado *> EmpleadoController::listarClientes() const
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
