#pragma once

#include <vector>

class Venta;
class AdminController;

using namespace std;

class VentaController {

private:

    vector<Venta*> ventas;
    AdminController& adminController;

public:

    VentaController(
        AdminController& adminController
    );

    ~VentaController();

    bool registrarVenta(Venta* venta);

    vector<Venta*> listarVentas() const;
};
