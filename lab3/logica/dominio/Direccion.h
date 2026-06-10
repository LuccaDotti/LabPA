#pragma once

#include <string>

class Direccion {

private:

    int nroPuerta;
    std::string calle;
    std::string ciudad;

public:

    Direccion(
        int nroPuerta,
        std::string calle,
        std::string ciudad
    );

    int getNroPuerta();
    std::string getCalle();
    std::string getCiudad();

    void setNroPuerta(int nroPuerta);
    void setCalle(std::string calle);
    void setCiudad(std::string ciudad);
};
