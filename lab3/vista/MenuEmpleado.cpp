#include "vista/MenuEmpleado.h"

#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/AdminController.h"

#include <iostream>

using namespace std;

MenuEmpleado::MenuEmpleado(EmpleadoController& empleadoController, AdminController& adminController) : empleadoController(empleadoController), adminController(adminController)
{
}

void MenuEmpleado::mostrar() {

    int opcion;

    do {

        cout << "\n===== MENU EMPLEADO =====\n";
        cout << "1. Gestionar Clientes\n";
        cout << "2. Gestionar Ordenes de Compra\n";
        cout << "3. Consultar Productos\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                cout << "Gestion de Clientes\n";
                break;

            case 2:
                cout << "Gestion de Ordenes\n";
                break;

            case 3:
                cout << "Consulta de Productos\n";
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 0);
}
