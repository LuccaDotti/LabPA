#include "logica/dominio/Direccion.h"
using namespace std;
#include <string>

Direccion::Direccion()
    : nroPuerta(0), calle(""), ciudad("")
{
}

Direccion::Direccion(int nroPuerta, string calle, string ciudad) 
    : nroPuerta(nroPuerta), calle(calle), ciudad(ciudad)
{
    this->nroPuerta = nroPuerta;
    this->calle = calle;
    this->ciudad = ciudad;
}

int Direccion::getNroPuerta() {
    return nroPuerta;
}

string Direccion::getCalle() {
    return calle;
}

string Direccion::getCiudad() {
    return ciudad;
}

void Direccion::setNroPuerta(int nroPuerta) {
    this->nroPuerta = nroPuerta;
}

void Direccion::setCalle(std::string calle) {
    this->calle = calle;
}

void Direccion::setCiudad(string ciudad) {
    this->ciudad = ciudad;
}
