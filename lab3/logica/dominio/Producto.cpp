#include "Producto.h"
#include <string>
using namespace std;

Producto::Producto(int codigo, const string &nombre, const string &descripcion, float precioUnitario, int stockActual, int stockMinimo, float puntajePromedio, int unidadesVendidas, bool bajoStock, Categoria *categoria) : codigo(codigo), nombre(nombre), descripcion(descripcion), precioUnitario(precioUnitario), stockActual(stockActual), stockMinimo(stockMinimo), puntajePromedio(puntajePromedio), unidadesVendidas(unidadesVendidas), bajoStock(bajoStock), categoria(categoria) {}

Producto::~Producto() = default;

int Producto::getCodigo() const
{
    return codigo;
}
void Producto::setCodigo(int codigo)
{
    this->codigo = codigo;
}

string Producto::getNombre() const
{
    return nombre;
}
void Producto::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

string Producto::getDescripcion() const
{
    return descripcion;
}
void Producto::setDescripcion(const string &descripcion)
{
    this->descripcion = descripcion;
}

float Producto::getPrecioUnitario() const
{
    return precioUnitario;
}
void Producto::setPrecioUnitario(float precioUnitario)
{
    this->precioUnitario = precioUnitario;
}

int Producto::getStockActual() const
{
    return stockActual;
}
void Producto::setStockActual(int stockActual)
{
    this->stockActual = stockActual;
}

int Producto::getStockMinimo() const
{
    return stockMinimo;
}
void Producto::setStockMinimo(int stockMinimo)
{
    this->stockMinimo = stockMinimo;
}

float Producto::getPuntajePromedio() const
{
    return puntajePromedio;
}
void Producto::setPuntajePromedio(float puntajePromedio)
{
    this->puntajePromedio = puntajePromedio;
}

int Producto::getUnidadesVendidas() const
{
    return unidadesVendidas;
}
void Producto::setUnidadesVendidas(int unidadesVendidas)
{
    this->unidadesVendidas = unidadesVendidas;
}

bool Producto::isBajoStock() const
{
    return bajoStock;
}
void Producto::setBajoStock(bool bajoStock)
{
    this->bajoStock = bajoStock;
}

Categoria *Producto::getCategoria() const
{
    return categoria;
}
void Producto::setCategoria(Categoria *categoria)
{
    this->categoria = categoria;
}

void Producto::vender(int unidades)
{
    // Stub: actualizar unidades vendidas y stock
    unidadesVendidas += unidades;
    stockActual -= unidades;
    if (stockActual < 0)
        stockActual = 0;
}

bool Producto::estaBajoStock() const
{
    return stockActual <= stockMinimo;
}
