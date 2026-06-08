#pragma once
using namespace std;
#include <string>

class Categoria
{
private:
    string nombre;
    string descripcion;

public:
    Categoria(const string &nombre, const string &descripcion);
    ~Categoria();

    string getNombre() const;
    void setNombre(const string &nombre);

    string getDescripcion() const;
    void setDescripcion(const string &descripcion);
};
