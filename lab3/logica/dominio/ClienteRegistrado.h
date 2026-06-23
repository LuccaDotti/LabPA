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
    string contrasenia;

    float totalFacturado;

    vector<Venta *> ventas;

    vector<Calificacion *> calificaciones;

public:
    ClienteRegistrado(int rut, const Direccion &direccion, const string &correo, const string &nombreCompleto, const string &contrasenia, float totalFacturado);

    ~ClienteRegistrado();

    TipoRet calificarProducto(int codigoProducto, int calificacion, string comentario);

    string getContrasenia() const;
    void setContrasenia(const string &contrasenia);

    int getRut() const;
    void setRut(int rut);

    Direccion getDireccion() const;
    void setDireccion(const Direccion &direccion);

    string getCorreo() const;
    void setCorreo(const string &correo);

    string getNombreCompleto() const;
    void setNombreCompleto(const string &nombreCompleto);

    float getTotalFacturado() const;
    void setTotalFacturado(float totalFacturado);

    vector<Venta *> getVentas() const;

    void agregarVenta(Venta *venta);

    vector<Calificacion *> getCalificaciones() const;

    void agregarCalificacion(Calificacion *calificacion);

    void agregarFacturacion(float monto);

    Producto* consultarInformacionDetalladaProducto(int codigoProducto) const;
};
