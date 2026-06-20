#pragma once

class VentaController;
class AdminController;

class MenuCliente {

private:

    VentaController& ventaController;
    AdminController& adminController;

    void consultarDetalleProducto();
    void realizarVenta();
    void calificarProducto();

public:

    MenuCliente(VentaController& ventaController, AdminController& adminController);

    void mostrar();
};
