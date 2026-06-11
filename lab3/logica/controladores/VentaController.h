#pragma once

class Venta;
class AdminController;

using namespace std;

class VentaController {

private:

    AdminController& adminController;

public:

    VentaController(
        AdminController& adminController
    );

    ~VentaController();

    bool registrarVenta(
        Venta* venta
    );
};
