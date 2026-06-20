#include "vista/MenuCliente.h"

#include "logica/controladores/VentaController.h"
#include "logica/controladores/AdminController.h"
#include "logica/controladores/tipoRetorno.h"

#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/Producto.h"
#include "logica/dominio/Venta.h"
#include "logica/dominio/LineaDetalle.h"
#include "logica/dominio/Categoria.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

MenuCliente::MenuCliente(VentaController& ventaController, AdminController& adminController, ClienteRegistrado* cliente)
: ventaController(ventaController), adminController(adminController), clienteActual(cliente)
{
}

void MenuCliente::mostrar() {

    int opcion;

    do {
        cout << "\n=====================================\n";
        cout << "         MENU CLIENTE\n";
        cout << "=====================================\n";
        cout << "1. Calificar Producto\n";
        cout << "2. Consultar Informacion de Producto\n";
        cout << "0. Cerrar Sesion\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                calificarProducto();
                break;

            case 2:
                consultarDetalleProducto();
                break;

            case 0:
                cout << "\nSesion cerrada.\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 0);
}

void MenuCliente::calificarProducto() {

    vector<Venta*> ventas = clienteActual->getVentas();

    if (ventas.empty()) {
        cout << "\nNo tenes compras registradas para calificar.\n";
        return;
    }

    cout << "\n===== CALIFICAR PRODUCTO =====\n";
    cout << "Productos disponibles para calificar:\n";

    for (Venta* v : ventas) {
        for (LineaDetalle* l : v->getLineas()) {
            cout << "  Codigo: " << l->getProducto()->getCodigo()
                 << " - " << l->getProducto()->getNombre() << "\n";
        }
    }

    int codigo, puntaje;
    string comentario;

    cout << "Ingrese codigo del producto: ";
    cin >> codigo;
    cout << "Ingrese puntaje (1-5): ";
    cin >> puntaje;
    cin.ignore();
    cout << "Ingrese comentario (opcional, Enter para omitir): ";
    getline(cin, comentario);

    TipoRet resultado = clienteActual->calificarProducto(codigo, puntaje, comentario);

    if (resultado == TipoRet::OK)
        cout << "Calificacion registrada correctamente.\n";
    else if (resultado == TipoRet::ERROR_PRODUCTO_NO_COMPRADO)
        cout << "Error: solo podes calificar productos que hayas comprado.\n";
    else if (resultado == TipoRet::ERROR_CALIFICACION_INVALIDA)
        cout << "Error: el puntaje debe ser un entero entre 1 y 5.\n";
}

void MenuCliente::consultarDetalleProducto() {

    vector<Venta*> ventas = clienteActual->getVentas();

    if (ventas.empty()) {
        cout << "\nNo tenes compras registradas.\n";
        return;
    }

    cout << "\n===== CONSULTAR INFORMACION DE PRODUCTO =====\n";
    cout << "Productos disponibles:\n";

    for (Venta* v : ventas) {
        for (LineaDetalle* l : v->getLineas()) {
            cout << "  Codigo: " << l->getProducto()->getCodigo()
                 << " - " << l->getProducto()->getNombre() << "\n";
        }
    }

    int codigo;
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    Producto* producto = clienteActual->consultarInformacionDetalladaProducto(codigo);

    if (producto == nullptr) {
        cout << "Error: solo podes consultar productos que hayas comprado.\n";
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
