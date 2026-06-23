#pragma once

class AdminController;

class MenuAdministrador
{
private:

    AdminController& adminController;

    void menuCategorias();
    void menuProductos();
    void menuProveedores();
    void menuCalificaciones();
    void menuStock();
    void menuReportes();
    void menuInfoProducto();
    void menuUsuarios();

    void listarCategorias();
    void agregarCategoria();
    void modificarCategoria();

    void listarProductos();
    void agregarProducto();
    void modificarProducto();
    void eliminarProducto();

    void listarProveedores();
    void altaProveedor();
    void modificarProveedor();
    void registrarProveedorProducto();

    void listarStock();
    void consultarStockProducto();

    void altaUsuario();
    void listarUsuarios();
    void eliminarUsuario();

public:

    MenuAdministrador(
        AdminController& adminController
    );

    void mostrar();
};
