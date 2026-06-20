#include "vista/MenuEmpleado.h"

#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/AdminController.h"
#include "logica/controladores/VentaController.h"

#include <iostream>
#include <vector>

#include "logica/dominio/Calificacion.h"
#include "logica/dominio/Producto.h"
#include "logica/dominio/ClienteRegistrado.h"

using namespace std;

MenuEmpleado::MenuEmpleado(
    EmpleadoController& empleadoController,
    AdminController& adminController,
    VentaController& ventaController
)
: empleadoController(empleadoController),
  adminController(adminController),
  ventaController(ventaController)
{
}

void MenuEmpleado::mostrar() {

    int opcion;

    do {
        cout << "\n=====================================\n";
        cout << "         MENU EMPLEADO\n";
        cout << "=====================================\n";
        cout << "1. Gestionar Clientes\n";
        cout << "2. Gestionar Ordenes de Compra\n";
        cout << "3. Consultar Productos\n";
        cout << "4. Consultar Calificaciones de Producto\n";
        cout << "0. Cerrar Sesion\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                menuGestionarClientes();
                break;

            case 2:
                cout << "Gestion de Ordenes\n";
                break;

            case 3:
                menuConsultarProductos();
                break;

            case 4:
                consultarCalificacionesProducto();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 0);
}

void MenuEmpleado::menuGestionarClientes() {

    int opcion;

    do {

        cout << "\n===== GESTIONAR CLIENTES =====\n";
        cout << "1. Monto total facturado a cliente\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                consultarTotalFacturado();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 0);
}

void MenuEmpleado::consultarTotalFacturado() {
    int rut;

    cout << "\n===== MONTO TOTAL FACTURADO =====\n";
    cout << "Ingrese RUT del cliente: ";
    cin >> rut;

    ClienteRegistrado* cliente =
    empleadoController.buscarCliente(rut);

    if (cliente == nullptr) {
        cout << "Cliente no encontrado.\n";
        return;
    }

    if (cliente == nullptr) {
        cout << "El cliente no es un cliente registrado.\n";
        return;
    }

    cout << "\nCliente: " << cliente->getNombreCompleto() << "\n";
    cout << "Total facturado: $" << cliente->getTotalFacturado() << "\n";
}

void MenuEmpleado::menuConsultarProductos() {

    int opcion;

    do {

        cout << "\n===== CONSULTAR PRODUCTOS =====\n";
        cout << "1. Consultar stock actual\n";
        cout << "2. Consultar productos bajo minimo\n";
        cout << "3. Consultar unidades vendidas\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                consultarStockActual();
                break;

            case 2:
                consultarProductosBajoMinimo();
                break;

            case 3:
                consultarUnidadesVendidas();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 0);
}

void MenuEmpleado::consultarStockActual() {
    int codigo;

    cout << "\n===== CONSULTAR STOCK ACTUAL =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    Producto* producto = adminController.buscarProducto(codigo);

    if (producto == nullptr) {
        cout << "Producto no encontrado.\n";
        return;
    }

    cout << "\nProducto: " << producto->getNombre() << "\n";
    cout << "Stock actual: " << producto->getStockActual() << " unidades\n";
}

void MenuEmpleado::consultarProductosBajoMinimo() {

    cout << "\n===== PRODUCTOS BAJO MINIMO =====\n";

    vector<Producto*> productos = adminController.listarProductos();

    bool hayAlguno = false;

    for (Producto* p : productos) {
        if (p->estaBajoStock()) {
            cout << "- " << p->getNombre()
                 << " | Stock actual: " << p->getStockActual()
                 << " | Stock minimo: " << p->getStockMinimo() << "\n";
            hayAlguno = true;
        }
    }

    if (!hayAlguno) {
        cout << "No hay productos bajo el stock minimo.\n";
    }
}

void MenuEmpleado::consultarUnidadesVendidas() {
    int codigo;

    cout << "\n===== UNIDADES VENDIDAS =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    Producto* producto = adminController.buscarProducto(codigo);

    if (producto == nullptr) {
        cout << "Producto no encontrado.\n";
        return;
    }

    cout << "\nProducto: " << producto->getNombre() << "\n";
    cout << "Unidades vendidas: " << producto->getUnidadesVendidas() << "\n";
}

void MenuEmpleado::consultarCalificacionesProducto() {
    int codigo;

    cout << "\n===== CONSULTAR CALIFICACIONES DE PRODUCTO =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    Producto* producto = adminController.buscarProducto(codigo);

    if (producto == nullptr) {
        cout << "Producto no encontrado.\n";
        return;
    }

    vector<Calificacion*> calificaciones = ventaController.getCalificacionesPorProducto(codigo);

    cout << "\n--- Producto: " << producto->getNombre() << " ---\n";
    cout << "Calificaciones:\n";

    if (calificaciones.empty()) {
        cout << "No hay calificaciones para este producto.\n";
    } else {
        for (Calificacion* cal : calificaciones) {
            cout << "  Puntaje: " << cal->getPuntaje() << "/5\n";
            cout << "  Comentario: " << cal->getComentarioOpcional() << "\n";
            cout << "  ---\n";
        }
    }
}
