#pragma once

#include <string>
#include <vector>

#include "logica/dominio/Calificacion.h"
#include "logica/dominio/Direccion.h"

using namespace std;

class Venta;

class ClienteRegistrado
{
private:

    int rut;
    Direccion direccion;
    string correo;
    string nombreCompleto;

    float totalFacturado;

    vector<Venta*> ventas;

    vector<Calificacion*> calificaciones;

public:

    ClienteRegistrado(
        int rut,
        const Direccion& direccion,
        const string& correo,
        const string& nombreCompleto,
        float totalFacturado
    );

    ~ClienteRegistrado();

    int getRut() const;
    void setRut(int rut);

    Direccion getDireccion() const;
    void setDireccion(
        const Direccion& direccion
    );

    string getCorreo() const;
    void setCorreo(
        const string& correo
    );

    string getNombreCompleto() const;
    void setNombreCompleto(
        const string& nombreCompleto
    );

    float getTotalFacturado() const;
    void setTotalFacturado(
        float totalFacturado
    );

    vector<Venta*> getVentas() const;

    void agregarVenta(
        Venta* venta
    );

    vector<Calificacion*> getCalificaciones() const;

    void agregarCalificacion(
        Calificacion* calificacion
    );

    void agregarFacturacion(
        float monto
    );
};
