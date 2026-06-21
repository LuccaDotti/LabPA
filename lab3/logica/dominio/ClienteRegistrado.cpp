#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/Venta.h"

using namespace std;

ClienteRegistrado::ClienteRegistrado(
    int rut,
    const Direccion &direccion,
    const string &correo,
    const string &nombreCompleto,
    int contrasenia,
    float totalFacturado)
    : rut(rut),
      direccion(direccion),
      correo(correo),
      nombreCompleto(nombreCompleto),
      contrasenia(contrasenia),
      totalFacturado(totalFacturado)
{
}

ClienteRegistrado::~ClienteRegistrado()
{
}

int ClienteRegistrado::getContrasenia() const
{
    return contrasenia;
}

void ClienteRegistrado::setContrasenia(int contrasenia)
{
    this->contrasenia = contrasenia;
}

int ClienteRegistrado::getRut() const
{
    return rut;
}

void ClienteRegistrado::setRut(
    int rut)
{
    this->rut = rut;
}

Direccion ClienteRegistrado::getDireccion() const
{
    return direccion;
}

void ClienteRegistrado::setDireccion(
    const Direccion &direccion)
{
    this->direccion = direccion;
}

string ClienteRegistrado::getCorreo() const
{
    return correo;
}

void ClienteRegistrado::setCorreo(
    const string &correo)
{
    this->correo = correo;
}

string ClienteRegistrado::getNombreCompleto() const
{
    return nombreCompleto;
}

void ClienteRegistrado::setNombreCompleto(
    const string &nombreCompleto)
{
    this->nombreCompleto = nombreCompleto;
}

float ClienteRegistrado::getTotalFacturado() const
{
    return totalFacturado;
}

void ClienteRegistrado::setTotalFacturado(
    float totalFacturado)
{
    this->totalFacturado = totalFacturado;
}

vector<Venta *> ClienteRegistrado::getVentas() const
{
    return ventas;
}

// Calificar Producto
TipoRet ClienteRegistrado::calificarProducto(int codigoProducto, int calificacion, string comentario)
{
    Producto *productoEncontrado = nullptr;

    for (Venta *venta : ventas)
    {
        for (LineaDetalle *linea : venta->getLineas())
        {
            if (linea->getProducto()->getCodigo() == codigoProducto)
            {
                productoEncontrado = linea->getProducto();
                break;
            }
        }
        if (productoEncontrado != nullptr)
            break;
    }

    if (productoEncontrado == nullptr)
        return TipoRet::ERROR_PRODUCTO_NO_COMPRADO;

    if (calificacion < 1 || calificacion > 5)
        return TipoRet::ERROR_CALIFICACION_INVALIDA;

    Calificacion *nuevaCalificacion = new Calificacion(calificacion, comentario, new Fecha(), productoEncontrado);
    agregarCalificacion(nuevaCalificacion);

    // Recalcular promedio considerando todas las calificaciones históricas del producto
    float suma = 0;
    int count = 0;
    for (Calificacion *c : calificaciones)
    {
        if (c->getProducto()->getCodigo() == codigoProducto)
        {
            suma += c->getPuntaje();
            count++;
        }
    }
    productoEncontrado->setPuntajePromedio(suma / count);

    return TipoRet::OK;
}

void ClienteRegistrado::agregarVenta(
    Venta *venta)
{
    ventas.push_back(
        venta);
}

vector<Calificacion *> ClienteRegistrado::getCalificaciones() const
{
    return calificaciones;
}

void ClienteRegistrado::agregarCalificacion(
    Calificacion *calificacion)
{
    calificaciones.push_back(
        calificacion);
}

void ClienteRegistrado::agregarFacturacion(
    float monto)
{
    totalFacturado += monto;
}

Producto *ClienteRegistrado::consultarInformacionDetalladaProducto(int codigoProducto) const
{
    // Buscar el producto en las compras del cliente
    for (Venta *venta : ventas)
    {
        for (LineaDetalle *linea : venta->getLineas())
        {
            if (linea->getProducto()->getCodigo() == codigoProducto)
            {
                return linea->getProducto(); // Retorna el producto, nada más
            }
        }
    }

    return nullptr; // No encontrado
}
