#include "vista/MenuAdministrador.h"
#include "vista/InputUtils.h"
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

        opcion = leerEntero();

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

// ============ CATEGORIAS ============

void MenuAdministrador::menuCategorias()
{
    int opcion;

    do
    {
        cout << "\n===== CATEGORIAS =====\n";
        cout << "1. Listar Categorias\n";
        cout << "2. Agregar Categoria\n";
        cout << "3. Modificar Categoria\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            listarCategorias();
            break;
        case 2:
            agregarCategoria();
            break;
        case 3:
            modificarCategoria();
            break;
        case 0:
            break;
        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
}

void MenuAdministrador::listarCategorias()
{
    cout << "\n===== LISTADO DE CATEGORIAS =====\n";

    vector<Categoria *> categorias = adminController.listarCategorias();

    if (categorias.empty())
    {
        cout << "No hay categorias registradas.\n";
        return;
    }

    cout << "\nTotal: " << categorias.size() << " categoria(s)\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < (int)categorias.size(); i++)
    {
        cout << (i + 1) << ". Nombre: " << categorias[i]->getNombre() << "\n";
        cout << "   Descripcion: " << categorias[i]->getDescripcion() << "\n";
        cout << "-------------------------------------------\n";
    }
}

void MenuAdministrador::agregarCategoria()
{
    string nombre;
    string descripcion;

    cout << "\n===== AGREGAR CATEGORIA =====\n";

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Descripcion: ";
    getline(cin, descripcion);

    TipoRet ret = adminController.agregarCategoria(nombre, descripcion);

    if (ret == TipoRet::OK)
        cout << "\nCategoria agregada correctamente.\n";
    else if (ret == TipoRet::ERROR_CATEGORIA_EXISTENTE)
        cout << "\nError: Ya existe una categoria con ese nombre.\n";
}

void MenuAdministrador::modificarCategoria()
{
    cout << "\n===== MODIFICAR CATEGORIA =====\n";
    cout << "\n--- CATEGORIAS DISPONIBLES ---\n";

    vector<Categoria *> categorias = adminController.listarCategorias();

    if (categorias.empty())
    {
        cout << "No hay categorias registradas.\n";
        return;
    }

    for (int i = 0; i < (int)categorias.size(); i++)
    {
        cout << (i + 1) << ". " << categorias[i]->getNombre() << "\n";
    }

    string nombreActual;
    string nuevoNombre;
    string nuevaDescripcion;

    cout << "\nNombre actual (copiar de la lista): ";
    getline(cin, nombreActual);

    Categoria *categoriaBuscada = adminController.buscarCategoria(nombreActual);
    if (categoriaBuscada == nullptr)
    {
        cout << "\nError: Categoria no encontrada.\n";
        return;
    }

    cout << "\n--- DATOS ACTUALES ---\n";
    cout << "Nombre: " << categoriaBuscada->getNombre() << "\n";
    cout << "Descripcion: " << categoriaBuscada->getDescripcion() << "\n";

    cout << "\nNuevo nombre: ";
    getline(cin, nuevoNombre);

    cout << "Nueva descripcion: ";
    getline(cin, nuevaDescripcion);

    cout << "\n--- CAMBIOS A REALIZAR ---\n";
    cout << "Nombre: " << categoriaBuscada->getNombre() << " -> " << nuevoNombre << "\n";
    cout << "Descripcion: " << categoriaBuscada->getDescripcion() << " -> " << nuevaDescripcion << "\n";

    char confirmar;
    cout << "\nConfirmar modificacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet ret = adminController.modificarCategoria(nombreActual, nuevoNombre, nuevaDescripcion);

    if (ret == TipoRet::OK)
        cout << "\nCategoria modificada correctamente.\n";
    else if (ret == TipoRet::ERROR_CATEGORIA_INEXISTENTE)
        cout << "\nError: Categoria inexistente.\n";
    else if (ret == TipoRet::ERROR_CATEGORIA_EXISTENTE)
        cout << "\nError: Ya existe una categoria con ese nombre.\n";
}

// ============ PRODUCTOS ============

void MenuAdministrador::menuProductos()
{
    int opcion;

    do
    {
        cout << "\n===== PRODUCTOS =====\n";
        cout << "1. Listar Productos\n";
        cout << "2. Agregar Producto\n";
        cout << "3. Modificar Producto\n";
        cout << "4. Eliminar Producto\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            listarProductos();
            break;
        case 2:
            agregarProducto();
            break;
        case 3:
            modificarProducto();
            break;
        case 4:
            eliminarProducto();
            break;
        case 0:
            break;
        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
}

void MenuAdministrador::listarProductos()
{
    cout << "\n===== LISTADO DE PRODUCTOS =====\n";

    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    cout << "\nTotal: " << productos.size() << " producto(s)\n";
    cout << "===================================================\n";

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". CODIGO: " << productos[i]->getCodigo() << "\n";
        cout << "   Nombre: " << productos[i]->getNombre() << "\n";
        cout << "   Descripcion: " << productos[i]->getDescripcion() << "\n";
        cout << "   Precio: $" << productos[i]->getPrecioUnitario() << "\n";
        cout << "   Stock Actual: " << productos[i]->getStockActual() << " unidades\n";
        cout << "   Stock Minimo: " << productos[i]->getStockMinimo() << " unidades\n";
        cout << "   Categoria: " << (productos[i]->getCategoria() ? productos[i]->getCategoria()->getNombre() : "Sin categoria") << "\n";
        cout << "===================================================\n";
    }
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
    codigo = leerEntero();

    cout << "Nombre: ";
    nombre = leerLineaNoVacia();

    cout << "Descripcion: ";
    descripcion = leerLineaNoVacia();

    cout << "Precio unitario: ";
    precioUnitario = leerFlotante();

    cout << "Stock actual: ";
    stockActual = leerEntero();

    cout << "Stock minimo: ";
    stockMinimo = leerEntero();

    cout << "Categoria: ";
    nombreCategoria = leerLineaNoVacia();

    Categoria *categoria = adminController.buscarCategoria(nombreCategoria);

    cout << "\n--- RESUMEN DEL NUEVO PRODUCTO ---\n";
    cout << "Codigo: " << codigo << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Precio: $" << precioUnitario << "\n";
    cout << "Stock Actual: " << stockActual << "\n";
    cout << "Stock Minimo: " << stockMinimo << "\n";
    cout << "Categoria: " << (categoria ? categoria->getNombre() : "Sin categoria") << "\n";

    char confirmar;
    cout << "\nConfirmar creacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet ret = adminController.agregarProducto(codigo, nombre, descripcion, precioUnitario, stockActual, stockMinimo, categoria);

    if (ret == TipoRet::OK)
        cout << "\nProducto agregado correctamente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_EXISTENTE)
        cout << "\nError: Ya existe un producto con ese codigo.\n";
    else if (ret == TipoRet::ERROR_STOCK_NEGATIVO)
        cout << "\nError: El stock y el stock minimo no pueden ser negativos.\n";
}

void MenuAdministrador::modificarProducto()
{
    cout << "\n===== MODIFICAR PRODUCTO =====\n";
    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";

    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre() << "\n";
    }

    int codigo;
    cout << "\nCodigo del producto a modificar: ";
    codigo = leerEntero();

    Producto *productoBuscado = adminController.buscarProducto(codigo);
    if (productoBuscado == nullptr)
    {
        cout << "\nError: Producto no encontrado.\n";
        return;
    }

    cout << "\n--- DATOS ACTUALES ---\n";
    cout << "Codigo: " << productoBuscado->getCodigo() << "\n";
    cout << "Nombre: " << productoBuscado->getNombre() << "\n";
    cout << "Descripcion: " << productoBuscado->getDescripcion() << "\n";
    cout << "Precio: $" << productoBuscado->getPrecioUnitario() << "\n";
    cout << "Stock Minimo: " << productoBuscado->getStockMinimo() << "\n";
    cout << "Categoria: " << (productoBuscado->getCategoria() ? productoBuscado->getCategoria()->getNombre() : "Sin categoria") << "\n";

    string nombre;
    string descripcion;
    float precioUnitario;
    int stockMinimo;
    string nombreCategoria;

    cout << "\nNuevo nombre: ";
    nombre = leerLineaNoVacia();

    cout << "Nueva descripcion: ";
    descripcion = leerLineaNoVacia();

    cout << "Nuevo precio: ";
    precioUnitario = leerFlotante();

    cout << "Nuevo stock minimo: ";
    stockMinimo = leerEntero();

    cout << "Nueva categoria: ";
    nombreCategoria = leerLineaNoVacia();

    Categoria *categoria = adminController.buscarCategoria(nombreCategoria);

    cout << "\n--- CAMBIOS A REALIZAR ---\n";
    cout << "Nombre: " << productoBuscado->getNombre() << " -> " << nombre << "\n";
    cout << "Precio: $" << productoBuscado->getPrecioUnitario() << " -> $" << precioUnitario << "\n";
    cout << "Stock Minimo: " << productoBuscado->getStockMinimo() << " -> " << stockMinimo << "\n";

    char confirmar;
    cout << "\nConfirmar modificacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet ret = adminController.modificarProducto(codigo, nombre, descripcion, precioUnitario, categoria, stockMinimo);

    if (ret == TipoRet::OK)
        cout << "\nProducto modificado correctamente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "\nError: Producto inexistente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_EXISTENTE)
        cout << "\nError: Ya existe un producto con ese nombre.\n";
    else if (ret == TipoRet::ERROR_STOCK_NEGATIVO)
        cout << "\nError: El stock minimo no puede ser negativo.\n";
}

void MenuAdministrador::eliminarProducto()
{
    cout << "\n===== ELIMINAR PRODUCTO =====\n";
    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";

    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre() << "\n";
    }

    int codigo;
    cout << "\nCodigo del producto a eliminar: ";
    codigo = leerEntero();

    Producto *productoBuscado = adminController.buscarProducto(codigo);
    if (productoBuscado == nullptr)
    {
        cout << "\nError: Producto no encontrado.\n";
        return;
    }

    cout << "\n--- PRODUCTO A ELIMINAR ---\n";
    cout << "Codigo: " << productoBuscado->getCodigo() << "\n";
    cout << "Nombre: " << productoBuscado->getNombre() << "\n";
    cout << "Precio: $" << productoBuscado->getPrecioUnitario() << "\n";
    cout << "Stock: " << productoBuscado->getStockActual() << "\n";

    char confirmar;
    cout << "\nConfirmar eliminacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet ret = EmpleadoController::getInstancia()->eliminarProducto(codigo);

    if (ret == TipoRet::OK)
        cout << "\nProducto eliminado correctamente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "\nError: Producto inexistente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_CON_VENTAS)
        cout << "\nError: No se puede eliminar, el producto tiene ventas registradas.\n";
    else if (ret == TipoRet::ERROR_ORDEN_PENDIENTE)
        cout << "\nError: No se puede eliminar, el producto tiene ordenes de compra pendientes.\n";
}

// ============ PROVEEDORES ============

void MenuAdministrador::menuProveedores()
{
    int opcion;

    do
    {
        cout << "\n===== PROVEEDORES =====\n";
        cout << "1. Listar Proveedores\n";
        cout << "2. Alta de Proveedor\n";
        cout << "3. Modificar Proveedor\n";
        cout << "4. Registrar Proveedor-Producto\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            listarProveedores();
            break;
        case 2:
            altaProveedor();
            break;
        case 3:
            modificarProveedor();
            break;
        case 4:
            registrarProveedorProducto();
            break;
        case 0:
            break;
        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
}

void MenuAdministrador::listarProveedores()
{
    cout << "\n===== LISTADO DE PROVEEDORES =====\n";

    vector<Proveedor *> proveedores = adminController.listarProveedores();

    if (proveedores.empty())
    {
        cout << "No hay proveedores registrados.\n";
        return;
    }

    cout << "\nTotal: " << proveedores.size() << " proveedor(es)\n";
    cout << "===================================================\n";

    for (int i = 0; i < (int)proveedores.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << proveedores[i]->getRut() << "\n";
        cout << "   Nombre Empresa: " << proveedores[i]->getNombreEmpresa() << "\n";
        cout << "   Telefono: " << proveedores[i]->getTelefono() << "\n";
        cout << "   Nombre Contacto: " << proveedores[i]->getNombreContacto() << "\n";
        cout << "===================================================\n";
    }
}

void MenuAdministrador::altaProveedor()
{
    int rut;
    string nombreEmpresa;
    string telefono;
    string nombreContacto;

    cout << "\n===== ALTA DE PROVEEDOR =====\n";

    cout << "RUT: ";
    rut = leerEntero();

    cout << "Nombre empresa: ";
    nombreEmpresa = leerLineaNoVacia();

    do {
        cout << "Telefono (9 digitos, empezar con 0): ";
        telefono = leerLineaNoVacia();
        if (validarTelefono(telefono) != TipoRet::OK)
            cout << "Telefono invalido. Debe tener 9 digitos y empezar con 0.\n";
    } while (validarTelefono(telefono) != TipoRet::OK);

    cout << "Nombre contacto: ";
    nombreContacto = leerLineaNoVacia();

    cout << "\n--- RESUMEN DEL NUEVO PROVEEDOR ---\n";
    cout << "RUT: " << rut << "\n";
    cout << "Nombre Empresa: " << nombreEmpresa << "\n";
    cout << "Telefono: " << telefono << "\n";
    cout << "Nombre Contacto: " << nombreContacto << "\n";

    char confirmar;
    cout << "\nConfirmar creacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet ret = adminController.agregarProveedor(rut, nombreEmpresa, stoi(telefono), nombreContacto);

    if (ret == TipoRet::OK)
        cout << "\nProveedor agregado correctamente.\n";
    else if (ret == TipoRet::ERROR_PROVEEDOR_EXISTENTE)
        cout << "\nError: Ya existe un proveedor con ese RUT.\n";
}

void MenuAdministrador::modificarProveedor()
{
    cout << "\n===== MODIFICAR PROVEEDOR =====\n";
    cout << "\n--- PROVEEDORES DISPONIBLES ---\n";

    vector<Proveedor *> proveedores = adminController.listarProveedores();

    if (proveedores.empty())
    {
        cout << "No hay proveedores registrados.\n";
        return;
    }

    for (int i = 0; i < (int)proveedores.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << proveedores[i]->getRut()
             << " | " << proveedores[i]->getNombreEmpresa() << "\n";
    }

    int rut;
    cout << "\nRUT del proveedor a modificar: ";
    rut = leerEntero();

    Proveedor *proveedorBuscado = adminController.buscarProveedor(rut);
    if (proveedorBuscado == nullptr)
    {
        cout << "\nError: Proveedor no encontrado.\n";
        return;
    }

    cout << "\n--- DATOS ACTUALES ---\n";
    cout << "RUT: " << proveedorBuscado->getRut() << "\n";
    cout << "Nombre Empresa: " << proveedorBuscado->getNombreEmpresa() << "\n";
    cout << "Telefono: " << proveedorBuscado->getTelefono() << "\n";
    cout << "Nombre Contacto: " << proveedorBuscado->getNombreContacto() << "\n";

    string nombreEmpresa;
    string telefono;
    string nombreContacto;

    cout << "\nNuevo nombre empresa: ";
    nombreEmpresa = leerLineaNoVacia();

    do {
        cout << "Nuevo telefono (9 digitos, empezar con 0): ";
        telefono = leerLineaNoVacia();
        if (validarTelefono(telefono) != TipoRet::OK)
            cout << "Telefono invalido. Debe tener 9 digitos y empezar con 0.\n";
    } while (validarTelefono(telefono) != TipoRet::OK);

    cout << "Nuevo nombre contacto: ";
    nombreContacto = leerLineaNoVacia();

    cout << "\n--- CAMBIOS A REALIZAR ---\n";
    cout << "Nombre Empresa: " << proveedorBuscado->getNombreEmpresa() << " -> " << nombreEmpresa << "\n";
    cout << "Telefono: " << proveedorBuscado->getTelefono() << " -> " << telefono << "\n";

    char confirmar;
    cout << "\nConfirmar modificacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada.\n";
        return;
    }

    TipoRet ret = adminController.modificarProveedor(rut, nombreEmpresa, stoi(telefono), nombreContacto);

    if (ret == TipoRet::OK)
        cout << "\nProveedor modificado correctamente.\n";
    else if (ret == TipoRet::ERROR_PROVEEDOR_INEXISTENTE)
        cout << "\nError: Proveedor inexistente.\n";
}

void MenuAdministrador::registrarProveedorProducto()
{
    cout << "\n===== ASOCIAR PROVEEDOR - PRODUCTO =====\n";

    // LISTAR PROVEEDORES
    cout << "\n--- PROVEEDORES DISPONIBLES ---\n";
    vector<Proveedor *> proveedores = adminController.listarProveedores();

    if (proveedores.empty())
    {
        cout << "No hay proveedores registrados.\n";
        return;
    }

    for (int i = 0; i < (int)proveedores.size(); i++)
    {
        cout << (i + 1) << ". RUT: " << proveedores[i]->getRut()
             << " | " << proveedores[i]->getNombreEmpresa() << "\n";
    }

    // LISTAR PRODUCTOS
    cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". Codigo: " << productos[i]->getCodigo()
             << " | " << productos[i]->getNombre() << "\n";
    }

    // SOLICITAR DATOS
    int rutProveedor;
    int codigoProducto;
    float precioCompra;
    int dia, mes, anio;

    cout << "\nRUT proveedor: ";
    rutProveedor = leerEntero();

    cout << "Codigo producto: ";
    codigoProducto = leerEntero();

    cout << "Precio de compra: ";
    precioCompra = leerFlotante();

    TipoRet retFecha;
    do {
        cout << "\nFecha de entrega estimada (>= 01/01/2026):\n";
        cout << "Anio: "; anio = leerEntero();
        cout << "Mes (1-12): "; mes = leerEntero();
        cout << "Dia (1-31): "; dia = leerEntero();
        retFecha = validarFecha(dia, mes, anio);
        if (retFecha != TipoRet::OK)
            cout << "Fecha invalida. Verifique anio >= 2026, mes 1-12 y dia valido para el mes.\n";
    } while (retFecha != TipoRet::OK);

    Fecha *fechaEntrega = new Fecha(dia, mes, anio, 0, 0, 0);

    TipoRet ret = adminController.asociarProveedorProducto(rutProveedor, codigoProducto, precioCompra, fechaEntrega);

    delete fechaEntrega;

    if (ret == TipoRet::OK)
        cout << "\nAsociacion registrada correctamente.\n";
    else if (ret == TipoRet::ERROR_PROVEEDOR_INEXISTENTE)
        cout << "\nError: Proveedor inexistente.\n";
    else if (ret == TipoRet::ERROR_PRODUCTO_INEXISTENTE)
        cout << "\nError: Producto inexistente.\n";
}

// ============ USUARIOS (EMPLEADOS) ============

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
        opcion = leerEntero();

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
    nombre = leerLineaNoVacia();

    do {
        cout << "Email (debe contener @ y .): ";
        email = leerLineaNoVacia();
        if (validarEmail(email) != TipoRet::OK)
            cout << "Email invalido. Debe contener @ y .\n";
    } while (validarEmail(email) != TipoRet::OK);

    cout << "Contrasenia: ";
    password = leerLineaNoVacia();

    cout << "\nSeleccione el rol:\n";
    cout << "1 - Empleado\n";
    cout << "2 - Administrador\n";
    cout << "Opcion: ";
    opcionRol = leerEntero();

    Rol rol = (opcionRol == 2) ? Rol::ADMINISTRADOR : Rol::EMPLEADO;

    cout << "\n=== RESUMEN ===\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Email: " << email << "\n";
    cout << "Rol: " << (rol == Rol::ADMINISTRADOR ? "Administrador" : "Empleado") << "\n";

    char confirmar;
    cout << "\nConfirmar la creacion del usuario? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada\n";
        return;
    }

    TipoRet ret = adminController.agregarUsuario(nombre, email, password, rol);

    if (ret == TipoRet::OK)
        cout << "\nUsuario registrado correctamente\n";
    else
        cout << "\nError: Ya existe un usuario con ese email\n";
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

    cout << "\n" << usuarios.size() << " usuario(s) encontrado(s):\n\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < (int)usuarios.size(); i++)
    {
        cout << "Usuario " << (i + 1) << ":\n";
        cout << "  Nombre: " << usuarios[i]->getNombreCompleto() << "\n";
        cout << "  Email: " << usuarios[i]->getEmail() << "\n";
        cout << "  Rol: " << (usuarios[i]->getRol() == Rol::ADMINISTRADOR ? "Administrador" : "Empleado") << "\n";
        cout << "-------------------------------------------\n";
    }
}

void MenuAdministrador::eliminarUsuario()
{
    cout << "\n=== ELIMINAR USUARIO ===\n";
    cout << "\n--- USUARIOS DISPONIBLES ---\n";

    vector<Usuario *> usuarios = adminController.listarUsuarios();

    if (usuarios.empty())
    {
        cout << "No hay usuarios registrados\n";
        return;
    }

    for (int i = 0; i < (int)usuarios.size(); i++)
    {
        cout << (i + 1) << ". " << usuarios[i]->getEmail()
             << " (" << usuarios[i]->getNombreCompleto() << ")\n";
    }

    string email;
    cout << "\nEmail del usuario a eliminar (copiar de la lista): ";
    getline(cin, email);

    Usuario *usuario = adminController.buscarUsuarioPorEmail(email);

    if (usuario == nullptr)
    {
        cout << "\nError: Usuario no encontrado\n";
        return;
    }

    cout << "\n--- DATOS DEL USUARIO A ELIMINAR ---\n";
    cout << "Nombre: " << usuario->getNombreCompleto() << "\n";
    cout << "Email: " << usuario->getEmail() << "\n";
    cout << "Rol: " << (usuario->getRol() == Rol::ADMINISTRADOR ? "Administrador" : "Empleado") << "\n";

    char confirmar;
    cout << "\nConfirmar la eliminacion? (S/N): ";
    cin >> confirmar;
    cin.ignore();

    if (toupper(confirmar) != 'S')
    {
        cout << "Operacion cancelada\n";
        return;
    }

    TipoRet ret = adminController.eliminarUsuario(email);

    if (ret == TipoRet::OK)
        cout << "\nUsuario eliminado correctamente\n";
    else
        cout << "\nError al eliminar el usuario\n";
}

// ============ CALIFICACIONES ============

void MenuAdministrador::menuCalificaciones()
{
    int codigo;

    cout << "\n===== CONSULTA DE CALIFICACIONES =====\n";

    cout << "Codigo del producto: ";
    codigo = leerEntero();

    Producto *producto = adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "Producto inexistente.\n";
        return;
    }

    cout << "\nProducto: " << producto->getNombre() << "\n";
    cout << "===================================================\n";

    vector<Calificacion *> calificaciones = EmpleadoController::getInstancia()->consultarCalificacionesDeProducto(codigo);

    if (calificaciones.empty())
    {
        cout << "No hay calificaciones para este producto.\n";
    }
    else
    {
        cout << "Total de calificaciones: " << calificaciones.size() << "\n\n";
        for (Calificacion *cal : calificaciones)
        {
            cout << "Puntaje: " << cal->getPuntaje() << "/5\n";
            cout << "Comentario: " << (cal->getComentarioOpcional().empty() ? "(sin comentario)" : cal->getComentarioOpcional()) << "\n";
            cout << "---\n";
        }
    }
}

// ============ STOCK ============

void MenuAdministrador::menuStock()
{
    int opcion;

    do
    {
        cout << "\n===== GESTION DE STOCK =====\n";
        cout << "1. Listar Stock de Productos\n";
        cout << "2. Consultar Stock de Producto Especifico\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            listarStock();
            break;
        case 2:
            consultarStockProducto();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);
}

void MenuAdministrador::listarStock()
{
    cout << "\n===== STOCK DE PRODUCTOS =====\n";

    vector<Producto *> productos = adminController.listarProductos();

    if (productos.empty())
    {
        cout << "No hay productos registrados.\n";
        return;
    }

    cout << "\nTotal: " << productos.size() << " producto(s)\n";
    cout << "===================================================\n";

    for (int i = 0; i < (int)productos.size(); i++)
    {
        cout << (i + 1) << ". " << productos[i]->getNombre() << "\n";
        cout << "   Codigo: " << productos[i]->getCodigo() << "\n";
        cout << "   Stock Actual: " << productos[i]->getStockActual() << "\n";
        cout << "   Stock Minimo: " << productos[i]->getStockMinimo() << "\n";

        if (productos[i]->getStockActual() <= productos[i]->getStockMinimo())
        {
            cout << "   ALERTA: Stock bajo o igual al minimo!\n";
        }
        cout << "---------------------------------------------------\n";
    }
}

void MenuAdministrador::consultarStockProducto()
{
    int codigo;

    cout << "\n===== CONSULTAR STOCK =====\n";
    cout << "Codigo del producto: ";
    codigo = leerEntero();

    Producto *producto = adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "Producto no encontrado.\n";
        return;
    }

    cout << "\nProducto: " << producto->getNombre() << "\n";
    cout << "Stock Actual: " << producto->getStockActual() << "\n";
    cout << "Stock Minimo: " << producto->getStockMinimo() << "\n";

    if (producto->getStockActual() <= producto->getStockMinimo())
    {
        cout << "ALERTA: Stock bajo o igual al minimo!\n";
    }
}

// ============ REPORTES ============

void MenuAdministrador::menuReportes()
{
    int opcion;

    do
    {
        cout << "\n===== REPORTES =====\n";
        cout << "1. Productos Bajo Stock Minimo\n";
        cout << "2. Unidades Vendidas por Producto\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
        {
            cout << "\n===== PRODUCTOS BAJO STOCK MINIMO =====\n";

            vector<Producto *> productos = adminController.listarProductos();
            vector<Producto *> bajos;

            for (Producto *p : productos)
                if (p->getStockActual() <= p->getStockMinimo())
                    bajos.push_back(p);

            if (bajos.empty())
            {
                cout << "No hay productos bajo el stock minimo.\n";
            }
            else
            {
                cout << "\nProductos con stock bajo o igual al minimo:\n";
                cout << "===================================================\n";
                for (Producto *p : bajos)
                {
                    cout << "Codigo: " << p->getCodigo() << "\n";
                    cout << "Nombre: " << p->getNombre() << "\n";
                    cout << "Stock actual: " << p->getStockActual() << "\n";
                    cout << "Stock minimo: " << p->getStockMinimo() << "\n";
                    cout << "===================================================\n";
                }
            }
            break;
        }

        case 2:
        {
            cout << "\n===== UNIDADES VENDIDAS POR PRODUCTO =====\n";

            vector<Producto *> productos = adminController.listarProductos();

            if (productos.empty())
            {
                cout << "No hay productos registrados.\n";
            }
            else
            {
                cout << "===================================================\n";
                for (Producto *p : productos)
                {
                    cout << "Codigo: " << p->getCodigo() << "\n";
                    cout << "Nombre: " << p->getNombre() << "\n";
                    cout << "Unidades vendidas: " << p->getUnidadesVendidas() << "\n";
                    cout << "===================================================\n";
                }
            }
            break;
        }

        case 0:
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while (opcion != 0);
}

// ============ INFORMACION DE PRODUCTOS ============

void MenuAdministrador::menuInfoProducto()
{
    int codigo;

    cout << "\n===== INFORMACION DE PRODUCTO =====\n";
    cout << "Codigo del producto: ";
    codigo = leerEntero();

    Producto *producto = adminController.buscarProducto(codigo);

    if (producto == nullptr)
    {
        cout << "Producto no encontrado.\n";
        return;
    }

    cout << "\n===== DATOS DEL PRODUCTO =====\n";
    cout << "Codigo: " << producto->getCodigo() << "\n";
    cout << "Nombre: " << producto->getNombre() << "\n";
    cout << "Descripcion: " << producto->getDescripcion() << "\n";
    cout << "Precio: $" << producto->getPrecioUnitario() << "\n";
    cout << "Categoria: " << (producto->getCategoria() ? producto->getCategoria()->getNombre() : "Sin categoria") << "\n";
    cout << "Stock disponible: " << producto->getStockActual() << " unidades\n";
    cout << "Stock minimo: " << producto->getStockMinimo() << " unidades\n";
    cout << "PuntajePromedio: " << producto->getPuntajePromedio() << "/5\n";
    cout << "Unidades vendidas: " << producto->getUnidadesVendidas() << "\n";
}

