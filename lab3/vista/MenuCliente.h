#pragma once

class VentaController;
class AdminController;

class MenuCliente {

private:

    VentaController& ventaController;
    AdminController& adminController;

    void consultarDetalleProducto();

public:

    MenuCliente(
        VentaController& ventaController,
        AdminController& adminController
    );

    void mostrar();
};
