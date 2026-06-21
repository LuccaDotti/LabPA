#include "vista/MenuAdministrador.h"
#include "logica/controladores/AdminController.h"
#include "logica/controladores/tipoRetorno.h"
#include "logica/controladores/Rol.h"
#include "logica/dominio/Usuario.h"
#include "logica/controladores/EmpleadoController.h"

#include <iostream>

using namespace std;

MenuAdministrador::MenuAdministrador(
    AdminController &adminController)
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
        cout << "4. Gestion de Empleados\n";
        cout << "5. Consulta de Calificaciones\n";
        cout << "6. Gestion de Stock\n";
        cout << "7. Reportes\n";
        cout << "8. Informacion de Productos\n";
        cout << "0. Cerrar Sesion\n";
        cout << "Opcion: ";

        cin >> opcion;
        cin.ignore();

        switch (opcion)
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
            menuUsuarios();
            break;

        case 5:
            menuCalificaciones();
            break;

        case 6:
            menuStock();
            break;

        case 7:
            menuReportes();
            break;

        case 8:
            menuInfoProducto();
            break;

        case 0:
            cout << "\nSesion cerrada.\n";
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
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

        switch (opcion)
        {
        case 1:
            agregarCategoria();
            break;

        case 2:
            modificarCategoria();
            break;

        case 0:
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
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

    if (ret == TipoRet::OK)
        cout << "Categoria agregada correctamente.\n";

    else if (ret == TipoRet::ERROR_CATEGORIA_EXISTENTE)
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

    if (ret == TipoRet::OK)
        cout << "Categoria modificada correctamente.\n";

    else if (ret == TipoRet::ERROR_CATEGORIA_INEXISTENTE)
        cout << "Categoria inexistente.\n";

    else if (ret == TipoRet::ERROR_CATEGORIA_EXISTENTE)
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

        switch (opcion)
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

        case 0:
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
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

    Categoria *categoria =
        adminController.buscarCategoria(nombreCategoria);

    TipoRet ret =
        adminController.agregarProducto(codigo, nombre, descripcion, precioUnitario, stockActual, stockMinimo, categoria);

    if (ret == TipoRet::OK)
        cout << "Producto agregado correctamente.\n";

    else if (ret == TipoRet::ERROR_PRODUCTO_EXISTENTE)
        cout << "Ya existe un producto con ese codigo.\n";

    else if (ret == TipoRet::ERROR_STOCK_NEGATIVO)
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

    Categoria *categoria =
        adminController.buscarCategoria(nombreCategoria);

    TipoRet ret =
        adminController.modificarProducto(codigo, nombre, descripcion, precioUnitario, categoria, stockMinimo);

    if (ret == TipoRet::OK)
        cout << "Producto modificado correctamente.\n";

    else if (ret == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "Producto inexistente.\n";

    else if (ret == TipoRet::ERROR_PRODUCTO_EXISTENTE)
        cout << "Ya existe un producto con ese nombre.\n";
}

void MenuAdministrador::eliminarProducto()
{
    int codigo;

    cout << "\n===== ELIMINAR PRODUCTO =====\n";
    cout << "Codigo del producto: ";
    cin >> codigo;

    TipoRet ret = EmpleadoController::getInstancia()->eliminarProducto(codigo);

    if (ret == TipoRet::OK)
        cout << "Producto eliminado correctamente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "Producto inexistente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_CON_VENTAS)
        cout << "No se puede eliminar: el producto tiene ventas registradas.\n";
    else if (ret == TipoRet::ERROR_ORDEN_PENDIENTE)
        cout << "No se puede eliminar: el producto tiene ordenes de compra pendientes.\n";
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

        switch (opcion)
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

        case 0:
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
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

    if (ret == TipoRet::OK)
        cout << "Proveedor agregado correctamente.\n";

    else if (ret == TipoRet::ERROR_PROVEEDOR_EXISTENTE)
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

    if (ret == TipoRet::OK)
        cout << "Proveedor modificado correctamente.\n";

    else if (ret == TipoRet::ERROR_PROVEEDOR_INEXISTENTE)
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

    Fecha *fechaEntrega =
        new Fecha(dia, mes, anio, 0, 0, 0);

    TipoRet ret =
        adminController.asociarProveedorProducto(rutProveedor, codigoProducto, precioCompra, fechaEntrega);

    delete fechaEntrega;

    if (ret == TipoRet::OK)
        cout << "Asociacion registrada correctamente.\n";

    else if (ret == TipoRet::ERROR_PROVEEDOR_INEXISTENTE)
        cout << "Proveedor inexistente.\n";

    else if (ret == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "Producto inexistente.\n";
}

void MenuAdministrador::menuUsuarios()
{
    int opcion;

    do
    {
        cout << "\n=== MENU GESTION DE USUARIOS ===\n";
        cout << "1. Alta de usuario\n";
        cout << "2. Listar usuarios\n";
        cout << "3. Eliminar usuario\n";
        cout << "0. Volver\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            altaUsuario();
            break;
        case 2:
            listarUsuarios();
            break;
        case 3:
            eliminarUsuario();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 0);
}

void MenuAdministrador::altaUsuario()
{
    string nombre;
    string email;
    string password;
    int opcionRol;

    cout << "\n=== ALTA DE USUARIO ===\n";

    cout << "Nombre completo: ";
    cin.ignore();
    getline(cin, nombre);

    cout << "Email: ";
    getline(cin, email);

    cout << "Contrasenia: ";
    getline(cin, password);

    cout << "\nSeleccione el rol:\n";
    cout << "1 - Empleado\n";
    cout << "2 - Administrador\n";
    cout << "Opcion: ";
    cin >> opcionRol;

    Rol rol = (opcionRol == 2) ? Rol::ADMINISTRADOR : Rol::EMPLEADO;

    cout << "\n=== RESUMEN ===\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Email: " << email << endl;
    cout << "Rol: " << (rol == Rol::ADMINISTRADOR ? "Administrador" : "Empleado") << endl;

    char confirmar;
    cout << "\n¿Confirmar la creacion del usuario? (S/N): ";
    cin >> confirmar;

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada\n";
        return;
    }

    TipoRet ret = adminController.agregarUsuario(nombre, email, password, rol);

    if (ret == TipoRet::OK)
        cout << "\nUsuario registrado correctamente\n";
    else
        cout << "\nYa existe un usuario con ese email\n";
}

void MenuAdministrador::listarUsuarios()
{
    cout << "\n=== LISTADO DE USUARIOS ===\n";

    vector<Usuario *> usuarios = adminController.listarUsuarios();

    if (usuarios.empty())
    {
        cout << "No hay usuarios registrados\n";
        return;
    }

    cout << "\n"
         << usuarios.size() << " usuario(s) encontrado(s):\n\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < usuarios.size(); i++)
    {
        cout << "Usuario " << (i + 1) << ":\n";
        cout << "  Nombre: " << usuarios[i]->getNombreCompleto() << endl;
        cout << "  Email: " << usuarios[i]->getEmail() << endl;
        cout << "  Rol: " << (usuarios[i]->getRol() == Rol::ADMINISTRADOR ? "Administrador" : "Empleado") << endl;
        cout << "-------------------------------------------\n";
    }
}

void MenuAdministrador::eliminarUsuario()
{
    string email;

    cout << "\n=== ELIMINAR USUARIO ===\n";
    cout << "Email del usuario a eliminar: ";
    cin.ignore();
    getline(cin, email);

    Usuario *usuario = adminController.buscarUsuarioPorEmail(email);

    if (usuario == nullptr)
    {
        cout << "Usuario no encontrado\n";
        return;
    }

    cout << "\nDatos del usuario a eliminar:\n";
    cout << "Nombre: " << usuario->getNombreCompleto() << endl;
    cout << "Email: " << usuario->getEmail() << endl;
    cout << "Rol: " << (usuario->getRol() == Rol::ADMINISTRADOR ? "Administrador" : "Empleado") << endl;

    char confirmar;
    cout << "\n¿Confirmar la eliminacion? (S/N): ";
    cin >> confirmar;

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada\n";
        return;
    }

    TipoRet ret = adminController.eliminarUsuario(email);

    if (ret == TipoRet::OK)
        cout << "Usuario eliminado correctamente\n";
    else
        cout << "Error al eliminar el usuario\n";
}

void MenuAdministrador::menuCalificaciones()
{
    int codigo;

    cout << "\n===== CONSULTA DE CALIFICACIONES =====\n";

    cout << "Codigo del producto: ";
    cin >> codigo;

    Producto *producto =
        adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "Producto inexistente.\n";
        return;
    }

    cout << "\nProducto: " << producto->getNombre() << endl;
    cout << "Puntaje promedio: " << producto->getPuntajePromedio() << " / 5\n";
}

void MenuAdministrador::menuStock()
{
    cout << "\n===== GESTION DE STOCK =====\n";

    vector<Producto *> productos =
        adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    cout << "\n"
         << productos.size() << " producto(s) encontrado(s):\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < productos.size(); i++)
    {
        cout << "Codigo: " << productos[i]->getCodigo() << endl;
        cout << "Nombre: " << productos[i]->getNombre() << endl;
        cout << "Stock actual: " << productos[i]->getStockActual() << endl;
        cout << "Stock minimo: " << productos[i]->getStockMinimo() << endl;
        cout << "Bajo stock: " << (productos[i]->isBajoStock() ? "Si" : "No") << endl;
        cout << "-------------------------------------------\n";
    }
}

void MenuAdministrador::menuReportes()
{
    cout << "\n===== REPORTES =====\n";

    vector<Producto *> productos =
        adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    cout << "\n--- Productos bajo stock minimo ---\n";

    bool hayBajoStock = false;

    for (int i = 0; i < productos.size(); i++)
    {
        if (productos[i]->isBajoStock())
        {
            hayBajoStock = true;
            cout << "Codigo: " << productos[i]->getCodigo()
                 << " - " << productos[i]->getNombre()
                 << " (Stock: " << productos[i]->getStockActual()
                 << ", Minimo: " << productos[i]->getStockMinimo() << ")\n";
        }
    }

    if (!hayBajoStock)
        cout << "No hay productos bajo el stock minimo.\n";

    cout << "\n--- Unidades vendidas por producto ---\n";

    for (int i = 0; i < productos.size(); i++)
    {
        cout << "Codigo: " << productos[i]->getCodigo()
             << " - " << productos[i]->getNombre()
             << " - Vendidas: " << productos[i]->getUnidadesVendidas() << endl;
    }
}

void MenuAdministrador::menuInfoProducto()
{
    int codigo;

    cout << "\n===== INFORMACION DETALLADA DE PRODUCTO =====\n";

    cout << "Codigo del producto: ";
    cin >> codigo;

    Producto *producto =
        adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "Producto inexistente.\n";
        return;
    }

    cout << "\nCodigo: " << producto->getCodigo() << endl;
    cout << "Nombre: " << producto->getNombre() << endl;
    cout << "Descripcion: " << producto->getDescripcion() << endl;
    cout << "Precio unitario: " << producto->getPrecioUnitario() << endl;
    cout << "Stock actual: " << producto->getStockActual() << endl;
    cout << "Stock minimo: " << producto->getStockMinimo() << endl;
    cout << "Bajo stock: " << (producto->isBajoStock() ? "Si" : "No") << endl;
    cout << "Puntaje promedio: " << producto->getPuntajePromedio() << " / 5\n";
    cout << "Unidades vendidas: " << producto->getUnidadesVendidas() << endl;

    if (producto->getCategoria() != nullptr)
        cout << "Categoria: " << producto->getCategoria()->getNombre() << endl;
    else
        cout << "Categoria: Sin categoria\n";
}
