#pragma once

#include <string>
#include "logica/controladores/Rol.h"

using namespace std;

class Usuario
{
private:
    string nombreCompleto;
    string email;
    string password;
    Rol rol;

public:
    Usuario(
        const string& nombreCompleto,
        const string& email,
        const string& password,
        Rol rol
    );

    string getNombreCompleto() const;
    string getEmail() const;
    string getPassword() const;
    Rol getRol() const;

    void setNombreCompleto(const string& nombreCompleto);
    void setEmail(const string& email);
    void setPassword(const string& password);
    void setRol(Rol rol);
};
