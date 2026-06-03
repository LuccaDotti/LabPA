#include "vista/MenuPrincipal.h"

#include "vista/MenuAdministrador.h"
#include "vista/MenuEmpleado.h"
#include "vista/MenuCliente.h"

#include "logica/controladores/AdminController.h"
#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/VentaController.h"

#include <iostream>

using namespace std;

MenuPrincipal::MenuPrincipal(
    AdminController& adminController,
    EmpleadoController& empleadoController,
    VentaController& ventaController
)
: adminController(adminController),
  empleadoController(empleadoController),
  ventaController(ventaController)
{
}

void MenuPrincipal::mostrar() {

    MenuAdministrador menuAdmin(
        adminController
    );

    MenuEmpleado menuEmpleado(
        empleadoController,
        adminController
    );

    MenuCliente menuCliente(
        ventaController,
        adminController
    );

    int opcion;

    do {

        cout << "\n=============================\n";
        cout << " SISTEMA STOCK Y VENTAS\n";
        cout << "=============================\n";
        cout << "1. Iniciar sesion Administrador\n";
        cout << "2. Iniciar sesion Empleado\n";
        cout << "3. Iniciar sesion Cliente\n";
        cout << "0. Salir\n";
        cout << "Seleccione: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                menuAdmin.mostrar();
                break;

            case 2:
                menuEmpleado.mostrar();
                break;

            case 3:
                menuCliente.mostrar();
                break;

            case 0:
                cout << "Hasta luego.\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 0);
}
