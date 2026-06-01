#include "Calificacion.h"
using namespace std;

Calificacion::Calificacion(int puntaje, const string &comentario, const DtFecha &fecha) : puntaje(puntaje), comentario(comentario), fecha(fecha) {}

int Calificacion::getPuntaje() const
{
    return puntaje;
}
string Calificacion::getComentario() const
{
    return comentario;
}
DtFecha Calificacion::getFecha() const
{
    return fecha;
}
