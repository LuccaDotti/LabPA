#pragma once

class Fecha
{
private:
    int dia, mes, anio, hora, minutos, segundos;

public:
    Fecha();
    Fecha(int dia, int mes, int anio, int hora, int minutos, int segundos);

    int getDia();
    int getMes();
    int getAnio();
    int getHora();
    int getMinutos();
    int getSegundos();

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    void setHora(int hora);
    void setMinutos(int minutos);
    void setSegundos(int segundos);
};
