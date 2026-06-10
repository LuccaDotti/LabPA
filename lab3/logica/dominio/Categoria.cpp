#include "Categoria.h"
using namespace std;
#include <string>

Categoria::Categoria(const string &nombre, const string &descripcion) : nombre(nombre), descripcion(descripcion) {}

Categoria::~Categoria() = default;

string Categoria::getNombre() const
{
    return nombre;
}
void Categoria::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

string Categoria::getDescripcion() const
{
    return descripcion;
}
void Categoria::setDescripcion(const string &descripcion)
{
    this->descripcion = descripcion;
}
