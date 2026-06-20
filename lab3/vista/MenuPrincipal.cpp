#include "vista/MenuPrincipal.h"
#include "vista/MenuAdministrador.h"
#include "vista/MenuEmpleado.h"
#include "vista/MenuCliente.h"

#include "logica/controladores/AdminController.h"
#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/VentaController.h"

#include <iostream>
#include <string>

using namespace std;

MenuPrincipal::MenuPrincipal()
{
}

void MenuPrincipal::mostrar()
{
    string email;
    string password;

    while (true)
    {
        cout << "\n=============================\n";
        cout << " SISTEMA STOCK Y VENTAS\n";
        cout << "=============================\n";

        cout << "Email: ";
        cin >> email;

        cout << "Contrasena: ";
        cin >> password;

        if (
            email == "admin@gmail.com" &&
            password == "admin2026"
        )
        {
            MenuAdministrador menuAdmin(
                *AdminController::getInstancia()
            );

            menuAdmin.mostrar();
        }
        else if (
            email == "empleado@gmail.com" &&
            password == "empleado1234"
        )
        {
            MenuEmpleado menuEmpleado(
                *EmpleadoController::getInstancia(),
                *AdminController::getInstancia(),
                *VentaController::getInstancia()
            );

            menuEmpleado.mostrar();
        }
        else if (
            email == "cliente@gmail.com" &&
            password == "cliente5678"
        )
        {
            MenuCliente menuCliente(
                *VentaController::getInstancia(),
                *AdminController::getInstancia()
            );

            menuCliente.mostrar();
        }
        else
        {
            cout << "\nERROR: Credenciales invalidas.\n";
        }
    }
}
