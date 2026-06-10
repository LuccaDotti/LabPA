#include "logica/dominio/Calificacion.h"

using namespace std;

Calificacion::Calificacion(
    int puntaje,
    const string& comentarioOpcional,
    Fecha* fecha,
    Producto* producto
)
{
    this->puntaje = puntaje;
    this->comentarioOpcional = comentarioOpcional;
    this->fecha = fecha;
    this->producto = producto;
}

Calificacion::~Calificacion()
{
}

int Calificacion::getPuntaje() const
{
    return puntaje;
}

void Calificacion::setPuntaje(int puntaje)
{
    this->puntaje = puntaje;
}

string Calificacion::getComentarioOpcional() const
{
    return comentarioOpcional;
}

void Calificacion::setComentarioOpcional(
    const string& comentarioOpcional
)
{
    this->comentarioOpcional = comentarioOpcional;
}

Fecha* Calificacion::getFecha() const
{
    return fecha;
}

void Calificacion::setFecha(Fecha* fecha)
{
    this->fecha = fecha;
}

Producto* Calificacion::getProducto() const
{
    return producto;
}

void Calificacion::setProducto(Producto* producto)
{
    this->producto = producto;
}
