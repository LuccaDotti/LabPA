#include "vista/MenuEmpleado.h"

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

        cin >> opcion;

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

// ===== CLIENTES (CU 12-13) =====

void MenuEmpleado::menuGestionarClientes()
{

    int opcion;

    do
    {
        cout << "\n===== GESTIONAR CLIENTES =====\n";
        cout << "1. Alta de Cliente\n";
        cout << "2. Modificar Cliente\n";
        cout << "3. Monto Total Facturado\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch (opcion)
        {

        case 1:
            altaCliente();
            break;

        case 2:
            modificarCliente();
            break;

        case 3:
            consultarTotalFacturado();
            break;

        case 0:
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

void MenuEmpleado::altaCliente()
{
    int rut, nroPuerta, contrasenia;
    string nombre, correo, calle, ciudad;

    cout << "\n===== ALTA DE CLIENTE =====\n";
    cout << "RUT: ";
    cin >> rut;
    cin.ignore();
    cout << "Nombre completo: ";
    getline(cin, nombre);
    cout << "Correo: ";
    getline(cin, correo);
    cout << "Calle: ";
    getline(cin, calle);
    cout << "Nro puerta: ";
    cin >> nroPuerta;
    cin.ignore();
    cout << "Ciudad: ";
    getline(cin, ciudad);
    cout << "Contrasenia: ";
    cin >> contrasenia;

    TipoRet resultado = empleadoController.registrarCliente(rut, nombre, correo, nroPuerta, calle, ciudad, contrasenia, 0.0f);

    if (resultado == TipoRet::OK)
        cout << "Cliente registrado correctamente.\n";
    else if (resultado == TipoRet::ERROR_CLIENTE_EXISTENTE)
        cout << "Error: ya existe un cliente con ese RUT.\n";
}

void MenuEmpleado::modificarCliente()
{
    int rut, nroPuerta, contrasenia;
    string nombre, correo, calle, ciudad;

    cout << "\n===== MODIFICAR CLIENTE =====\n";
    cout << "RUT del cliente: ";
    cin >> rut;
    cin.ignore();
    cout << "Nuevo nombre completo: ";
    getline(cin, nombre);
    cout << "Nuevo correo: ";
    getline(cin, correo);
    cout << "Nueva calle: ";
    getline(cin, calle);
    cout << "Nuevo nro puerta: ";
    cin >> nroPuerta;
    cin.ignore();
    cout << "Nueva ciudad: ";
    getline(cin, ciudad);
    cout << "Nueva contrasenia: ";
    cin >> contrasenia;

    TipoRet resultado = empleadoController.modificarCliente(rut, nombre, correo, nroPuerta, calle, ciudad, contrasenia);

    if (resultado == TipoRet::OK)
        cout << "Cliente modificado correctamente.\n";
    else if (resultado == TipoRet::ERROR_CLIENTE_INEXISTENTE)
        cout << "Error: cliente no encontrado.\n";
    else if (resultado == TipoRet::ERROR_CORREO_EXISTENTE)
        cout << "Error: ese correo ya esta en uso.\n";
}

// ===== VENTAS (CU 14-15) =====

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

        cin >> opcion;

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
    cout << "RUT del cliente: ";
    cin >> rut;
    cout << "Codigo del producto: ";
    cin >> codigo;
    cout << "Cantidad: ";
    cin >> cantidad;

    TipoRet resultado = empleadoController.registrarVenta(rut, codigo, cantidad);

    if (resultado == TipoRet::OK)
        cout << "Venta registrada correctamente.\n";
    else if (resultado == TipoRet::ERROR_CLIENTE_INEXISTENTE)
        cout << "Error: cliente no encontrado.\n";
    else if (resultado == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "Error: producto no encontrado.\n";
    else if (resultado == TipoRet::ERROR_STOCK_INSUFICIENTE)
        cout << "Error: stock insuficiente.\n";
}

void MenuEmpleado::consultarHistorialCompras()
{
    int rut;

    cout << "\n===== HISTORIAL DE COMPRAS =====\n";
    cout << "RUT del cliente: ";
    cin >> rut;

    vector<Venta *> ventas;
    TipoRet resultado = empleadoController.consultarHistorialCompraCliente(rut, ventas);

    if (resultado == TipoRet::ERROR_CLIENTE_INEXISTENTE)
    {
        cout << "Error: cliente no encontrado.\n";
        return;
    }
    if (resultado == TipoRet::ERROR_VENTA_SIN_DETALLES)
    {
        cout << "El cliente no tiene compras registradas.\n";
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

// ===== ORDENES DE COMPRA (CU 16-18) =====

void MenuEmpleado::menuGestionarOrdenesCompra()
{

    int opcion;

    do
    {
        cout << "\n===== ORDENES DE COMPRA =====\n";
        cout << "1. Emitir Orden de Compra\n";
        cout << "2. Cancelar Orden de Compra\n";
        cout << "3. Registrar Recepcion de Orden\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch (opcion)
        {

        case 1:
            emitirOrdenCompra();
            break;

        case 2:
            cancelarOrdenCompra();
            break;

        case 3:
            registrarRecepcionOrden();
            break;

        case 0:
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

void MenuEmpleado::emitirOrdenCompra()
{
    int codigo, cantidad, rutProveedor;

    cout << "\n===== EMITIR ORDEN DE COMPRA =====\n";
    cout << "Codigo del producto: ";
    cin >> codigo;
    cout << "Cantidad: ";
    cin >> cantidad;
    cout << "RUT del proveedor: ";
    cin >> rutProveedor;

    TipoRet resultado = empleadoController.emitirOrdenCompra(codigo, cantidad, rutProveedor);

    if (resultado == TipoRet::OK)
        cout << "Orden emitida correctamente.\n";
    else if (resultado == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "Error: producto no encontrado.\n";
    else if (resultado == TipoRet::ERROR_PROVEEDOR_INEXISTENTE)
        cout << "Error: proveedor no encontrado.\n";
    else if (resultado == TipoRet::ERROR_PROVEEDOR_PRODUCTO_INEXISTENTE)
        cout << "Error: el proveedor no suministra ese producto.\n";
}

void MenuEmpleado::cancelarOrdenCompra()
{
    int id;

    cout << "\n===== CANCELAR ORDEN DE COMPRA =====\n";
    cout << "ID de la orden: ";
    cin >> id;

    TipoRet resultado = empleadoController.cancelarOrdenCompra(id);

    if (resultado == TipoRet::OK)
        cout << "Orden cancelada correctamente.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_INEXISTENTE)
        cout << "Error: orden no encontrada.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_NO_PENDIENTE)
        cout << "Error: solo se pueden cancelar ordenes pendientes.\n";
}

void MenuEmpleado::registrarRecepcionOrden()
{
    int id, n;

    cout << "\n===== REGISTRAR RECEPCION DE ORDEN =====\n";
    cout << "ID de la orden: ";
    cin >> id;
    cout << "Cantidad de lineas en la orden: ";
    cin >> n;

    vector<int> cantidades(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Cantidad recibida para linea " << (i + 1) << ": ";
        cin >> cantidades[i];
    }

    TipoRet resultado = empleadoController.registrarRecepcionOrdenCompra(id, cantidades);

    if (resultado == TipoRet::OK)
        cout << "Recepcion registrada correctamente.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_INEXISTENTE)
        cout << "Error: orden no encontrada.\n";
    else if (resultado == TipoRet::ERROR_ORDEN_NO_PENDIENTE)
        cout << "Error: solo se pueden recibir ordenes pendientes.\n";
    else if (resultado == TipoRet::ERROR_CANTIDAD_NO_COINCIDE)
        cout << "Error: las cantidades no coinciden con la orden.\n";
}

// ===== REPORTES (CU 21-24) =====

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
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

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
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    int stock = empleadoController.consultarStockActual(codigo);

    if (stock == -1)
    {
        cout << "Error: producto no encontrado.\n";
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

    for (Producto *p : productos)
    {
        cout << "- " << p->getNombre()
             << " | Stock actual: " << p->getStockActual()
             << " | Stock minimo: " << p->getStockMinimo() << "\n";
    }
}

void MenuEmpleado::consultarTotalFacturado()
{
    int rut;

    cout << "\n===== MONTO TOTAL FACTURADO =====\n";
    cout << "Ingrese RUT del cliente: ";
    cin >> rut;

    ClienteRegistrado *cliente = empleadoController.buscarCliente(rut);

    if (cliente == nullptr)
    {
        cout << "Error: cliente no encontrado.\n";
        return;
    }

    cout << "\nCliente: " << cliente->getNombreCompleto() << "\n";
    cout << "Total facturado: $" << empleadoController.montoTotalFacturadoACliente(rut) << "\n";
}

void MenuEmpleado::consultarUnidadesVendidas()
{
    int codigo;

    cout << "\n===== UNIDADES VENDIDAS =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    int unidades = empleadoController.unidadesVendidasDeProducto(codigo);

    if (unidades == -1)
    {
        cout << "Error: producto no encontrado.\n";
        return;
    }

    Producto *producto = adminController.buscarProducto(codigo);
    cout << "\nProducto: " << producto->getNombre() << "\n";
    cout << "Unidades vendidas: " << unidades << "\n";
}

// ===== CALIFICACIONES / INFO PRODUCTO (CU 20, 25) =====

void MenuEmpleado::consultarCalificacionesProducto()
{
    int codigo;

    cout << "\n===== CALIFICACIONES DE PRODUCTO =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    Producto *producto = adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "Error: producto no encontrado.\n";
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
        for (Calificacion *cal : calificaciones)
        {
            cout << "  Puntaje: " << cal->getPuntaje() << "/5\n";
            cout << "  Comentario: " << cal->getComentarioOpcional() << "\n";
            cout << "  ---\n";
        }
    }
}

void MenuEmpleado::consultarDetalleProducto()
{
    int codigo;

    cout << "\n===== INFORMACION DETALLADA DE PRODUCTO =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    Producto *producto = adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "Error: producto no encontrado.\n";
        return;
    }

    cout << "\nNombre: " << producto->getNombre() << "\n";
    cout << "Descripcion: " << producto->getDescripcion() << "\n";
    cout << "Precio: $" << producto->getPrecioUnitario() << "\n";
    cout << "Categoria: " << (producto->getCategoria() ? producto->getCategoria()->getNombre() : "Sin categoria") << "\n";
    cout << "Stock disponible: " << producto->getStockActual() << " unidades\n";
    cout << "Puntaje promedio: " << producto->getPuntajePromedio() << "/5\n";
    cout << "Unidades vendidas: " << producto->getUnidadesVendidas() << "\n";
}
