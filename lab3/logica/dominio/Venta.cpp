#include "logica/dominio/Venta.h"
#include "logica/dominio/ClienteRegistrado.h"

using namespace std;

Venta::Venta(
    const Fecha& fecha,
    ClienteRegistrado* cliente
)
: fecha(fecha),
  cliente(cliente)
{
}

Venta::~Venta()
{
}

Fecha Venta::getFecha() const
{
    return fecha;
}

ClienteRegistrado* Venta::getCliente() const
{
    return cliente;
}

void Venta::setCliente(
    ClienteRegistrado* cliente
)
{
    this->cliente = cliente;
}

void Venta::agregarLineaDetalle(
    LineaDetalle* linea
)
{
    lineas.push_back(
        linea
    );
}

const vector<LineaDetalle*>& Venta::getLineas() const
{
    return lineas;
}

float Venta::getTotal() const
{
    float total = 0.0f;

    for (const auto* l : lineas)
    {
        total += l->getSubtotal();
    }

    return total;
}

vector<Venta*> Venta::getVentas() const
{
    return ventas;
}

void Venta::agregarVenta(
    Venta* venta
)
{
    ventas.push_back(
        venta
    );
}
