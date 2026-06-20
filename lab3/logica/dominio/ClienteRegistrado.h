#pragma once

#include <string>
#include <vector>

#include "logica/dominio/Calificacion.h"
#include "logica/dominio/Direccion.h"
#include "logica/controladores/tipoRetorno.h"

using namespace std;

class Venta;

class ClienteRegistrado
{
private:
    int rut;
    Direccion direccion;
    string correo;
    string nombreCompleto;
    int contrasenia;

    float totalFacturado;

    vector<Venta *> ventas;

    vector<Calificacion *> calificaciones;

public:
    ClienteRegistrado(int rut, const Direccion &direccion, const string &correo, const string &nombreCompleto, int contrasenia, float totalFacturado);

    ~ClienteRegistrado();

    TipoRet calificarProducto(int codigoProducto, int calificacion, string comentario);

    int getContrasenia() const;
    void setContrasenia(int contrasenia);

    int getRut() const;
    void setRut(int rut);

    Direccion getDireccion() const;
    void setDireccion(
        const Direccion &direccion);

    string getCorreo() const;
    void setCorreo(
        const string &correo);

    string getNombreCompleto() const;
    void setNombreCompleto(
        const string &nombreCompleto);

    float getTotalFacturado() const;
    void setTotalFacturado(
        float totalFacturado);

    vector<Venta *> getVentas() const;

    void agregarVenta(
        Venta *venta);

    vector<Calificacion *> getCalificaciones() const;

    void agregarCalificacion(
        Calificacion *calificacion);

    void agregarFacturacion(float monto);
};
