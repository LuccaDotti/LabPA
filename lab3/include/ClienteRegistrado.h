#pragma once
#include <string>
#include "Cliente.h"
#include "DtDireccion.h"
using namespace std;

class ClienteRegistrado : public Cliente
{
public:
    ClienteRegistrado(int RUT, const DtDireccion &direccion, const string &correo, const string &nombreCompleto);

    int getRUT() const;
    DtDireccion getDireccion() const;
    string getCorreo() const;
    string getNombreCompleto() const;

    // Atributo derivado
    float getTotalFacturado() const;
    void agregarFacturado(float monto);

private:
    int RUT;
    DtDireccion direccion;
    string correo;
    string nombreCompleto;
    float totalFacturado;
};
