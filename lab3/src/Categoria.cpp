#include "Categoria.h"
using namespace std;

Categoria::Categoria(const string &nombre, const string &descripcion) : nombre(nombre), descripcion(descripcion) {}

string Categoria::getNombre() const
{
    return nombre;
}
string Categoria::getDescripcion() const
{
    return descripcion;
}
