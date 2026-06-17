#pragma once

class AdminController;
class EmpleadoController;
class VentaController;

class MenuPrincipal
{
private:

    AdminController* adminController;
    EmpleadoController* empleadoController;
    VentaController* ventaController;

public:

    MenuPrincipal();

    void mostrar();
};
