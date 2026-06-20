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
    static EmpleadoController* instancia;  // ← SINGLETON
    
    vector<ClienteRegistrado *> clientes;
    vector<OrdenCompra *> ordenesCompra;
    vector<Producto *> productos;
    vector<Proveedor *> proveedores;
    vector<ProveedorProducto *> proveedorProductos;
    
    AdminController *adminController;  // ← Cambiar de referencia a puntero
    
    EmpleadoController();  // ← Constructor privado

public:
    static EmpleadoController* getInstancia();  // ← SINGLETON
    ~EmpleadoController();
    
    EmpleadoController(const EmpleadoController&) = delete;  // ← Eliminar copia
    EmpleadoController& operator=(const EmpleadoController&) = delete;  // ← Eliminar asignación
    
    TipoRet registrarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia, float totalFacturado);
    TipoRet modificarCliente(int rut, string nombreCompleto, string correo, int nroPuerta, string calle, string ciudad, int contrasenia);
    TipoRet registrarVenta(int rut, int codigoProducto, int cantidad);
    TipoRet consultarHistorialCompraCliente(int rut, vector<Venta *> &ventas);
    TipoRet emitirOrdenCompra(int codigoProducto, int cantidad, int rutProveedor);
    TipoRet cancelarOrdenCompra(int idOrdenCompra);
    TipoRet registrarRecepcionOrdenCompra(int idOodenCompra, vector<int> cantidadesRecibidas);
    
    Proveedor *buscarProveedor(int codigoProveedor) const;
    Producto *buscarProducto(int codigoProducto) const;
    OrdenCompra *buscarOrdenCompra(int idOrdenCompra) const;
    ClienteRegistrado *buscarCliente(int rut) const;
    
    vector<ClienteRegistrado *> listarClientes() const;
    
    bool crearOrdenCompra(OrdenCompra *orden);
    vector<OrdenCompra *> listarOrdenes() const;

    vector<Calificacion*> consultarCalificacionesDeProducto(int codigoProducto) const;
    int consultarStockActual(int codigoProducto) const;
    vector<Producto*> consultarProductoBajoMinimo() const;
    float montoTotalFacturadoACliente(int rut) const;
    int unidadesVendidasDeProducto(int codigoProducto) const;

};
