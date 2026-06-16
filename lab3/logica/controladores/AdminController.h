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

    vector<Producto*> productos;
    vector<Categoria*> categorias;
    vector<Proveedor*> proveedores;
    vector<ProveedorProducto*> proveedorProductos;

public:

    AdminController();
    ~AdminController();

    // ===== PRODUCTOS =====

    bool agregarProducto(int codigo, const string& nombre, const string& descripcion, float precioUnitario, int stockActual, int stockMinimo, Categoria* categoria);

    Producto* buscarProducto(int codigo) const;

    vector<Producto*> listarProductos() const;

    bool eliminarProducto(int codigo);

    // ===== CATEGORIAS =====

    bool agregarCategoria(const string& nombre, const string& descripcion);

    Categoria* buscarCategoria(const string& nombre) const;

    vector<Categoria*> listarCategorias() const;

    // ===== PROVEEDORES =====

    bool agregarProveedor(int rut, const string& nombreEmpresa, int telefono, const string& nombreContacto);

    Proveedor* buscarProveedor(int rut) const;

    vector<Proveedor*> listarProveedores() const;

    // ===== PROVEEDOR-PRODUCTO =====

    bool asociarProveedorProducto(int rutProveedor, int codigoProducto, float precioCompra, Fecha* fechaEntrega);

    vector<ProveedorProducto*> listarProveedorProductos() const;
};
