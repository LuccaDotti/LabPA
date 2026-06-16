#include "vista/MenuAdministrador.h"
#include "logica/controladores/AdminController.h"

#include <iostream>

using namespace std;

MenuAdministrador::MenuAdministrador(AdminController& adminController) : adminController(adminController)
{
}

void MenuAdministrador::mostrar() {

    int opcion;

    do {

        cout << "\n===== MENU ADMINISTRADOR =====\n";
        cout << "1. Gestionar Productos\n";
        cout << "2. Gestionar Categorias\n";
        cout << "3. Gestionar Proveedores\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        switch(opcion) {

            case 1:
                cout << "Gestion de Productos\n";
                break;

            case 2:
                cout << "Gestion de Categorias\n";
                break;

            case 3:
                cout << "Gestion de Proveedores\n";
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while(opcion != 0);
}
