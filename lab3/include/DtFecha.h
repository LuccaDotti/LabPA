#pragma once
using namespace std;

class DtFecha {
public:
    DtFecha(int dia, int mes, int anio, int hora = 0, int minutos = 0, int segundos = 0);

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinutos() const;
    int getSegundos() const;

private:
    int dia;
    int mes;
    int anio;
    int hora;
    int minutos;
    int segundos;
};
