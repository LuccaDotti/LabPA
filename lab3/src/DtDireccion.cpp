#include "DtDireccion.h"
using namespace std;

DtDireccion::DtDireccion(const string &calle, int numero, const string &ciudad) : calle(calle), numero(numero), ciudad(ciudad) {}

string DtDireccion::getCalle() const
{
    return calle;
}
int DtDireccion::getNumero() const
{
    return numero;
}
string DtDireccion::getCiudad() const
{
    return ciudad;
}
