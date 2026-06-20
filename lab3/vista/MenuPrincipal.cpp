#include "vista/MenuPrincipal.h"
#include "vista/MenuAdministrador.h"
#include "vista/MenuEmpleado.h"
#include "vista/MenuCliente.h"

#include "logica/controladores/AdminController.h"
#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/VentaController.h"
#include "logica/dominio/Usuario.h"
#include "logica/dominio/ClienteRegistrado.h"
#include "logica/controladores/Rol.h"

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

        cout << "Contrasenia: ";
        cin >> password;

        if (email == "admin@gmail.com" && password == "admin2026")
        {
            MenuAdministrador menuAdmin(
                *AdminController::getInstancia()
            );
            menuAdmin.mostrar();
        }
        else if (email == "empleado@gmail.com" && password == "empleado1234")
        {
            MenuEmpleado menuEmpleado(
                *EmpleadoController::getInstancia(),
                *AdminController::getInstancia(),
                *VentaController::getInstancia()
            );
            menuEmpleado.mostrar();
        }
        else if (email == "cliente@gmail.com" && password == "cliente5678")
        {
            ClienteRegistrado* cliente = EmpleadoController::getInstancia()->buscarClientePorCorreo(email, password);

            if (cliente != nullptr)
            {
                MenuCliente menuCliente(
                    *VentaController::getInstancia(),
                    *AdminController::getInstancia(),
                    cliente
                );
                menuCliente.mostrar();
            }
            else
            {
                cout << "\nERROR: Cliente no registrado en el sistema.\n";
            }
        }
        else
        {
            Usuario* usuario = AdminController::getInstancia()->buscarUsuarioPorEmail(email);

            if (usuario != nullptr && usuario->getPassword() == password)
            {
                if (usuario->getRol() == Rol::ADMINISTRADOR)
                {
                    MenuAdministrador menuAdmin(
                        *AdminController::getInstancia()
                    );
                    menuAdmin.mostrar();
                }
                else if (usuario->getRol() == Rol::EMPLEADO)
                {
                    MenuEmpleado menuEmpleado(
                        *EmpleadoController::getInstancia(),
                        *AdminController::getInstancia(),
                        *VentaController::getInstancia()
                    );
                    menuEmpleado.mostrar();
                }
            }
            else
            {
                ClienteRegistrado* cliente = EmpleadoController::getInstancia()->buscarClientePorCorreo(email, password);

                if (cliente != nullptr)
                {
                    MenuCliente menuCliente(
                        *VentaController::getInstancia(),
                        *AdminController::getInstancia(),
                        cliente
                    );
                    menuCliente.mostrar();
                }
                else
                {
                    cout << "\nERROR: Credenciales invalidas.\n";
                }
            }
        }
    }
}
