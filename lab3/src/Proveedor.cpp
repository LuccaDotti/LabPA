#include "Proveedor.h"
using namespace std;

Proveedor::Proveedor(int RUT, const string &nombreEmpresa, int telefono, const string &nombreContacto) : RUT(RUT), nombreEmpresa(nombreEmpresa), telefono(telefono), nombreContacto(nombreContacto) {}

int Proveedor::getRUT() const
{
  return RUT;
}
string Proveedor::getNombreEmpresa() const
{
  return nombreEmpresa;
}
int Proveedor::getTelefono() const
{
  return telefono;
}
string Proveedor::getNombreContacto() const
{
  return nombreContacto;
}
