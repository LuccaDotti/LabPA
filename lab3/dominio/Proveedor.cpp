#include "logica/dominio/Proveedor.h"

using namespace std;

Proveedor::Proveedor(
    int rut,
    const string& nombreEmpresa,
    int telefono,
    const string& nombreContacto
)
{
    this->rut = rut;
    this->nombreEmpresa = nombreEmpresa;
    this->telefono = telefono;
    this->nombreContacto = nombreContacto;
}

Proveedor::~Proveedor()
{
}

int Proveedor::getRut() const
{
    return rut;
}

void Proveedor::setRut(int rut)
{
    this->rut = rut;
}

string Proveedor::getNombreEmpresa() const
{
    return nombreEmpresa;
}

void Proveedor::setNombreEmpresa(
    const string& nombreEmpresa
)
{
    this->nombreEmpresa = nombreEmpresa;
}

int Proveedor::getTelefono() const
{
    return telefono;
}

void Proveedor::setTelefono(int telefono)
{
    this->telefono = telefono;
}

string Proveedor::getNombreContacto() const
{
    return nombreContacto;
}

void Proveedor::setNombreContacto(
    const string& nombreContacto
)
{
    this->nombreContacto = nombreContacto;
}

vector<ProveedorProducto*> Proveedor::getProductosProveidos() const
{
    return productosProveidos;
}

void Proveedor::agregarProducto(
    ProveedorProducto* proveedorProducto
)
{
    productosProveidos.push_back(
        proveedorProducto
    );
}
