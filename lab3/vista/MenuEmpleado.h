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
    void altaCliente();
    void modificarCliente();

    void menuVentas();
    void registrarVenta();
    void consultarHistorialCompras();

    void menuGestionarOrdenesCompra();
    void emitirOrdenCompra();
    void cancelarOrdenCompra();
    void registrarRecepcionOrden();

    void menuReportes();
    void consultarStockActual();
    void consultarProductosBajoMinimo();
    void consultarTotalFacturado();
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
