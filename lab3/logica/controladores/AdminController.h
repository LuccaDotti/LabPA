#pragma once

#include <vector>
#include <string>

#include "logica/dominio/Producto.h"
#include "logica/dominio/Categoria.h"
#include "logica/dominio/Proveedor.h"
#include "logica/dominio/ProveedorProducto.h"
#include "logica/dominio/Fecha.h"

using namespace std;

class AdminController {

private:

    static AdminController* instancia;

    vector<Producto*> productos;
    vector<Categoria*> categorias;
    vector<Proveedor*> proveedores;
    vector<ProveedorProducto*> proveedorProductos;

    AdminController();

public:

    static AdminController* getInstancia();

    ~AdminController();

    AdminController(const AdminController&) = delete;
    AdminController& operator=(const AdminController&) = delete;

    bool agregarProducto(
        int codigo,
        const string& nombre,
        const string& descripcion,
        float precioUnitario,
        int stockActual,
        int stockMinimo,
        Categoria* categoria
    );

    bool modificarProducto(
        int codigo,
        const string& nuevoNombre,
        const string& nuevaDescripcion,
        float nuevoPrecio,
        Categoria* nuevaCategoria,
        int nuevoStockMinimo
    );

    Producto* buscarProducto(
        int codigo
    ) const;

    vector<Producto*> listarProductos() const;

    bool eliminarProducto(
        int codigo
    );

    bool agregarCategoria(
        const string& nombre,
        const string& descripcion
    );

    bool modificarCategoria(
        const string& nombreActual,
        const string& nuevoNombre,
        const string& nuevaDescripcion
    );

    Categoria* buscarCategoria(
        const string& nombre
    ) const;

    vector<Categoria*> listarCategorias() const;

    bool agregarProveedor(
        int rut,
        const string& nombreEmpresa,
        int telefono,
        const string& nombreContacto
    );

    bool modificarProveedor(
        int rut,
        const string& nuevoNombreEmpresa,
        int nuevoTelefono,
        const string& nuevoNombreContacto
    );

    Proveedor* buscarProveedor(
        int rut
    ) const;

    vector<Proveedor*> listarProveedores() const;

    bool asociarProveedorProducto(
        int rutProveedor,
        int codigoProducto,
        float precioCompra,
        Fecha* fechaEntrega
    );

    vector<ProveedorProducto*> listarProveedorProductos() const;
};
