#pragma once

#include <string>
#include <vector>

class ProveedorProducto;

class Proveedor {

private:

    int rut;
    std::string nombreEmpresa;
    int telefono;
    std::string nombreContacto;

    std::vector<ProveedorProducto*> productosProveidos;

public:

    Proveedor(
        int rut,
        const std::string& nombreEmpresa,
        int telefono,
        const std::string& nombreContacto
    );

    ~Proveedor();

    int getRut() const;
    void setRut(int rut);

    std::string getNombreEmpresa() const;
    void setNombreEmpresa(const std::string& nombreEmpresa);

    int getTelefono() const;
    void setTelefono(int telefono);

    std::string getNombreContacto() const;
    void setNombreContacto(const std::string& nombreContacto);

    std::vector<ProveedorProducto*> getProductosProveidos() const;

    void agregarProducto(
        ProveedorProducto* proveedorProducto
    );
};
