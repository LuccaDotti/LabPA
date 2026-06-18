#pragma once
#include "tipoRetorno.h"
#include <vector>

#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/OrdenCompra.h"
#include "logica/dominio/Producto.h"

class AdminController;

using namespace std;

class EmpleadoController
{

private:
    vector<ClienteRegistrado *> clientes;
    vector<OrdenCompra *> ordenesCompra;
    vector<Producto *> productos;

    AdminController &adminController;

public:
    EmpleadoController(
        AdminController &adminController);

    ~EmpleadoController();

    // ====================================
    // CLIENTES REGISTRADOS
    // ====================================

    TipoRet registrarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia, float totalFacturado);
    TipoRet modificarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia);
    TipoRet registrarVenta(int rut, int codigoProducto, int cantidad);

    ClienteRegistrado *buscarCliente(int rut) const;

    vector<ClienteRegistrado *> listarClientes() const;

    // ====================================
    // ORDENES DE COMPRA
    // ====================================

    bool crearOrdenCompra(
        OrdenCompra *orden);

    vector<OrdenCompra *> listarOrdenes() const;
};
