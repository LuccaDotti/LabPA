#include "logica/controladores/EmpleadoController.h"
#include "logica/dominio/ClienteRegistrado.h"
#include "logica/controladores/tipoRetorno.h"
#include "logica/dominio/Venta.h"
#include "logica/dominio/LineaDetalle.h"
#include "logica/dominio/Fecha.h"

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
    ClienteRegistrado *cliente = buscarCliente(rut);
    if (cliente == nullptr)
    {
        return TipoRet::ERROR_CLIENTE_INEXISTENTE;
    }

    Producto *producto = buscarProducto(codigoProducto); // ← producto, no productos
    if (producto == nullptr)
    {
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;
    }

    if (producto->getStockActual() < cantidad)
    {
        return TipoRet::ERROR_STOCK_INSUFICIENTE;
    }

    Venta *venta = new Venta(Fecha(), cliente);
    LineaDetalle *linea = new LineaDetalle(producto, cantidad, producto->getPrecioUnitario());
    venta->agregarLineaDetalle(linea);

    cliente->agregarVenta(venta);
    producto->vender(cantidad);

    return TipoRet::OK;
}

TipoRet EmpleadoController::consultarHistorialCompraCliente(int rut, vector<Venta *> &ventas)
{
    if (buscarCliente(rut) == nullptr)
    {
        return TipoRet::ERROR_CLIENTE_INEXISTENTE;
    }

    ClienteRegistrado *cliente = buscarCliente(rut);
    ventas = cliente->getVentas();

    if (ventas.empty())
    {
        return TipoRet::ERROR_VENTA_SIN_DETALLES;
    }

    // se pasa por referencia el vector de ventas para que la vista pueda acceder a él
    ventas = cliente->getVentas();
    return TipoRet::OK;
}

TipoRet EmpleadoController::emitirOrdenCompra(int codigoProducto, int cantidad, int rutProveedor)
{
    if (buscarProducto(codigoProducto) == nullptr)
    {
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;
    }

    if (buscarProveedor(rutProveedor) == nullptr)
    {
        return TipoRet::ERROR_PROVEEDOR_INEXISTENTE;
    }

    Proveedor *proveedorEncontrado = nullptr;
    Producto *productoEncontrado = nullptr;

    for (int x = 0; x < proveedorProductos.size(); x++)
    {
        if (proveedorProductos[x]->getProducto()->getCodigo() == codigoProducto && proveedorProductos[x]->getProveedor()->getRut() == rutProveedor)
        {
            proveedorEncontrado = proveedorProductos[x]->getProveedor();
            productoEncontrado = proveedorProductos[x]->getProducto();
            break;
        }
    }

    if (proveedorEncontrado == nullptr)
    {
        return TipoRet::ERROR_PROVEEDOR_PRODUCTO_INEXISTENTE;
    }

    OrdenCompra *ordenCompra = new OrdenCompra(new Fecha(), PENDIENTE, proveedorEncontrado);
    ordenesCompra.push_back(ordenCompra);

    return TipoRet::OK;
}

TipoRet EmpleadoController::cancelarOrdenCompra(int idOrdenCompra)
{
    if (buscarOrdenCompra(idOrdenCompra) == nullptr)
    {
        return TipoRet::ERROR_ORDEN_INEXISTENTE;
    }

    OrdenCompra *orden = buscarOrdenCompra(idOrdenCompra);

    if (orden->getEstado() != PENDIENTE)
    {
        return TipoRet::ERROR_ORDEN_NO_PENDIENTE;
    }
    orden->setEstado(CANCELADA);

    return TipoRet::OK;
}

OrdenCompra *EmpleadoController::buscarOrdenCompra(int idOrdenCompra) const
{

    for (OrdenCompra *c : ordenesCompra)
    {
        if (c->getId() == idOrdenCompra)
        {
            return c;
        }
    }

    return nullptr;
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

Proveedor *EmpleadoController::buscarProveedor(int codigoProveedor) const
{
    for (Proveedor *p : proveedores)
    {
        if (p->getRut() == codigoProveedor)
            return p;
    }

    return nullptr;
}

Producto *EmpleadoController::buscarProducto(int codigoProducto) const
{
    for (Producto *p : productos)
    {
        if (p->getCodigo() == codigoProducto)
            return p;
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
