#include "logica/dominio/ClienteRegistrado.h"
#include "logica/controladores/tipoRetorno.h"
#include "logica/dominio/Venta.h"
#include "logica/dominio/LineaDetalle.h"
#include "logica/dominio/Fecha.h"
#include "logica/dominio/LineaOrdenCompra.h"
#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/AdminController.h"

EmpleadoController *EmpleadoController::instancia = nullptr;

EmpleadoController *EmpleadoController::getInstancia()
{
    if (instancia == nullptr)
        instancia = new EmpleadoController();
    return instancia;
}

EmpleadoController::EmpleadoController()
{
    adminController = AdminController::getInstancia();

    Direccion dir1(0, "Sin calle", "Sin ciudad");
    clientes.push_back(new ClienteRegistrado(0, dir1, "cliente@gmail.com", "Cliente", "5678", 0.0f));

    Direccion dir2(1234, "18 de Julio", "Montevideo");
    ClienteRegistrado* cliente2 = new ClienteRegistrado(11223344, dir2, "ana.perez@gmail.com", "Ana Perez", "ana1234", 0.0f);
    clientes.push_back(cliente2);

    Direccion dir3(987, "Av. Italia", "Montevideo");
    ClienteRegistrado* cliente3 = new ClienteRegistrado(55667788, dir3, "carlos.diaz@gmail.com", "Carlos Diaz", "carlos1234", 0.0f);
    clientes.push_back(cliente3);

    // Venta inicial precargada para cliente2, asi ya tiene historial y puede calificar
    Producto* producto = buscarProducto(1001);
    if (producto != nullptr)
    {
        Venta* ventaSeed = new Venta(Fecha(), cliente2);
        LineaDetalle* linea = new LineaDetalle(producto, 2, producto->getPrecioUnitario());
        ventaSeed->agregarLineaDetalle(linea);
        cliente2->agregarVenta(ventaSeed);
        producto->vender(2);
        cliente2->agregarFacturacion(2 * producto->getPrecioUnitario());
    }
}

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

TipoRet EmpleadoController::registrarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, string contrasenia, float totalFacturado)
{
    if (buscarCliente(rut) != nullptr)
        return TipoRet::ERROR_CLIENTE_EXISTENTE;

    for (ClienteRegistrado *c : clientes)
        if (c->getCorreo() == correo)
            return TipoRet::ERROR_CORREO_EXISTENTE;

    Direccion direccion(nroPuerta, calle, ciudad);
    ClienteRegistrado *cliente = new ClienteRegistrado(rut, direccion, correo, nombreCompleto, contrasenia, totalFacturado);
    clientes.push_back(cliente);

    return TipoRet::OK;
}

TipoRet EmpleadoController::modificarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, string contrasenia)
{
    if (buscarCliente(rut) == nullptr)
        return TipoRet::ERROR_CLIENTE_INEXISTENTE;

    for (int x = 0; x < (int)clientes.size(); x++)
    {
        if (clientes[x]->getCorreo() == correo && clientes[x]->getRut() != rut)
            return TipoRet::ERROR_CORREO_EXISTENTE;
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
    if (cantidad <= 0)
        return TipoRet::ERROR_CANTIDAD_INVALIDA;

    ClienteRegistrado *cliente = buscarCliente(rut);
    if (cliente == nullptr)
        return TipoRet::ERROR_CLIENTE_INEXISTENTE;

    Producto *producto = buscarProducto(codigoProducto);
    if (producto == nullptr)
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;

    if (producto->getStockActual() < cantidad)
        return TipoRet::ERROR_STOCK_INSUFICIENTE;

    Venta *venta = new Venta(Fecha(), cliente);
    LineaDetalle *linea = new LineaDetalle(producto, cantidad, producto->getPrecioUnitario());
    venta->agregarLineaDetalle(linea);

    cliente->agregarVenta(venta);
    producto->vender(cantidad);

    float total = cantidad * producto->getPrecioUnitario();
    cliente->agregarFacturacion(total);

    return TipoRet::OK;
}

TipoRet EmpleadoController::consultarHistorialCompraCliente(int rut, vector<Venta *> &ventas)
{
    if (buscarCliente(rut) == nullptr)
        return TipoRet::ERROR_CLIENTE_INEXISTENTE;

    ClienteRegistrado *cliente = buscarCliente(rut);
    ventas = cliente->getVentas();

    if (ventas.empty())
        return TipoRet::ERROR_VENTA_SIN_DETALLES;

    return TipoRet::OK;
}

TipoRet EmpleadoController::emitirOrdenCompra(int codigoProducto, int cantidad, int rutProveedor)
{
    if (cantidad <= 0)
        return TipoRet::ERROR_CANTIDAD_INVALIDA;

    if (buscarProducto(codigoProducto) == nullptr)
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;

    if (buscarProveedor(rutProveedor) == nullptr)
        return TipoRet::ERROR_PROVEEDOR_INEXISTENTE;

    Proveedor *proveedorEncontrado = nullptr;
    Producto *productoEncontrado = nullptr;

    vector<ProveedorProducto *> relaciones = adminController->listarProveedorProductos();
    for (ProveedorProducto *pp : relaciones)
    {
        if (pp->getProducto()->getCodigo() == codigoProducto &&
            pp->getProveedor()->getRut() == rutProveedor)
        {
            proveedorEncontrado = pp->getProveedor();
            productoEncontrado = pp->getProducto();
            break;
        }
    }

    if (proveedorEncontrado == nullptr)
        return TipoRet::ERROR_PROVEEDOR_PRODUCTO_INEXISTENTE;

    OrdenCompra *ordenCompra = new OrdenCompra(new Fecha(), PENDIENTE, proveedorEncontrado);
    LineaOrdenCompra *linea = new LineaOrdenCompra(productoEncontrado, cantidad, productoEncontrado->getPrecioUnitario());
    ordenCompra->agregarLineaCompra(linea);
    ordenesCompra.push_back(ordenCompra);

    return TipoRet::OK;
}

TipoRet EmpleadoController::cancelarOrdenCompra(int idOrdenCompra)
{
    OrdenCompra *orden = buscarOrdenCompra(idOrdenCompra);
    if (orden == nullptr)
        return TipoRet::ERROR_ORDEN_INEXISTENTE;

    if (orden->getEstado() != PENDIENTE)
        return TipoRet::ERROR_ORDEN_NO_PENDIENTE;

    orden->setEstado(CANCELADA);
    return TipoRet::OK;
}

TipoRet EmpleadoController::registrarRecepcionOrdenCompra(int idOrden, vector<int> cantidadesRecibidas)
{
    OrdenCompra *orden = buscarOrdenCompra(idOrden);
    if (orden == nullptr)
        return TipoRet::ERROR_ORDEN_INEXISTENTE;

    if (orden->getEstado() != PENDIENTE)
        return TipoRet::ERROR_ORDEN_NO_PENDIENTE;

    vector<LineaOrdenCompra *> lineas = orden->getLineasCompra();

    for (int i = 0; i < (int)lineas.size(); i++)
    {
        if (lineas[i]->getCantidad() != cantidadesRecibidas[i])
            return TipoRet::ERROR_CANTIDAD_NO_COINCIDE;
    }

    orden->setEstado(RECIBIDA);
    orden->setFechaRecepcion(new Fecha());

    for (int i = 0; i < (int)lineas.size(); i++)
    {
        int stockActual = lineas[i]->getProducto()->getStockActual();
        lineas[i]->getProducto()->setStockActual(stockActual + cantidadesRecibidas[i]);
    }

    return TipoRet::OK;
}

TipoRet EmpleadoController::eliminarProducto(int codigo)
{
    Producto *producto = adminController->buscarProducto(codigo);
    if (producto == nullptr)
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;

    if (producto->getUnidadesVendidas() > 0)
        return TipoRet::ERROR_PRODUCTO_CON_VENTAS;

    for (OrdenCompra *o : ordenesCompra)
        for (LineaOrdenCompra *l : o->getLineasCompra())
            if (l->getProducto()->getCodigo() == codigo && o->getEstado() == PENDIENTE)
                return TipoRet::ERROR_ORDEN_PENDIENTE;

    return adminController->eliminarProducto(codigo);
}

// ====================================
// BUSQUEDAS - delegan en AdminController
// ====================================

Producto *EmpleadoController::buscarProducto(int codigoProducto) const
{
    return adminController->buscarProducto(codigoProducto);
}

Proveedor *EmpleadoController::buscarProveedor(int rutProveedor) const
{
    return adminController->buscarProveedor(rutProveedor);
}

OrdenCompra *EmpleadoController::buscarOrdenCompra(int idOrdenCompra) const
{
    for (OrdenCompra *o : ordenesCompra)
        if (o->getId() == idOrdenCompra)
            return o;
    return nullptr;
}

ClienteRegistrado *EmpleadoController::buscarCliente(int rut) const
{
    for (ClienteRegistrado *c : clientes)
        if (c->getRut() == rut)
            return c;
    return nullptr;
}

vector<ClienteRegistrado *> EmpleadoController::listarClientes() const
{
    return clientes;
}

bool EmpleadoController::crearOrdenCompra(OrdenCompra *orden)
{
    ordenesCompra.push_back(orden);
    return true;
}

vector<OrdenCompra *> EmpleadoController::listarOrdenes() const
{
    return ordenesCompra;
}

// ====================================
// REPORTES
// ====================================

vector<Calificacion *> EmpleadoController::consultarCalificacionesDeProducto(int codigoProducto) const
{
    vector<Calificacion *> calificaciones;
    for (ClienteRegistrado *cliente : clientes)
        for (Calificacion *cal : cliente->getCalificaciones())
            if (cal->getProducto()->getCodigo() == codigoProducto)
                calificaciones.push_back(cal);
    return calificaciones;
}

int EmpleadoController::consultarStockActual(int codigoProducto) const
{
    Producto *producto = buscarProducto(codigoProducto);
    if (producto == nullptr)
        return -1;
    return producto->getStockActual();
}

vector<Producto *> EmpleadoController::consultarProductoBajoMinimo() const
{
    vector<Producto *> productosBajos;
    for (Producto *producto : adminController->listarProductos())
        if (producto->getStockActual() <= producto->getStockMinimo())
            productosBajos.push_back(producto);
    return productosBajos;
}

float EmpleadoController::montoTotalFacturadoACliente(int rut) const
{
    ClienteRegistrado *cliente = buscarCliente(rut);
    if (cliente == nullptr)
        return 0.0;
    return cliente->getTotalFacturado();
}

int EmpleadoController::unidadesVendidasDeProducto(int codigoProducto) const
{
    Producto *producto = buscarProducto(codigoProducto);
    if (producto == nullptr)
        return -1;
    return producto->getUnidadesVendidas();
}

ClienteRegistrado *EmpleadoController::buscarClientePorCorreo(const string &correo, const string &password) const
{
    for (ClienteRegistrado *c : clientes)
        if (c->getCorreo() == correo && c->getContrasenia() == password)
            return c;
    return nullptr;
}
