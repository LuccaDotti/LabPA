#pragma once

class AdminController;

class MenuAdministrador {

private:

    AdminController& adminController;

public:

    MenuAdministrador(
        AdminController& adminController
    );

    void mostrar();
};
