#pragma once
#include "tipoRetorno.h"
#include <vector>

#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/OrdenCompra.h"
#include "logica/dominio/Producto.h"
#include "logica/dominio/Proveedor.h"
#include "logica/dominio/ProveedorProducto.h"

class AdminController;

using namespace std;

class EmpleadoController
{

private:
    vector<ClienteRegistrado *> clientes;
    vector<OrdenCompra *> ordenesCompra;
    vector<Producto *> productos;
    vector<Proveedor *> proveedores;
    vector<ProveedorProducto *> proveedorProductos;

    AdminController &adminController;

public:
    EmpleadoController(AdminController &adminController);

    ~EmpleadoController();

    // ====================================
    // CLIENTES REGISTRADOS
    // ====================================

    TipoRet registrarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia, float totalFacturado);
    TipoRet modificarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia);
    TipoRet registrarVenta(int rut, int codigoProducto, int cantidad);
    TipoRet consultarHistorialCompraCliente(int rut, vector<Venta *> &ventas);
    TipoRet emitirOrdenCompra(int codigoProducto, int cantidad, int rutProveedor);
    TipoRet cancelarOrdenCompra(int idOrdenCompra);

    Proveedor *buscarProveedor(int codigoProveedor) const;
    Producto *buscarProducto(int codigoProducto) const;
    OrdenCompra *buscarOrdenCompra(int idOrdenCompra) const;
    ClienteRegistrado *buscarCliente(int rut) const;

    vector<ClienteRegistrado *> listarClientes() const;

    // ====================================
    // ORDENES DE COMPRA
    // ====================================

    bool crearOrdenCompra(OrdenCompra *orden);

    vector<OrdenCompra *> listarOrdenes() const;
};
