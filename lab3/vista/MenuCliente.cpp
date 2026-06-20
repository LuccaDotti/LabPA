#include "vista/MenuCliente.h"

#include "logica/controladores/VentaController.h"
#include "logica/controladores/AdminController.h"

#include <iostream>

#include "logica/dominio/Producto.h"
#include "logica/dominio/Categoria.h"

using namespace std;

MenuCliente::MenuCliente(VentaController& ventaController, AdminController& adminController) : ventaController(ventaController), adminController(adminController)
{
}

void MenuCliente::mostrar() {

    int opcion;

    do {
        cout << "\n=====================================\n";
        cout << "         MENU CLIENTE\n";
        cout << "=====================================\n";
        cout << "1. Realizar Venta\n";
        cout << "2. Ver Productos\n";
        cout << "3. Calificar Producto\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                cout << "Registrar Venta\n";
                break;

            case 2:
                consultarDetalleProducto();
                break;

            case 3:
                cout << "Calificar Producto\n";
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 0);
}

void MenuCliente::consultarDetalleProducto() {
    int codigo;

    cout << "\n===== INFORMACION DE PRODUCTO =====\n";
    cout << "Ingrese codigo del producto: ";
    cin >> codigo;

    Producto* producto = adminController.buscarProducto(codigo);

    if (producto == nullptr) {
        cout << "Producto no encontrado.\n";
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
