#include "logica/dominio/Direccion.h"

Direccion::Direccion(
    int nroPuerta,
    std::string calle,
    std::string ciudad
) {
    this->nroPuerta = nroPuerta;
    this->calle = calle;
    this->ciudad = ciudad;
}

int Direccion::getNroPuerta() {
    return nroPuerta;
}

std::string Direccion::getCalle() {
    return calle;
}

std::string Direccion::getCiudad() {
    return ciudad;
}

void Direccion::setNroPuerta(int nroPuerta) {
    this->nroPuerta = nroPuerta;
}

void Direccion::setCalle(std::string calle) {
    this->calle = calle;
}

void Direccion::setCiudad(std::string ciudad) {
    this->ciudad = ciudad;
}
