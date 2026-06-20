#include "logica/controladores/VentaController.h"
#include "logica/controladores/AdminController.h"
#include "logica/dominio/Venta.h"
#include "logica/dominio/Calificacion.h"
#include "logica/controladores/tipoRetorno.h"

using namespace std;

VentaController::VentaController(
    AdminController& adminController
)
: adminController(adminController)
{
}

VentaController::~VentaController()
{
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
    {
        return TipoRet::ERROR_PRODUCTO_NO_COMPRADO;
    }

    if (calificacion < 1 || calificacion > 5)
    {
        return TipoRet::ERROR_CALIFICACION_INVALIDA;
    }

    Calificacion *nuevaCalificacion = new Calificacion(calificacion, comentario, new Fecha(), productoEncontrado);
    agregarCalificacion(nuevaCalificacion);

    return TipoRet::OK;
}

// ===== VENTAS =====

bool VentaController::registrarVenta(
    Venta* venta
)
{
    return true;
}

vector<Calificacion*> VentaController::listarCalificaciones() const {

    return calificaciones;
}

vector<Calificacion*> VentaController::getCalificacionesPorProducto(
    int codigoProducto
) const {
    vector<Calificacion*> calificacionesProducto;

    for (Calificacion* calificacion : calificaciones) {
        Producto* producto = calificacion->getProducto();
        if (producto && producto->getCodigo() == codigoProducto) {
            calificacionesProducto.push_back(calificacion);
        }
    }

    return calificacionesProducto;
}
