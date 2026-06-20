#pragma once

class VentaController;
class AdminController;
class ClienteRegistrado;

class MenuCliente {

private:

    VentaController& ventaController;
    AdminController& adminController;
    ClienteRegistrado* clienteActual;

    void calificarProducto();
    void consultarDetalleProducto();

public:

    MenuCliente(VentaController& ventaController, AdminController& adminController, ClienteRegistrado* cliente);

    void mostrar();
};
