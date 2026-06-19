#include "vista/MenuAdministrador.h"
#include "logica/controladores/AdminController.h"
#include "logica/controladores/tipoRetorno.h"

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
        adminController.agregarCategoria(nombre, descripcion);

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
        adminController.modificarCategoria(nombreActual, nuevoNombre, nuevaDescripcion);

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
    int codigo;
    string nombre;
    string descripcion;
    float precioUnitario;
    int stockActual;
    int stockMinimo;
    string nombreCategoria;

    cout << "\n===== AGREGAR PRODUCTO =====\n";

    cout << "Codigo: ";
    cin >> codigo;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Descripcion: ";
    getline(cin, descripcion);

    cout << "Precio unitario: ";
    cin >> precioUnitario;

    cout << "Stock actual: ";
    cin >> stockActual;

    cout << "Stock minimo: ";
    cin >> stockMinimo;
    cin.ignore();

    cout << "Categoria: ";
    getline(cin, nombreCategoria);

    Categoria* categoria =
        adminController.buscarCategoria(nombreCategoria);

    TipoRet ret =
        adminController.agregarProducto(codigo, nombre, descripcion, precioUnitario, stockActual, stockMinimo, categoria);

    if(ret == OK)
        cout << "Producto agregado correctamente.\n";

    else if(ret == ERROR_PRODUCTO_EXISTENTE)
        cout << "Ya existe un producto con ese codigo.\n";

    else if(ret == ERROR_STOCK_NEGATIVO)
        cout << "El stock no puede ser negativo.\n";
}

void MenuAdministrador::modificarProducto()
{
    int codigo;
    string nombre;
    string descripcion;
    float precioUnitario;
    int stockMinimo;
    string nombreCategoria;

    cout << "\n===== MODIFICAR PRODUCTO =====\n";

    cout << "Codigo: ";
    cin >> codigo;
    cin.ignore();

    cout << "Nuevo nombre: ";
    getline(cin, nombre);

    cout << "Nueva descripcion: ";
    getline(cin, descripcion);

    cout << "Nuevo precio: ";
    cin >> precioUnitario;

    cout << "Nuevo stock minimo: ";
    cin >> stockMinimo;
    cin.ignore();

    cout << "Nueva categoria: ";
    getline(cin, nombreCategoria);

    Categoria* categoria =
        adminController.buscarCategoria(nombreCategoria);

    TipoRet ret =
        adminController.modificarProducto(codigo, nombre, descripcion, precioUnitario, categoria, stockMinimo);

    if(ret == OK)
        cout << "Producto modificado correctamente.\n";

    else if(ret == ERROR_PRODUCTO_INEXISTENTE)
        cout << "Producto inexistente.\n";

    else if(ret == ERROR_PRODUCTO_EXISTENTE)
        cout << "Ya existe un producto con ese nombre.\n";
}

void MenuAdministrador::eliminarProducto()
{
    int codigo;

    cout << "\n===== ELIMINAR PRODUCTO =====\n";

    cout << "Codigo del producto: ";
    cin >> codigo;

    TipoRet ret =
        adminController.eliminarProducto(codigo);

    if(ret == OK)
        cout << "Producto eliminado correctamente.\n";

    else if(ret == ERROR_PRODUCTO_INEXISTENTE)
        cout << "Producto inexistente.\n";
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
    int rut;
    string nombreEmpresa;
    int telefono;
    string nombreContacto;

    cout << "\n===== ALTA DE PROVEEDOR =====\n";

    cout << "RUT: ";
    cin >> rut;
    cin.ignore();

    cout << "Nombre empresa: ";
    getline(cin, nombreEmpresa);

    cout << "Telefono: ";
    cin >> telefono;
    cin.ignore();

    cout << "Nombre contacto: ";
    getline(cin, nombreContacto);

    TipoRet ret =
        adminController.agregarProveedor(rut, nombreEmpresa, telefono, nombreContacto);

    if(ret == OK)
        cout << "Proveedor agregado correctamente.\n";

    else if(ret == ERROR_PROVEEDOR_EXISTENTE)
        cout << "Ya existe un proveedor con ese RUT.\n";
}

void MenuAdministrador::modificarProveedor()
{
    int rut;
    string nombreEmpresa;
    int telefono;
    string nombreContacto;

    cout << "\n===== MODIFICAR PROVEEDOR =====\n";

    cout << "RUT: ";
    cin >> rut;
    cin.ignore();

    cout << "Nuevo nombre empresa: ";
    getline(cin, nombreEmpresa);

    cout << "Nuevo telefono: ";
    cin >> telefono;
    cin.ignore();

    cout << "Nuevo nombre contacto: ";
    getline(cin, nombreContacto);

    TipoRet ret =
        adminController.modificarProveedor(rut, nombreEmpresa, telefono, nombreContacto);

    if(ret == OK)
        cout << "Proveedor modificado correctamente.\n";

    else if(ret == ERROR_PROVEEDOR_INEXISTENTE)
        cout << "Proveedor inexistente.\n";
}

void MenuAdministrador::registrarProveedorProducto()
{
    int rutProveedor;
    int codigoProducto;
    float precioCompra;

    int dia;
    int mes;
    int anio;

    cout << "\n===== ASOCIAR PROVEEDOR - PRODUCTO =====\n";

    cout << "RUT proveedor: ";
    cin >> rutProveedor;

    cout << "Codigo producto: ";
    cin >> codigoProducto;

    cout << "Precio de compra: ";
    cin >> precioCompra;

    cout << "Dia entrega: ";
    cin >> dia;

    cout << "Mes entrega: ";
    cin >> mes;

    cout << "Anio entrega: ";
    cin >> anio;

    Fecha* fechaEntrega =
        new Fecha(dia, mes, anio);

    TipoRet ret =
        adminController.asociarProveedorProducto(rutProveedor, codigoProducto, precioCompra, fechaEntrega);

    delete fechaEntrega;

    if(ret == OK)
        cout << "Asociacion registrada correctamente.\n";

    else if(ret == ERROR_PROVEEDOR_INEXISTENTE)
        cout << "Proveedor inexistente.\n";

    else if(ret == ERROR_PRODUCTO_INEXISTENTE)
        cout << "Producto inexistente.\n";
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
