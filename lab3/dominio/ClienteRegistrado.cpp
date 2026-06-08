#include "ClienteRegistrado.h"
using namespace std;

ClienteRegistrado::ClienteRegistrado(int id, int rut, const string &direccion, const string &correo, const string &nombreCompleto, float totalFacturado) : Cliente(id), rut(rut), direccion(direccion), correo(correo), nombreCompleto(nombreCompleto), totalFacturado(totalFacturado) {}

ClienteRegistrado::~ClienteRegistrado() = default;

int ClienteRegistrado::getRut() const
{
    return rut;
}
void ClienteRegistrado::setRut(int rut)
{
    this->rut = rut;
}

string ClienteRegistrado::getDireccion() const
{
    return direccion;
}
void ClienteRegistrado::setDireccion(const string &direccion)
{
    this->direccion = direccion;
}

string ClienteRegistrado::getCorreo() const
{
    return correo;
}
void ClienteRegistrado::setCorreo(const string &correo)
{
    this->correo = correo;
}

string ClienteRegistrado::getNombreCompleto() const
{
    return nombreCompleto;
}
void ClienteRegistrado::setNombreCompleto(const string &nombreCompleto)
{
    this->nombreCompleto = nombreCompleto;
}

float ClienteRegistrado::getTotalFacturado() const
{
    return totalFacturado;
}

void ClienteRegistrado::setTotalFacturado(float totalFacturado)
{
    this->totalFacturado = totalFacturado;
}

string ClienteRegistrado::clienteTipo() const
{
    return "Registrado";
}

void ClienteRegistrado::agregarFacturacion(float monto)
{
    // Stub: acumular facturación
    totalFacturado += monto;
}