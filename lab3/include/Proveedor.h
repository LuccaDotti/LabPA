#pragma once
#include <string>
using namespace std;

class Proveedor
{
public:
    Proveedor(int RUT, const string &nombreEmpresa, int telefono, const string &nombreContacto);

    int getRUT() const;
    string getNombreEmpresa() const;
    int getTelefono() const;
    string getNombreContacto() const;

private:
    int RUT;
    string nombreEmpresa;
    int telefono;
    string nombreContacto;
};
