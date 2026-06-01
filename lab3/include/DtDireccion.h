#pragma once
#include <string>
using namespace std;

class DtDireccion {
public:
    DtDireccion(const string& calle, int numero, const string& ciudad);

    string getCalle() const;
    int getNumero() const;
    string getCiudad() const;

private:
    string calle;
    int numero;
    string ciudad;
};
