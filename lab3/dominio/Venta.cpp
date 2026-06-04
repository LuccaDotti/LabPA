#include "Venta.h"
using namespace std;

Venta::Venta(const Fecha& fecha, Cliente* cliente)
    : fecha(fecha), cliente(cliente) {}

Fecha Venta::getFecha() const {
    return fecha;
}

Cliente* Venta::getCliente() const {
    return cliente;
}

void Venta::agregarLineaDetalle(LineaDetalle* linea) {
    lineas.push_back(linea);
}

const vector<LineaDetalle*>& Venta::getLineas() const {
    return lineas;
}

float Venta::getTotal() const {
    float total = 0.0f;
    for (const auto* l : lineas)
        total += l->getSubtotal();
    return total;
}