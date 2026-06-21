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
    static EmpleadoController* instancia;

    vector<ClienteRegistrado*> clientes;
    vector<OrdenCompra*> ordenesCompra;

    AdminController* adminController;

    EmpleadoController();

public:
    static EmpleadoController* getInstancia();
    ~EmpleadoController();

    EmpleadoController(const EmpleadoController&) = delete;
    EmpleadoController& operator=(const EmpleadoController&) = delete;

    TipoRet registrarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia, float totalFacturado);
    TipoRet modificarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia);
    TipoRet registrarVenta(int rut, int codigoProducto, int cantidad);
    TipoRet consultarHistorialCompraCliente(int rut, vector<Venta*>& ventas);
    TipoRet emitirOrdenCompra(int codigoProducto, int cantidad, int rutProveedor);
    TipoRet cancelarOrdenCompra(int idOrdenCompra);
    TipoRet registrarRecepcionOrdenCompra(int idOrden, vector<int> cantidadesRecibidas);
    TipoRet eliminarProducto(int codigo);

    Proveedor* buscarProveedor(int rutProveedor) const;
    Producto* buscarProducto(int codigoProducto) const;
    OrdenCompra* buscarOrdenCompra(int idOrdenCompra) const;
    ClienteRegistrado* buscarCliente(int rut) const;

    vector<ClienteRegistrado*> listarClientes() const;
    vector<OrdenCompra*> listarOrdenes() const;
    bool crearOrdenCompra(OrdenCompra* orden);

    vector<Calificacion*> consultarCalificacionesDeProducto(int codigoProducto) const;
    int consultarStockActual(int codigoProducto) const;
    vector<Producto*> consultarProductoBajoMinimo() const;
    float montoTotalFacturadoACliente(int rut) const;
    int unidadesVendidasDeProducto(int codigoProducto) const;
    ClienteRegistrado* buscarClientePorCorreo(const string& correo, const string& password) const;
};
