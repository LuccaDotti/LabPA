#pragma once

#include <vector>
#include <string>

#include "logica/dominio/Producto.h"
#include "logica/dominio/Categoria.h"
#include "logica/dominio/Proveedor.h"

using namespace std;

class AdminController {

private:

    vector<Producto*> productos;
    vector<Categoria*> categorias;
    vector<Proveedor*> proveedores;

public:

    AdminController();
    ~AdminController();

    // Productos

    bool agregarProducto(
        int codigo,
        string nombre,
        string descripcion,
        float precioUnitario,
        int stockActual,
        int stockMinimo,
        Categoria* categoria,
        Proveedor* proveedor
    );

    Producto* buscarProducto(int codigo) const;

    vector<Producto*> listarProductos() const;

    bool eliminarProducto(int codigo);

    // Categorias

    bool agregarCategoria(
        string nombre,
        string descripcion
    );

    Categoria* buscarCategoria(
        string nombre
    ) const;

    vector<Categoria*> listarCategorias() const;

    // Proveedores

    bool agregarProveedor(
        int rut,
        string nombreEmpresa,
        int telefono,
        string nombreContacto
    );

    Proveedor* buscarProveedor(
        int rut
    ) const;

    vector<Proveedor*> listarProveedores() const;
};
