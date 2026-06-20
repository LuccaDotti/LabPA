#pragma once

#include <vector>
#include <string>

#include "logica/controladores/tipoRetorno.h"
#include "logica/controladores/Rol.h"

#include "logica/dominio/Producto.h"
#include "logica/dominio/Categoria.h"
#include "logica/dominio/Proveedor.h"
#include "logica/dominio/ProveedorProducto.h"
#include "logica/dominio/Fecha.h"
#include "logica/dominio/Usuario.h"

using namespace std;

class AdminController
{
private:

    static AdminController* instancia;

    vector<Producto*> productos;
    vector<Categoria*> categorias;
    vector<Proveedor*> proveedores;
    vector<ProveedorProducto*> proveedorProductos;
    vector<Usuario*> usuarios;

    AdminController();

public:

    static AdminController* getInstancia();

    ~AdminController();

    AdminController(const AdminController&) = delete;
    AdminController& operator=(const AdminController&) = delete;

    TipoRet agregarProducto(int codigo, const string& nombre, const string& descripcion, float precioUnitario, int stockActual, int stockMinimo, Categoria* categoria);

    TipoRet modificarProducto(int codigo, const string& nuevoNombre, const string& nuevaDescripcion, float nuevoPrecio, Categoria* nuevaCategoria, int nuevoStockMinimo);

    Producto* buscarProducto(int codigo) const;

    vector<Producto*> listarProductos() const;

    TipoRet eliminarProducto(int codigo);

    TipoRet agregarCategoria(const string& nombre, const string& descripcion);

    TipoRet modificarCategoria(const string& nombreActual, const string& nuevoNombre, const string& nuevaDescripcion);

    Categoria* buscarCategoria(const string& nombre) const;

    vector<Categoria*> listarCategorias() const;

    TipoRet agregarProveedor(int rut, const string& nombreEmpresa, int telefono, const string& nombreContacto);

    TipoRet modificarProveedor(int rut, const string& nuevoNombreEmpresa, int nuevoTelefono, const string& nuevoNombreContacto);

    Proveedor* buscarProveedor(int rut) const;

    vector<Proveedor*> listarProveedores() const;

    TipoRet asociarProveedorProducto(int rutProveedor, int codigoProducto, float precioCompra, Fecha* fechaEntrega);

    vector<ProveedorProducto*> listarProveedorProductos() const;

    TipoRet agregarUsuario(const string& nombre, const string& email, const string& password, Rol rol);

    Usuario* buscarUsuarioPorEmail(const string& email) const;

    vector<Usuario*> listarUsuarios() const;

    TipoRet eliminarUsuario(const string& email);
};
