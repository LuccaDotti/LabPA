#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include "logica/controladores/tipoRetorno.h"

inline int leerEntero(const std::string &mensajeError = "Entrada invalida. Ingrese un numero: ")
{
    int valor;
    while (!(std::cin >> valor))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << mensajeError;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

inline float leerFlotante(const std::string &mensajeError = "Entrada invalida. Ingrese un numero: ")
{
    float valor;
    while (!(std::cin >> valor))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << mensajeError;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

inline std::string leerLineaNoVacia(const std::string &mensajeError = "Este campo no puede quedar vacio. Intente nuevamente: ")
{
    std::string linea;
    std::getline(std::cin, linea);
    while (linea.empty())
    {
        std::cout << mensajeError;
        std::getline(std::cin, linea);
    }
    return linea;
}

// ── Validaciones puras: solo reciben datos y devuelven TipoRet, sin I/O ──

inline TipoRet validarEmail(const std::string &email)
{
    bool tieneArroba = false;
    bool tienePunto = false;
    int posArroba = -1;

    for (int i = 0; i < (int)email.length(); i++)
    {
        if (email[i] == '@')
        {
            if (tieneArroba) return TipoRet::ERROR_EMAIL_INVALIDO;
            tieneArroba = true;
            posArroba = i;
        }
        if (email[i] == '.' && tieneArroba)
            tienePunto = true;
    }

    if (!tieneArroba || !tienePunto || posArroba < 0 || posArroba >= (int)email.length() - 1)
        return TipoRet::ERROR_EMAIL_INVALIDO;

    return TipoRet::OK;
}

inline TipoRet validarTelefono(const std::string &telefono)
{
    if (telefono.length() != 9) return TipoRet::ERROR_TELEFONO_INVALIDO;
    if (telefono[0] != '0')    return TipoRet::ERROR_TELEFONO_INVALIDO;

    for (int i = 0; i < (int)telefono.length(); i++)
        if (!std::isdigit(telefono[i])) return TipoRet::ERROR_TELEFONO_INVALIDO;

    return TipoRet::OK;
}

inline int diasEnMes(int mes)
{
    if (mes == 2) return 28;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
    return 31;
}

inline TipoRet validarFecha(int dia, int mes, int anio, int anioMinimo = 2026)
{
    if (anio < anioMinimo)            return TipoRet::ERROR_FECHA_INVALIDA;
    if (mes < 1 || mes > 12)          return TipoRet::ERROR_FECHA_INVALIDA;
    if (dia < 1 || dia > diasEnMes(mes)) return TipoRet::ERROR_FECHA_INVALIDA;
    return TipoRet::OK;
}
