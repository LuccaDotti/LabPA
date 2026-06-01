#pragma once
#include <string>
#include "DtFecha.h"
using namespace std;

class Calificacion {
public:
    Calificacion(int puntaje, const string& comentario, const DtFecha& fecha);

    int getPuntaje() const;
    string getComentario() const;
    DtFecha getFecha() const;

private:
    int puntaje;
    string comentario;
    DtFecha fecha;
};
