#include "ClienteRegistrado.h"
using namespace std;

ClienteRegistrado::ClienteRegistrado(int RUT, const DtDireccion &direccion, const string &correo, const string &nombreCompleto) : RUT(RUT), direccion(direccion), correo(correo), nombreCompleto(nombreCompleto), totalFacturado(0.0f) {}

int ClienteRegistrado::getRUT() const
{
  return RUT;
}
DtDireccion ClienteRegistrado::getDireccion() const
{
  return direccion;
}
string ClienteRegistrado::getCorreo() const
{
  return correo;
}
string ClienteRegistrado::getNombreCompleto() const
{
  return nombreCompleto;
}

float ClienteRegistrado::getTotalFacturado() const
{
  return totalFacturado;
}
void ClienteRegistrado::agregarFacturado(float monto)
{
  totalFacturado += monto;
}
