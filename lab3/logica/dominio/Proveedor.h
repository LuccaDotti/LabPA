#pragma once

#include <string>
#include <vector>

using namespace std;

class ProveedorProducto;

class Proveedor
{
private:
    int rut;
    string nombreEmpresa;
    int telefono;
    string nombreContacto;

    vector<ProveedorProducto*> productosProveidos;

public:
    Proveedor(
        int rut,
        const string& nombreEmpresa,
        int telefono,
        const string& nombreContacto
    );

    ~Proveedor();

    int getRut() const;
    void setRut(int rut);

    string getNombreEmpresa() const;
    void setNombreEmpresa(
        const string& nombreEmpresa
    );

    int getTelefono() const;
    void setTelefono(int telefono);

    string getNombreContacto() const;
    void setNombreContacto(
        const string& nombreContacto
    );

    vector<ProveedorProducto*> getProductosProveidos() const;

    void agregarProducto(
        ProveedorProducto* proveedorProducto
    );
};
