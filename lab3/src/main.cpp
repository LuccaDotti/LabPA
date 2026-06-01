#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
#include "DtFecha.h"
#include "DtDireccion.h"
#include "Categoria.h"
#include "Producto.h"
#include "Proveedor.h"
#include "ProveedorProducto.h"
#include "OrdenCompra.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
#include "DtFecha.h"
#include "DtDireccion.h"
#include "Categoria.h"
#include "Producto.h"
#include "Proveedor.h"
#include "ProveedorProducto.h"
#include "OrdenCompra.h"
#include "LineaCompra.h"
#include "ClienteRegistrado.h"
#include "Venta.h"
#include "LineaDetalle.h"
#include "Calificacion.h"

// Almacenamiento global
vector<Categoria *> categorias;
vector<Producto *> productos;
vector<ClienteRegistrado *> clientes;
vector<Venta *> ventas;
vector<Proveedor *> proveedores;

void mostrarMenuPrincipal()
{
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1. Gestionar Categorias" << endl;
    cout << "2. Gestionar Productos" << endl;
    cout << "3. Gestionar Clientes" << endl;
    cout << "4. Gestionar Ventas" << endl;
    cout << "5. Gestionar Proveedores" << endl;
    cout << "6. Consultar Datos" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void agregarCategoria()
{
    string nombre, descripcion;
    cout << "\n--- Agregar Categoria ---" << endl;
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);

    Categoria *cat = new Categoria(nombre, descripcion);
    categorias.push_back(cat);
    cout << "Categoria agregada exitosamente." << endl;
}

void listarCategorias()
{
    if (categorias.empty())
    {
        cout << "No hay categorias registradas." << endl;
        return;
    }
    cout << "\n--- Categorias Registradas ---" << endl;
    for (size_t i = 0; i < categorias.size(); i++)
    {
        cout << (i + 1) << ". " << categorias[i]->getNombre() << " - " << categorias[i]->getDescripcion() << endl;
    }
}

void gestionarCategorias()
{
    int opcion;
    while (true)
    {
        cout << "\n--- Gestion de Categorias ---" << endl;
        cout << "1. Agregar categoria" << endl;
        cout << "2. Listar categorias" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0)
            break;
        else if (opcion == 1)
            agregarCategoria();
        else if (opcion == 2)
            listarCategorias();
        else
            cout << "Opcion invalida." << endl;
    }
}

void agregarProducto()
{
    int codigo, stockMin;
    string nombre, descripcion;
    float precio;
    int stock;

    cout << "\n--- Agregar Producto ---" << endl;
    cout << "Codigo: ";
    cin >> codigo;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    cout << "Precio Unitario: $";
    cin >> precio;
    cout << "Stock Actual: ";
    cin >> stock;
    cout << "Stock Minimo: ";
    cin >> stockMin;
    cin.ignore();

    Producto *p = new Producto(codigo, nombre, descripcion, precio, stock, stockMin);

    if (!categorias.empty())
    {
        listarCategorias();
        cout << "Seleccione categoria (numero): ";
        int catIdx;
        cin >> catIdx;
        cin.ignore();
        catIdx--; // Convertir de 1-based a 0-based
        if (catIdx >= 0 && catIdx < (int)categorias.size())
        {
            p->setCategoria(categorias[catIdx]);
        }
    }

    productos.push_back(p);
    cout << "Producto agregado exitosamente." << endl;
}

void listarProductos()
{
    if (productos.empty())
    {
        cout << "No hay productos registrados." << endl;
        return;
    }
    cout << "\n--- Productos Registrados ---" << endl;
    cout << left << setw(5) << "ID" << setw(20) << "Nombre" << setw(12) << "Precio" << setw(10) << "Stock" << setw(15) << "Bajo Stock?" << endl;
    cout << string(62, '-') << endl;

    for (size_t i = 0; i < productos.size(); i++)
    {
        cout << left << setw(5) << (i + 1) << setw(20) << productos[i]->getNombre() << setw(12) << "$" + to_string((int)productos[i]->getPrecioUnitario()) << setw(10) << productos[i]->getStockActual() << (productos[i]->isBajoStock() ? "Si" : "No") << endl;
    }
}

void gestionarProductos()
{
    int opcion;
    while (true)
    {
        cout << "\n--- Gestion de Productos ---" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Listar productos" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0)
            break;
        else if (opcion == 1)
            agregarProducto();
        else if (opcion == 2)
            listarProductos();
        else
            cout << "Opcion invalida." << endl;
    }
}

void agregarCliente()
{
    int rut;
    string calle, ciudad, correo, nombre;
    int numero;

    cout << "\n--- Agregar Cliente ---" << endl;
    cout << "RUT: ";
    cin >> rut;
    cin.ignore();

    cout << "Nombre Completo: ";
    getline(cin, nombre);
    cout << "Correo: ";
    getline(cin, correo);
    cout << "Calle: ";
    getline(cin, calle);
    cout << "Numero: ";
    cin >> numero;
    cin.ignore();
    cout << "Ciudad: ";
    getline(cin, ciudad);

    DtDireccion dir(calle, numero, ciudad);
    ClienteRegistrado *cliente = new ClienteRegistrado(rut, dir, correo, nombre);
    clientes.push_back(cliente);
    cout << "Cliente agregado exitosamente." << endl;
}

void listarClientes()
{
    if (clientes.empty())
    {
        cout << "No hay clientes registrados." << endl;
        return;
    }
    cout << "\n--- Clientes Registrados ---" << endl;
    cout << left << setw(5) << "ID" << setw(12) << "RUT" << setw(25) << "Nombre" << setw(25) << "Correo" << setw(20) << "Total Facturado" << endl;
    cout << string(87, '-') << endl;

    for (size_t i = 0; i < clientes.size(); i++)
    {
        cout << left << setw(5) << (i + 1) << setw(12) << clientes[i]->getRUT() << setw(25) << clientes[i]->getNombreCompleto() << setw(25) << clientes[i]->getCorreo() << "$" << clientes[i]->getTotalFacturado() << endl;
    }
}

void gestionarClientes()
{
    int opcion;
    while (true)
    {
        cout << "\n--- Gestion de Clientes ---" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Listar clientes" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0)
            break;
        else if (opcion == 1)
            agregarCliente();
        else if (opcion == 2)
            listarClientes();
        else
            cout << "Opcion invalida." << endl;
    }
}

void crearVenta()
{
    if (clientes.empty())
    {
        cout << "Debe haber al menos un cliente registrado." << endl;
        return;
    }
    if (productos.empty())
    {
        cout << "Debe haber al menos un producto registrado." << endl;
        return;
    }

    int dia, mes, anio;
    cout << "\n--- Crear Venta ---" << endl;
    cout << "Fecha - Dia: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    cin.ignore();

    listarClientes();
    cout << "Seleccione cliente (numero): ";
    int clienteIdx;
    cin >> clienteIdx;
    cin.ignore();
    clienteIdx--; // Convertir de 1-based a 0-based

    if (clienteIdx < 0 || clienteIdx >= (int)clientes.size())
    {
        cout << "Cliente invalido." << endl;
        return;
    }

    DtFecha fecha(dia, mes, anio);
    Venta *venta = new Venta(fecha, clientes[clienteIdx]);

    bool agregarMas = true;
    while (agregarMas)
    {
        listarProductos();
        cout << "Seleccione producto (numero): ";
        int prodIdx;
        cin >> prodIdx;
        cin.ignore();
        prodIdx--; // Convertir de 1-based a 0-based

        if (prodIdx < 0 || prodIdx >= (int)productos.size())
        {
            cout << "Producto invalido." << endl;
            continue;
        }

        cout << "Cantidad: ";
        int cantidad;
        cin >> cantidad;
        cin.ignore();

        LineaDetalle *ld = new LineaDetalle(productos[prodIdx], cantidad,
                                            productos[prodIdx]->getPrecioUnitario());
        venta->agregarLineaDetalle(ld);
        productos[prodIdx]->agregarUnidadesVendidas(cantidad);
        productos[prodIdx]->setStockActual(productos[prodIdx]->getStockActual() - cantidad);
        clientes[clienteIdx]->agregarFacturado(cantidad * productos[prodIdx]->getPrecioUnitario());

        cout << "Producto agregado. \u00bfAgregar otro? (s/n): ";
        char resp;
        cin >> resp;
        cin.ignore();
        agregarMas = (resp == 's' || resp == 'S');
    }

    ventas.push_back(venta);
    cout << "\nVenta creada. Total: $" << venta->getTotal() << endl;
}

void listarVentas()
{
    if (ventas.empty())
    {
        cout << "No hay ventas registradas." << endl;
        return;
    }
    cout << "\n--- Ventas Registradas ---" << endl;
    for (size_t i = 0; i < ventas.size(); i++)
    {
        ClienteRegistrado *clienteReg = dynamic_cast<ClienteRegistrado *>(ventas[i]->getCliente());
        string nombreCliente = clienteReg ? clienteReg->getNombreCompleto() : "Desconocido";
        cout << (i + 1) << ". Cliente: " << nombreCliente << " | Total: $" << ventas[i]->getTotal() << " | Lineas: " << ventas[i]->getLineas().size() << endl;
    }
}

void gestionarVentas()
{
    int opcion;
    while (true)
    {
        cout << "\n--- Gestion de Ventas ---" << endl;
        cout << "1. Crear venta" << endl;
        cout << "2. Listar ventas" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0)
            break;
        else if (opcion == 1)
            crearVenta();
        else if (opcion == 2)
            listarVentas();
        else
            cout << "Opcion invalida." << endl;
    }
}

void agregarProveedor()
{
    int rut, telefono;
    string nombre, contacto;

    cout << "\n--- Agregar Proveedor ---" << endl;
    cout << "RUT: ";
    cin >> rut;
    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Telefono: ";
    cin >> telefono;
    cin.ignore();
    cout << "Contacto: ";
    getline(cin, contacto);

    Proveedor *prov = new Proveedor(rut, nombre, telefono, contacto);
    proveedores.push_back(prov);
    cout << "Proveedor agregado exitosamente." << endl;
}

void listarProveedores()
{
    if (proveedores.empty())
    {
        cout << "No hay proveedores registrados." << endl;
        return;
    }
    cout << "\n--- Proveedores Registrados ---" << endl;
    for (size_t i = 0; i < proveedores.size(); i++)
    {
        cout << (i + 1) << ". " << proveedores[i]->getNombreEmpresa() << endl;
    }
}

void gestionarProveedores()
{
    int opcion;
    while (true)
    {
        cout << "\n--- Gestion de Proveedores ---" << endl;
        cout << "1. Agregar proveedor" << endl;
        cout << "2. Listar proveedores" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0)
            break;
        else if (opcion == 1)
            agregarProveedor();
        else if (opcion == 2)
            listarProveedores();
        else
            cout << "Opcion invalida." << endl;
    }
}

void consultarDatos()
{
    int opcion;
    while (true)
    {
        cout << "\n--- Consultar Datos ---" << endl;
        cout << "1. Listar categorias" << endl;
        cout << "2. Listar productos" << endl;
        cout << "3. Listar clientes" << endl;
        cout << "4. Listar ventas" << endl;
        cout << "5. Listar proveedores" << endl;
        cout << "0. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0)
            break;
        else if (opcion == 1)
            listarCategorias();
        else if (opcion == 2)
            listarProductos();
        else if (opcion == 3)
            listarClientes();
        else if (opcion == 4)
            listarVentas();
        else if (opcion == 5)
            listarProveedores();
        else
            cout << "Opcion invalida." << endl;
    }
}

int main()
{
    int opcion;

    cout << "========================================" << endl;
    cout << "=== Sistema labDottiMacedoSantos ===" << endl;
    cout << "========================================" << endl;

    while (true)
    {
        mostrarMenuPrincipal();
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            gestionarCategorias();
            break;
        case 2:
            gestionarProductos();
            break;
        case 3:
            gestionarClientes();
            break;
        case 4:
            gestionarVentas();
            break;
        case 5:
            gestionarProveedores();
            break;
        case 6:
            consultarDatos();
            break;
        case 0:
            cout << "Saliendo del programa..." << endl;
            return 0;
        default:
            cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}
