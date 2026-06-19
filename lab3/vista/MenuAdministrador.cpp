#include "vista/MenuAdministrador.h"
#include "logica/controladores/AdminController.h"
#include "logica/tipos/TipoRet.h"

#include <iostream>

using namespace std;

MenuAdministrador::MenuAdministrador(
    AdminController& adminController
)
: adminController(adminController)
{
}

void MenuAdministrador::mostrar()
{
    int opcion;

    do
    {
        cout << "\n=====================================\n";
        cout << "         MENU ADMINISTRADOR\n";
        cout << "=====================================\n";
        cout << "1. Gestion de Categorias\n";
        cout << "2. Gestion de Productos\n";
        cout << "3. Gestion de Proveedores\n";
        cout << "4. Consulta de Calificaciones\n";
        cout << "5. Gestion de Stock\n";
        cout << "6. Reportes\n";
        cout << "7. Informacion de Productos\n";
        cout << "0. Cerrar Sesion\n";
        cout << "Opcion: ";

        cin >> opcion;
        cin.ignore();

        switch(opcion)
        {
            case 1:
                menuCategorias();
                break;

            case 2:
                menuProductos();
                break;

            case 3:
                menuProveedores();
                break;

            case 4:
                menuCalificaciones();
                break;

            case 5:
                menuStock();
                break;

            case 6:
                menuReportes();
                break;

            case 7:
                menuInfoProducto();
                break;

            case 0:
                cout << "\nSesion cerrada.\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while(opcion != 0);
}

void MenuAdministrador::menuCategorias()
{
    int opcion;

    do
    {
        cout << "\n===== CATEGORIAS =====\n";
        cout << "1. Agregar Categoria\n";
        cout << "2. Modificar Categoria\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;
        cin.ignore();

        switch(opcion)
        {
            case 1:
                agregarCategoria();
                break;

            case 2:
                modificarCategoria();
                break;
        }

    } while(opcion != 0);
}

void MenuAdministrador::agregarCategoria()
{
    string nombre;
    string descripcion;

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Descripcion: ";
    getline(cin, descripcion);

    TipoRet ret =
        adminController.agregarCategoria(
            nombre,
            descripcion
        );

    if(ret == OK)
        cout << "Categoria agregada correctamente.\n";

    else if(ret == ERROR_CATEGORIA_EXISTENTE)
        cout << "Ya existe una categoria con ese nombre.\n";
}

void MenuAdministrador::modificarCategoria()
{
    string nombreActual;
    string nuevoNombre;
    string nuevaDescripcion;

    cout << "Nombre actual: ";
    getline(cin, nombreActual);

    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);

    cout << "Nueva descripcion: ";
    getline(cin, nuevaDescripcion);

    TipoRet ret =
        adminController.modificarCategoria(
            nombreActual,
            nuevoNombre,
            nuevaDescripcion
        );

    if(ret == OK)
        cout << "Categoria modificada correctamente.\n";

    else if(ret == ERROR_CATEGORIA_INEXISTENTE)
        cout << "Categoria inexistente.\n";

    else if(ret == ERROR_CATEGORIA_EXISTENTE)
        cout << "Ya existe una categoria con ese nombre.\n";
}

void MenuAdministrador::menuProductos()
{
    int opcion;

    do
    {
        cout << "\n===== PRODUCTOS =====\n";
        cout << "1. Agregar Producto\n";
        cout << "2. Modificar Producto\n";
        cout << "3. Eliminar Producto\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;
        cin.ignore();

        switch(opcion)
        {
            case 1:
                agregarProducto();
                break;

            case 2:
                modificarProducto();
                break;

            case 3:
                eliminarProducto();
                break;
        }

    } while(opcion != 0);
}

void MenuAdministrador::agregarProducto()
{
    cout << "\nCU Agregar Producto\n";
}

void MenuAdministrador::modificarProducto()
{
    cout << "\nCU Modificar Producto\n";
}

void MenuAdministrador::eliminarProducto()
{
    cout << "\nCU Eliminar Producto\n";
}

void MenuAdministrador::menuProveedores()
{
    int opcion;

    do
    {
        cout << "\n===== PROVEEDORES =====\n";
        cout << "1. Alta de Proveedor\n";
        cout << "2. Modificar Proveedor\n";
        cout << "3. Registrar Proveedor-Producto\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;
        cin.ignore();

        switch(opcion)
        {
            case 1:
                altaProveedor();
                break;

            case 2:
                modificarProveedor();
                break;

            case 3:
                registrarProveedorProducto();
                break;
        }

    } while(opcion != 0);
}

void MenuAdministrador::altaProveedor()
{
    cout << "\nCU Alta Proveedor\n";
}

void MenuAdministrador::modificarProveedor()
{
    cout << "\nCU Modificar Proveedor\n";
}

void MenuAdministrador::registrarProveedorProducto()
{
    cout << "\nCU Registrar Proveedor-Producto\n";
}

void MenuAdministrador::menuCalificaciones()
{
    cout << "\nConsulta de calificaciones.\n";
}

void MenuAdministrador::menuStock()
{
    cout << "\nGestion de stock.\n";
}

void MenuAdministrador::menuReportes()
{
    cout << "\nReportes.\n";
}

void MenuAdministrador::menuInfoProducto()
{
    cout << "\nInformacion detallada de productos.\n";
}
