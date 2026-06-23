#include "vista/MenuEmpleado.h"
#include "vista/InputUtils.h"

#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/AdminController.h"
#include "logica/controladores/VentaController.h"
#include "logica/controladores/tipoRetorno.h"

#include "logica/dominio/Calificacion.h"
#include "logica/dominio/Producto.h"
#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/Venta.h"
#include "logica/dominio/LineaDetalle.h"
#include "logica/dominio/Categoria.h"
#include "logica/dominio/OrdenCompra.h"
#include "logica/dominio/LineaOrdenCompra.h"
#include "logica/dominio/Proveedor.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

MenuEmpleado::MenuEmpleado(
    EmpleadoController &empleadoController,
    AdminController &adminController,
    VentaController &ventaController)
    : empleadoController(empleadoController),
      adminController(adminController),
      ventaController(ventaController)
{
}

void MenuEmpleado::mostrar()
{
    int opcion;

    do
    {
        cout << "\n=====================================\n";
        cout << "         MENU EMPLEADO\n";
        cout << "=====================================\n";
        cout << "1. Gestionar Clientes\n";
        cout << "2. Ventas\n";
        cout << "3. Ordenes de Compra\n";
        cout << "4. Reportes\n";
        cout << "5. Consultar Informacion de Producto\n";
        cout << "0. Cerrar Sesion\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            menuGestionarClientes();
            break;
        case 2:
            menuVentas();
            break;
        case 3:
            menuGestionarOrdenesCompra();
            break;
        case 4:
            menuReportes();
            break;
        case 5:
            consultarDetalleProducto();
            break;
        case 0:
            cout << "\nSesion cerrada.\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

// ===== CLIENTES =====

void MenuEmpleado::menuGestionarClientes()
{
    int opcion;

    do
    {
        cout << "\n===== GESTIONAR CLIENTES =====\n";
        cout << "1. Listar Clientes\n";
        cout << "2. Alta de Cliente\n";
        cout << "3. Modificar Cliente\n";
        cout << "4. Monto Total Facturado\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            listarClientes();
            break;
        case 2:
            altaCliente();
            break;
        case 3:
            modificarCliente();
            break;
        case 4:
            consultarTotalFacturado();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

void MenuEmpleado::listarClientes()
{
    cout << "\n===== LISTADO DE CLIENTES =====\n";

    vector<ClienteRegistrado *> clientes = empleadoController.listarClientes();

    if (clientes.empty())
    {
        cout << "No hay clientes registrados.\n";
        return;
    }

    cout << "\nTotal: " << clientes.size() << " cliente(s)\n";
    cout << "===================================================\n";

    for (int i = 0; i < (int)clientes.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << clientes[i]->getRut() << "\n";
        cout << "   Nombre: " << clientes[i]->getNombreCompleto() << "\n";
        cout << "   Correo: " << clientes[i]->getCorreo() << "\n";
        cout << "   Total Facturado: $" << clientes[i]->getTotalFacturado() << "\n";
        cout << "===================================================\n";
    }
}

void MenuEmpleado::altaCliente()
{
    int rut, nroPuerta;
    string nombre, correo, calle, ciudad, contrasenia;

    cout << "\n===== ALTA DE CLIENTE =====\n";
    cout << "RUT: ";
    rut = leerEntero();
    cout << "Nombre completo: ";
    nombre = leerLineaNoVacia();
    do {
        cout << "Correo (debe contener @ y .): ";
        correo = leerLineaNoVacia();
        if (validarEmail(correo) != TipoRet::OK)
            cout << "Email invalido. Debe contener @ y .\n";
    } while (validarEmail(correo) != TipoRet::OK);
    cout << "Calle: ";
    calle = leerLineaNoVacia();
    cout << "Nro puerta: ";
    nroPuerta = leerEntero();
    cout << "Ciudad: ";
    ciudad = leerLineaNoVacia();
    cout << "Contrasenia: ";
    contrasenia = leerLineaNoVacia();

    cout << "\n--- RESUMEN DEL NUEVO CLIENTE ---\n";
    cout << "RUT: " << rut << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Correo: " << correo << "\n";
    cout << "Direccion: " << calle << " #" << nroPuerta << ", " << ciudad << "\n";

    char confirmar;
    cout << "\nConfirmar creacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet resultado = empleadoController.registrarCliente(rut, nombre, correo, nroPuerta, calle, ciudad, contrasenia, 0.0f);

    if (resultado == TipoRet::OK)
        cout << "\nCliente registrado correctamente.\n";
    else if (resultado == TipoRet::ERROR_CLIENTE_EXISTENTE)
        cout << "\nError: ya existe un cliente con ese RUT.\n";
    else if (resultado == TipoRet::ERROR_CORREO_EXISTENTE)
        cout << "\nError: ese correo ya esta en uso por otro cliente.\n";
}

void MenuEmpleado::modificarCliente()
{
    cout << "\n===== MODIFICAR CLIENTE =====\n";
    cout << "\n--- CLIENTES DISPONIBLES ---\n";

    vector<ClienteRegistrado *> clientes = empleadoController.listarClientes();

    if (clientes.empty())
    {
        cout << "No hay clientes registrados.\n";
        return;
    }

    for (int i = 0; i < (int)clientes.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << clientes[i]->getRut()
             << " | " << clientes[i]->getNombreCompleto() << "\n";
    }

    int rut;
    cout << "\nRUT del cliente a modificar: ";
    rut = leerEntero();

    ClienteRegistrado *clienteBuscado = empleadoController.buscarCliente(rut);
    if (clienteBuscado == nullptr)
    {
        cout << "\nError: Cliente no encontrado.\n";
        return;
    }

    cout << "\n--- DATOS ACTUALES ---\n";
    cout << "RUT: " << clienteBuscado->getRut() << "\n";
    cout << "Nombre: " << clienteBuscado->getNombreCompleto() << "\n";
    cout << "Correo: " << clienteBuscado->getCorreo() << "\n";
    cout << "Calle: " << clienteBuscado->getDireccion().getCalle() << "\n";
    cout << "Nro Puerta: " << clienteBuscado->getDireccion().getNroPuerta() << "\n";
    cout << "Ciudad: " << clienteBuscado->getDireccion().getCiudad() << "\n";

    int nroPuerta;
    string nombre, correo, calle, ciudad, contrasenia;

    cout << "\nNuevo nombre completo: ";
    nombre = leerLineaNoVacia();
    do {
        cout << "Nuevo correo (debe contener @ y .): ";
        correo = leerLineaNoVacia();
        if (validarEmail(correo) != TipoRet::OK)
            cout << "Email invalido. Debe contener @ y .\n";
    } while (validarEmail(correo) != TipoRet::OK);
    cout << "Nueva calle: ";
    calle = leerLineaNoVacia();
    cout << "Nuevo nro puerta: ";
    nroPuerta = leerEntero();
    cout << "Nueva ciudad: ";
    ciudad = leerLineaNoVacia();
    cout << "Nueva contrasenia: ";
    contrasenia = leerLineaNoVacia();

    cout << "\n--- CAMBIOS A REALIZAR ---\n";
    cout << "Nombre: " << clienteBuscado->getNombreCompleto() << " -> " << nombre << "\n";
    cout << "Correo: " << clienteBuscado->getCorreo() << " -> " << correo << "\n";

    char confirmar;
    cout << "\nConfirmar modificacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet resultado = empleadoController.modificarCliente(rut, nombre, correo, nroPuerta, calle, ciudad, contrasenia);

    if (resultado == TipoRet::OK)
        cout << "\nCliente modificado correctamente.\n";
    else if (resultado == TipoRet::ERROR_CLIENTE_INEXISTENTE)
        cout << "\nError: cliente no encontrado.\n";
    else if (resultado == TipoRet::ERROR_CORREO_EXISTENTE)
        cout << "\nError: ese correo ya esta en uso.\n";
}

// ===== VENTAS =====

void MenuEmpleado::menuVentas()
{
    int opcion;

    do
    {
        cout << "\n===== VENTAS =====\n";
        cout << "1. Registrar Venta\n";
        cout << "2. Consultar Historial de Compras\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            registrarVenta();
            break;
        case 2:
            consultarHistorialCompras();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

void MenuEmpleado::registrarVenta()
{
    int rut, codigo, cantidad;

    cout << "\n===== REGISTRAR VENTA =====\n";

    cout << "\n--- CLIENTES DISPONIBLES ---\n";
    vector<ClienteRegistrado *> clientes = empleadoController.listarClientes();

    if (clientes.empty())
    {
        cout << "No hay clientes registrados.\n";
        return;
    }

    for (int i = 0; i < (int)clientes.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << clientes[i]->getRut()
             << " | " << clientes[i]->getNombreCompleto() << "\n";
    }

    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre()
             << " | Stock: " << productos[i]->getStockActual() << "\n";
    }

    cout << "\nRUT del cliente: ";
    rut = leerEntero();
    cout << "Codigo del producto: ";
    codigo = leerEntero();
    cout << "Cantidad: ";
    cantidad = leerEntero();

    TipoRet resultado = empleadoController.registrarVenta(rut, codigo, cantidad);

    if (resultado == TipoRet::OK)
        cout << "\nVenta registrada correctamente.\n";
    else if (resultado == TipoRet::ERROR_CANTIDAD_INVALIDA)
        cout << "\nError: la cantidad debe ser mayor a cero.\n";
    else if (resultado == TipoRet::ERROR_CLIENTE_INEXISTENTE)
        cout << "\nError: cliente no encontrado.\n";
    else if (resultado == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "\nError: producto no encontrado.\n";
    else if (resultado == TipoRet::ERROR_STOCK_INSUFICIENTE)
        cout << "\nError: stock insuficiente.\n";
}

void MenuEmpleado::consultarHistorialCompras()
{
    int rut;

    cout << "\n===== HISTORIAL DE COMPRAS =====\n";

    cout << "\n--- CLIENTES DISPONIBLES ---\n";
    vector<ClienteRegistrado *> clientes = empleadoController.listarClientes();

    if (clientes.empty())
    {
        cout << "No hay clientes registrados.\n";
        return;
    }

    for (int i = 0; i < (int)clientes.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << clientes[i]->getRut()
             << " | " << clientes[i]->getNombreCompleto() << "\n";
    }

    cout << "\nRUT del cliente: ";
    rut = leerEntero();

    vector<Venta *> ventas;
    TipoRet resultado = empleadoController.consultarHistorialCompraCliente(rut, ventas);

    if (resultado == TipoRet::ERROR_CLIENTE_INEXISTENTE)
    {
        cout << "\nError: cliente no encontrado.\n";
        return;
    }
    if (resultado == TipoRet::ERROR_VENTA_SIN_DETALLES)
    {
        cout << "\nEl cliente no tiene compras registradas.\n";
        return;
    }

    cout << "\n--- Historial de compras ---\n";
    for (Venta *v : ventas)
    {
        cout << "Venta | Total: $" << v->getTotal() << "\n";
        for (LineaDetalle *l : v->getLineas())
        {
            cout << "  - " << l->getProducto()->getNombre()
                 << " x" << l->getCantidad()
                 << " @ $" << l->getPrecioUnitario()
                 << " = $" << l->getSubtotal() << "\n";
        }
    }
}

// ===== ORDENES DE COMPRA =====

void MenuEmpleado::menuGestionarOrdenesCompra()
{
    int opcion;

    do
    {
        cout << "\n===== ORDENES DE COMPRA =====\n";
        cout << "1. Listar Ordenes de Compra\n";
        cout << "2. Emitir Orden de Compra\n";
        cout << "3. Cancelar Orden de Compra\n";
        cout << "4. Registrar Recepcion de Orden\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            listarOrdenesCompra();
            break;
        case 2:
            emitirOrdenCompra();
            break;
        case 3:
            cancelarOrdenCompra();
            break;
        case 4:
            registrarRecepcionOrden();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

void MenuEmpleado::listarOrdenesCompra()
{
    cout << "\n===== LISTADO DE ORDENES DE COMPRA =====\n";

    vector<OrdenCompra *> ordenes = empleadoController.listarOrdenes();

    if (ordenes.empty())
    {
        cout << "No hay ordenes de compra registradas.\n";
        return;
    }

    cout << "\nTotal: " << ordenes.size() << " orden(es)\n";
    cout << "===================================================\n";

    for (int i = 0; i < (int)ordenes.size(); i++)
    {
        cout << (i + 1) << ". ID: " << ordenes[i]->getId() << "\n";
        cout << "   Proveedor: " << ordenes[i]->getProveedor()->getNombreEmpresa() << "\n";
        cout << "   Estado: ";

        switch (ordenes[i]->getEstado())
        {
        case 0: cout << "PENDIENTE"; break;
        case 1: cout << "RECIBIDA"; break;
        case 2: cout << "CANCELADA"; break;
        default: cout << "DESCONOCIDO";
        }
        cout << "\n";
        cout << "===================================================\n";
    }
}

void MenuEmpleado::emitirOrdenCompra()
{
    int codigo, cantidad, rutProveedor;

    cout << "\n===== EMITIR ORDEN DE COMPRA =====\n";

    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre() << "\n";
    }

    cout << "\n--- PROVEEDORES DISPONIBLES ---\n";
    vector<Proveedor *> proveedores = adminController.listarProveedores();

    if (proveedores.empty())
    {
        cout << "No hay proveedores registrados.\n";
        return;
    }

    for (int i = 0; i < (int)proveedores.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << proveedores[i]->getRut()
             << " | " << proveedores[i]->getNombreEmpresa() << "\n";
    }

    cout << "\nCodigo del producto: ";
    codigo = leerEntero();
    cout << "Cantidad: ";
    cantidad = leerEntero();
    cout << "RUT del proveedor: ";
    rutProveedor = leerEntero();

    TipoRet resultado = empleadoController.emitirOrdenCompra(codigo, cantidad, rutProveedor);

    if (resultado == TipoRet::OK)
        cout << "\nOrden emitida correctamente.\n";
    else if (resultado == TipoRet::ERROR_CANTIDAD_INVALIDA)
        cout << "\nError: la cantidad debe ser mayor a cero.\n";
    else if (resultado == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "\nError: producto no encontrado.\n";
    else if (resultado == TipoRet::ERROR_PROVEEDOR_INEXISTENTE)
        cout << "\nError: proveedor no encontrado.\n";
    else if (resultado == TipoRet::ERROR_PROVEEDOR_PRODUCTO_INEXISTENTE)
        cout << "\nError: el proveedor no suministra ese producto.\n";
}

void MenuEmpleado::cancelarOrdenCompra()
{
    cout << "\n===== CANCELAR ORDEN DE COMPRA =====\n";
    cout << "\n--- ORDENES PENDIENTES ---\n";

    vector<OrdenCompra *> ordenes = empleadoController.listarOrdenes();
    vector<OrdenCompra *> ordenesPendientes;

    for (OrdenCompra *o : ordenes)
    {
        if (o->getEstado() == PENDIENTE)
            ordenesPendientes.push_back(o);
    }

    if (ordenesPendientes.empty())
    {
        cout << "No hay ordenes pendientes para cancelar.\n";
        return;
    }

    for (int i = 0; i < (int)ordenesPendientes.size(); i++)
    {
        cout << (i + 1) << ". ID: " << ordenesPendientes[i]->getId()
             << " | Proveedor: " << ordenesPendientes[i]->getProveedor()->getNombreEmpresa() << "\n";
    }

    int id;
    cout << "\nID de la orden a cancelar: ";
    id = leerEntero();

    OrdenCompra *ordenBuscada = empleadoController.buscarOrdenCompra(id);
    if (ordenBuscada == nullptr)
    {
        cout << "\nError: orden no encontrada.\n";
        return;
    }

    cout << "\n--- DATOS DE LA ORDEN ---\n";
    cout << "ID: " << ordenBuscada->getId() << "\n";
    cout << "Proveedor: " << ordenBuscada->getProveedor()->getNombreEmpresa() << "\n";
    cout << "Estado: PENDIENTE\n";

    char confirmar;
    cout << "\nConfirmar cancelacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet resultado = empleadoController.cancelarOrdenCompra(id);

    if (resultado == TipoRet::OK)
        cout << "\nOrden cancelada correctamente.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_INEXISTENTE)
        cout << "\nError: orden no encontrada.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_NO_PENDIENTE)
        cout << "\nError: solo se pueden cancelar ordenes pendientes.\n";
}

void MenuEmpleado::registrarRecepcionOrden()
{
    cout << "\n===== REGISTRAR RECEPCION DE ORDEN =====\n";
    cout << "\n--- ORDENES PENDIENTES ---\n";

    vector<OrdenCompra *> ordenes = empleadoController.listarOrdenes();
    vector<OrdenCompra *> ordenesPendientes;

    for (OrdenCompra *o : ordenes)
    {
        if (o->getEstado() == PENDIENTE)
            ordenesPendientes.push_back(o);
    }

    if (ordenesPendientes.empty())
    {
        cout << "No hay ordenes pendientes para recibir.\n";
        return;
    }

    for (int i = 0; i < (int)ordenesPendientes.size(); i++)
    {
        cout << (i + 1) << ". ID: " << ordenesPendientes[i]->getId()
             << " | Proveedor: " << ordenesPendientes[i]->getProveedor()->getNombreEmpresa() << "\n";
    }

    int id;
    cout << "\nID de la orden: ";
    id = leerEntero();

    OrdenCompra *ordenBuscada = empleadoController.buscarOrdenCompra(id);
    if (ordenBuscada == nullptr)
    {
        cout << "\nError: orden no encontrada.\n";
        return;
    }

    cout << "\n--- DETALLES DE LA ORDEN ---\n";
    cout << "ID: " << ordenBuscada->getId() << "\n";
    cout << "Proveedor: " << ordenBuscada->getProveedor()->getNombreEmpresa() << "\n";
    cout << "Lineas de compra: " << ordenBuscada->getLineasCompra().size() << "\n";

    vector<LineaOrdenCompra *> lineas = ordenBuscada->getLineasCompra();
    cout << "\n";
    for (int i = 0; i < (int)lineas.size(); i++)
    {
        cout << "Linea " << (i + 1) << ": " << lineas[i]->getProducto()->getNombre()
             << " | Cantidad esperada: " << lineas[i]->getCantidad() << "\n";
    }

    cout << "\nIngrese las cantidades recibidas:\n";
    vector<int> cantidades(lineas.size());

    for (int i = 0; i < (int)lineas.size(); i++)
    {
        cout << "Cantidad recibida para linea " << (i + 1) << ": ";
        cantidades[i] = leerEntero();
    }
    cin.ignore();

    char confirmar;
    cout << "\nConfirmar recepcion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet resultado = empleadoController.registrarRecepcionOrdenCompra(id, cantidades);

    if (resultado == TipoRet::OK)
        cout << "\nRecepcion registrada correctamente.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_INEXISTENTE)
        cout << "\nError: orden no encontrada.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_NO_PENDIENTE)
        cout << "\nError: solo se pueden recibir ordenes pendientes.\n";
    else if (resultado == TipoRet::ERROR_CANTIDAD_NO_COINCIDE)
        cout << "\nError: las cantidades no coinciden con la orden.\n";
}

// ===== REPORTES =====

void MenuEmpleado::menuReportes()
{
    int opcion;

    do
    {
        cout << "\n===== REPORTES =====\n";
        cout << "1. Consultar Stock Actual\n";
        cout << "2. Consultar Productos Bajo Minimo\n";
        cout << "3. Monto Total Facturado a Cliente\n";
        cout << "4. Unidades Vendidas de Producto\n";
        cout << "5. Consultar Calificaciones de Producto\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            consultarStockActual();
            break;
        case 2:
            consultarProductosBajoMinimo();
            break;
        case 3:
            consultarTotalFacturado();
            break;
        case 4:
            consultarUnidadesVendidas();
            break;
        case 5:
            consultarCalificacionesProducto();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

void MenuEmpleado::consultarStockActual()
{
    int codigo;

    cout << "\n===== CONSULTAR STOCK ACTUAL =====\n";

    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre() << "\n";
    }

    cout << "\nIngrese codigo del producto: ";
    codigo = leerEntero();

    int stock = empleadoController.consultarStockActual(codigo);

    if (stock == -1)
    {
        cout << "\nError: producto no encontrado.\n";
        return;
    }

    Producto *producto = adminController.buscarProducto(codigo);
    cout << "\nProducto: " << producto->getNombre() << "\n";
    cout << "Stock actual: " << stock << " unidades\n";
}

void MenuEmpleado::consultarProductosBajoMinimo()
{
    cout << "\n===== PRODUCTOS BAJO MINIMO =====\n";

    vector<Producto *> productos = empleadoController.consultarProductoBajoMinimo();

    if (productos.empty())
    {
        cout << "No hay productos bajo el stock minimo.\n";
        return;
    }

    cout << "\nProductos con stock bajo:\n";
    cout << "===================================================\n";

    for (Producto *p : productos)
    {
        cout << "Codigo: " << p->getCodigo() << "\n";
        cout << "Nombre: " << p->getNombre() << "\n";
        cout << "Stock actual: " << p->getStockActual() << "\n";
        cout << "Stock minimo: " << p->getStockMinimo() << "\n";
        cout << "===================================================\n";
    }
}

void MenuEmpleado::consultarTotalFacturado()
{
    int rut;

    cout << "\n===== MONTO TOTAL FACTURADO =====\n";

    cout << "\n--- CLIENTES DISPONIBLES ---\n";
    vector<ClienteRegistrado *> clientes = empleadoController.listarClientes();

    if (clientes.empty())
    {
        cout << "No hay clientes registrados.\n";
        return;
    }

    for (int i = 0; i < (int)clientes.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << clientes[i]->getRut()
             << " | " << clientes[i]->getNombreCompleto() << "\n";
    }

    cout << "\nIngrese RUT del cliente: ";
    rut = leerEntero();

    ClienteRegistrado *cliente = empleadoController.buscarCliente(rut);

    if (cliente == nullptr)
    {
        cout << "\nError: cliente no encontrado.\n";
        return;
    }

    cout << "\nCliente: " << cliente->getNombreCompleto() << "\n";
    cout << "Total facturado: $" << empleadoController.montoTotalFacturadoACliente(rut) << "\n";
}

void MenuEmpleado::consultarUnidadesVendidas()
{
    int codigo;

    cout << "\n===== UNIDADES VENDIDAS =====\n";

    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre() << "\n";
    }

    cout << "\nIngrese codigo del producto: ";
    codigo = leerEntero();

    int unidades = empleadoController.unidadesVendidasDeProducto(codigo);

    if (unidades == -1)
    {
        cout << "\nError: producto no encontrado.\n";
        return;
    }

    Producto *producto = adminController.buscarProducto(codigo);
    cout << "\nProducto: " << producto->getNombre() << "\n";
    cout << "Unidades vendidas: " << unidades << "\n";
}

// ===== CALIFICACIONES / INFO PRODUCTO =====

void MenuEmpleado::consultarCalificacionesProducto()
{
    int codigo;

    cout << "\n===== CALIFICACIONES DE PRODUCTO =====\n";
    cout << "Ingrese codigo del producto: ";
    codigo = leerEntero();

    Producto *producto = adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "\nError: producto no encontrado.\n";
        return;
    }

    vector<Calificacion *> calificaciones = empleadoController.consultarCalificacionesDeProducto(codigo);

    cout << "\n--- Producto: " << producto->getNombre() << " ---\n";

    if (calificaciones.empty())
    {
        cout << "No hay calificaciones para este producto.\n";
    }
    else
    {
        cout << "Total de calificaciones: " << calificaciones.size() << "\n\n";
        for (Calificacion *cal : calificaciones)
        {
            cout << "Puntaje: " << cal->getPuntaje() << "/5\n";
            cout << "Comentario: " << (cal->getComentarioOpcional().empty() ? "(sin comentario)" : cal->getComentarioOpcional()) << "\n";
            cout << "---\n";
        }
    }
}

void MenuEmpleado::consultarDetalleProducto()
{
    int codigo;

    cout << "\n===== INFORMACION DETALLADA DE PRODUCTO =====\n";

    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre() << "\n";
    }

    cout << "\nIngrese codigo del producto: ";
    codigo = leerEntero();

    Producto *producto = adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "\nError: producto no encontrado.\n";
        return;
    }

    cout << "\n===== DATOS DEL PRODUCTO =====\n";
    cout << "Nombre: " << producto->getNombre() << "\n";
    cout << "Descripcion: " << producto->getDescripcion() << "\n";
    cout << "Precio: $" << producto->getPrecioUnitario() << "\n";
    cout << "Categoria: " << (producto->getCategoria() ? producto->getCategoria()->getNombre() : "Sin categoria") << "\n";
    cout << "Stock disponible: " << producto->getStockActual() << " unidades\n";
    cout << "Puntaje promedio: " << producto->getPuntajePromedio() << "/5\n";
    cout << "Unidades vendidas: " << producto->getUnidadesVendidas() << "\n";
}
