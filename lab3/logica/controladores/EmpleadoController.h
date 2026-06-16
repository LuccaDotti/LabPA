#pragma once

#include <vector>

#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/OrdenCompra.h"

class AdminController;

using namespace std;

class EmpleadoController {

private:

    vector<ClienteRegistrado*> clientes;
    vector<OrdenCompra*> ordenesCompra;

    AdminController& adminController;

public:

    EmpleadoController(
        AdminController& adminController
    );

    ~EmpleadoController();

    // ====================================
    // CLIENTES REGISTRADOS
    // ====================================

    bool agregarCliente(
        ClienteRegistrado* cliente
    );

    ClienteRegistrado* buscarCliente(
        int rut
    ) const;

    vector<ClienteRegistrado*> listarClientes() const;

    // ====================================
    // ORDENES DE COMPRA
    // ====================================

    bool crearOrdenCompra(
        OrdenCompra* orden
    );

    vector<OrdenCompra*> listarOrdenes() const;
};
