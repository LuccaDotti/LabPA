#pragma once
#include <string>
using namespace std;

class Categoria {
public:
    Categoria(const string& nombre, const string& descripcion);

    string getNombre() const;
    string getDescripcion() const;

private:
    string nombre;
    string descripcion;
};
