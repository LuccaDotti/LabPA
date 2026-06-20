#include "logica/dominio/Usuario.h"

Usuario::Usuario(
    const string& nombreCompleto,
    const string& email,
    const string& password,
    Rol rol
)
    : nombreCompleto(nombreCompleto),
      email(email),
      password(password),
      rol(rol)
{
}

string Usuario::getNombreCompleto() const
{
    return nombreCompleto;
}

string Usuario::getEmail() const
{
    return email;
}

string Usuario::getPassword() const
{
    return password;
}

Rol Usuario::getRol() const
{
    return rol;
}

void Usuario::setNombreCompleto(const string& nombreCompleto)
{
    this->nombreCompleto = nombreCompleto;
}

void Usuario::setEmail(const string& email)
{
    this->email = email;
}

void Usuario::setPassword(const string& password)
{
    this->password = password;
}

void Usuario::setRol(Rol rol)
{
    this->rol = rol;
}
