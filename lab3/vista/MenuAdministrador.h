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

    void agregarCategoria();
    void modificarCategoria();

    void agregarProducto();
    void modificarProducto();
    void eliminarProducto();

    void altaProveedor();
    void modificarProveedor();
    void registrarProveedorProducto();

    void altaUsuario();
    void listarUsuarios();
    void eliminarUsuario();

public:

    MenuAdministrador(
        AdminController& adminController
    );

    void mostrar();
};
