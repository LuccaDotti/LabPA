#include "DtFecha.h"
using namespace std;

DtFecha::DtFecha(int dia, int mes, int anio, int hora, int minutos, int segundos) : dia(dia), mes(mes), anio(anio), hora(hora), minutos(minutos), segundos(segundos) {}

int DtFecha::getDia() const
{
    return dia;
}
int DtFecha::getMes() const
{
    return mes;
}
int DtFecha::getAnio() const
{
    return anio;
}
int DtFecha::getHora() const
{
    return hora;
}
int DtFecha::getMinutos() const
{
    return minutos;
}
int DtFecha::getSegundos() const
{
    return segundos;
}
