#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/Venta.h"

using namespace std;

ClienteRegistrado::ClienteRegistrado(
    int rut,
    const Direccion& direccion,
    const string& correo,
    const string& nombreCompleto,
    float totalFacturado
)
{
    : rut(rut),
      direccion(direccion),
      correo(correo),
      nombreCompleto(nombreCompleto),
      totalFacturado(totalFacturado)
}

ClienteRegistrado::~ClienteRegistrado()
{
}

int ClienteRegistrado::getRut() const
{
    return rut;
}

void ClienteRegistrado::setRut(
    int rut
)
{
    this->rut = rut;
}

Direccion ClienteRegistrado::getDireccion() const
{
    return direccion;
}

void ClienteRegistrado::setDireccion(
    const Direccion& direccion
)
{
    this->direccion = direccion;
}

string ClienteRegistrado::getCorreo() const
{
    return correo;
}

void ClienteRegistrado::setCorreo(
    const string& correo
)
{
    this->correo = correo;
}

string ClienteRegistrado::getNombreCompleto() const
{
    return nombreCompleto;
}

void ClienteRegistrado::setNombreCompleto(
    const string& nombreCompleto
)
{
    this->nombreCompleto = nombreCompleto;
}

float ClienteRegistrado::getTotalFacturado() const
{
    return totalFacturado;
}

void ClienteRegistrado::setTotalFacturado(
    float totalFacturado
)
{
    this->totalFacturado = totalFacturado;
}

vector<Venta*> ClienteRegistrado::getVentas() const
{
    return ventas;
}

void ClienteRegistrado::agregarVenta(
    Venta* venta
)
{
    ventas.push_back(
        venta
    );
}

vector<Calificacion*> ClienteRegistrado::getCalificaciones() const
{
    return calificaciones;
}

void ClienteRegistrado::agregarCalificacion(
    Calificacion* calificacion
)
{
    calificaciones.push_back(
        calificacion
    );
}

void ClienteRegistrado::agregarFacturacion(
    float monto
)
{
    totalFacturado += monto;
}
