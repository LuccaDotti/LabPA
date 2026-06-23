#pragma once

#include <vector>

class EmpleadoController;
class AdminController;
class VentaController;

class MenuEmpleado {

private:

    EmpleadoController& empleadoController;
    AdminController& adminController;
    VentaController& ventaController;

    void menuGestionarClientes();
    void listarClientes();
    void altaCliente();
    void modificarCliente();
    void consultarTotalFacturado();

    void menuVentas();
    void registrarVenta();
    void consultarHistorialCompras();

    void menuGestionarOrdenesCompra();
    void listarOrdenesCompra();
    void emitirOrdenCompra();
    void cancelarOrdenCompra();
    void registrarRecepcionOrden();

    void menuReportes();
    void consultarStockActual();
    void consultarProductosBajoMinimo();
    void consultarUnidadesVendidas();

    void consultarCalificacionesProducto();
    void consultarDetalleProducto();

public:

    MenuEmpleado(
        EmpleadoController& empleadoController,
        AdminController& adminController,
        VentaController& ventaController
    );

    void mostrar();
};
