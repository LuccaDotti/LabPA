#pragma once

class EmpleadoController;
class AdminController;
class VentaController;

class MenuEmpleado {

private:

    EmpleadoController& empleadoController;
    AdminController& adminController;
    VentaController& ventaController;

    void menuGestionarClientes();
    void consultarTotalFacturado();
    void menuConsultarProductos();
    void consultarStockActual();
    void consultarProductosBajoMinimo();
    void consultarUnidadesVendidas();
    void consultarCalificacionesProducto();
    void menuGestionarOrdenesCompra();
    void registrarVenta();
    void consultarHistorialCompras();

public:

    MenuEmpleado(
        EmpleadoController& empleadoController,
        AdminController& adminController,
        VentaController& ventaController
    );

    void mostrar();
};
