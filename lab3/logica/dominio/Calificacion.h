#pragma once

#include <string>

using namespace std;

class Fecha;
class Producto;

class Calificacion
{
private:
    int puntaje;
    string comentarioOpcional;
    Fecha *fecha;
    Producto *producto;

public:
    Calificacion(
        int puntaje,
        const string& comentarioOpcional,
        Fecha* fecha,
        Producto* producto
    );

    ~Calificacion();

    int getPuntaje() const;
    void setPuntaje(int puntaje);

    string getComentarioOpcional() const;
    void setComentarioOpcional(const string &comentarioOpcional);

    Fecha *getFecha() const;
    void setFecha(Fecha *fecha);

    Producto *getProducto() const;
    void setProducto(Producto *producto);
};
