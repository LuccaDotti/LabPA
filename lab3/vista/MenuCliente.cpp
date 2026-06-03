#include "vista/MenuCliente.h"

#include "logica/controladores/VentaController.h"
#include "logica/controladores/AdminController.h"

#include <iostream>

using namespace std;

MenuCliente::MenuCliente(
    VentaController& ventaController,
    AdminController& adminController
)
: ventaController(ventaController),
  adminController(adminController)
{
}

void MenuCliente::mostrar() {

    int opcion;

    do {

        cout << "\n===== MENU CLIENTE =====\n";
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
                cout << "Listado de Productos\n";
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
