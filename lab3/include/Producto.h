#pragma once
#include <string>
#include <vector>
#include "Categoria.h"
#include "Calificacion.h"
using namespace std;

class Producto
{
public:
    Producto(int codigo, const string &nombre, const string &descripcion, float precioUnitario, int stockActual, int stockMinimo);

    // Getters
    int getCodigo() const;
    string getNombre() const;
    string getDescripcion() const;
    float getPrecioUnitario() const;
    int getStockActual() const;
    int getStockMinimo() const;

    // Atributos derivados
    float getPuntajePromedio() const;
    int getUnidadesVendidas() const;
    bool isBajoStock() const;

    // Setters
    void setPrecioUnitario(float precio);
    void setStockActual(int stock);

    // Relaciones
    void setCategoria(Categoria *categoria);
    Categoria *getCategoria() const;

    void agregarCalificacion(Calificacion *calificacion);
    const vector<Calificacion *> &getCalificaciones() const;

    void agregarUnidadesVendidas(int cantidad);

private:
    int codigo;
    string nombre;
    string descripcion;
    float precioUnitario;
    int stockActual;
    int stockMinimo;
    int unidadesVendidas;

    Categoria *categoria;
    vector<Calificacion *> calificaciones;
};
