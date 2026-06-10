#pragma once

#include <vector>
#include <string>

#include "logica/dominio/Cliente.h"
#include "logica/dominio/OrdenCompra.h"

class AdminController;

using namespace std;

class EmpleadoController {

private:

    vector<Cliente*> clientes;
    vector<OrdenCompra*> ordenesCompra;

    AdminController& adminController;

public:

    EmpleadoController(AdminController& adminController);

    ~EmpleadoController();

    // Clientes

    bool agregarCliente(Cliente* cliente);

    Cliente* buscarCliente(int rut) const;

    vector<Cliente*> listarClientes() const;

    // Ordenes

    bool crearOrdenCompra(
        OrdenCompra* orden
    );

    vector<OrdenCompra*> listarOrdenes() const;
};
