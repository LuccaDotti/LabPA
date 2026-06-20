#include "logica/dominio/Fecha.h"
#include <ctime>

Fecha::Fecha()
{
    time_t now = time(0);
    tm *tiempoLocal = localtime(&now);

    dia = tiempoLocal->tm_mday;
    mes = tiempoLocal->tm_mon + 1;
    anio = tiempoLocal->tm_year + 1900;
    hora = tiempoLocal->tm_hour;
    minutos = tiempoLocal->tm_min;
    segundos = tiempoLocal->tm_sec;
}

Fecha::Fecha(int dia, int mes, int anio, int hora, int minutos, int segundos)
{
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
    this->hora = hora;
    this->minutos = minutos;
    this->segundos = segundos;
}

int Fecha::getDia()
{
    return dia;
}

int Fecha::getMes()
{
    return mes;
}

int Fecha::getAnio()
{
    return anio;
}

int Fecha::getHora()
{
    return hora;
}

int Fecha::getMinutos()
{
    return minutos;
}

int Fecha::getSegundos()
{
    return segundos;
}

void Fecha::setDia(int dia)
{
    this->dia = dia;
}

void Fecha::setMes(int mes)
{
    this->mes = mes;
}

void Fecha::setAnio(int anio)
{
    this->anio = anio;
}

void Fecha::setHora(int hora)
{
    this->hora = hora;
}

void Fecha::setMinutos(int minutos)
{
    this->minutos = minutos;
}

void Fecha::setSegundos(int segundos)
{
    this->segundos = segundos;
}
