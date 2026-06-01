#include "Producto.h"
using namespace std;

Producto::Producto(int codigo, const string &nombre, const string &descripcion, float precioUnitario, int stockActual, int stockMinimo) : codigo(codigo), nombre(nombre), descripcion(descripcion), precioUnitario(precioUnitario), stockActual(stockActual), stockMinimo(stockMinimo), unidadesVendidas(0), categoria(NULL) {}

int Producto::getCodigo() const
{
    return codigo;
}
string Producto::getNombre() const
{
    return nombre;
}
string Producto::getDescripcion() const
{
    return descripcion;
}
float Producto::getPrecioUnitario() const
{
    return precioUnitario;
}
int Producto::getStockActual() const
{
    return stockActual;
}
int Producto::getStockMinimo() const
{
    return stockMinimo;
}

float Producto::getPuntajePromedio() const
{
    if (calificaciones.empty())
        return 0.0f;
    float suma = 0.0f;
    for (const auto *c : calificaciones)
        suma += c->getPuntaje();
    return suma / calificaciones.size();
}

int Producto::getUnidadesVendidas() const
{
    return unidadesVendidas;
}

bool Producto::isBajoStock() const
{
    return stockActual < stockMinimo;
}

void Producto::setPrecioUnitario(float precio)
{
    precioUnitario = precio;
}
void Producto::setStockActual(int stock)
{
    stockActual = stock;
}

void Producto::setCategoria(Categoria *cat)
{
    categoria = cat;
}
Categoria *Producto::getCategoria() const
{
    return categoria;
}

void Producto::agregarCalificacion(Calificacion *cal)
{
    calificaciones.push_back(cal);
}
const vector<Calificacion *> &Producto::getCalificaciones() const
{
    return calificaciones;
}

void Producto::agregarUnidadesVendidas(int cantidad)
{
    unidadesVendidas += cantidad;
}
