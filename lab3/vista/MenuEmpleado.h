#pragma once

class EmpleadoController;
class AdminController;

class MenuEmpleado {

private:

    EmpleadoController& empleadoController;
    AdminController& adminController;

public:

    MenuEmpleado(EmpleadoController& empleadoController, AdminController& adminController);

    void mostrar();
};
