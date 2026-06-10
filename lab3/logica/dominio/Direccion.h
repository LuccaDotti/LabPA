#pragma once
using namespace std;
#include <string>

class Direccion {

private:

    int nroPuerta;
    string calle;
    string ciudad;

public:

    Direccion(
        int nroPuerta,
        string calle,
        string ciudad
    );

    int getNroPuerta();
    string getCalle();
    string getCiudad();

    void setNroPuerta(int nroPuerta);
    void setCalle(string calle);
    void setCiudad(string ciudad);
};
