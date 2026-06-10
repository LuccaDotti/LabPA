#include "logica/dominio/Producto.h"
#include "logica/dominio/ProveedorProducto.h"

#include <string>

using namespace std;

Producto::Producto(
    int codigo,
    const string &nombre,
    const string &descripcion,
    float precioUnitario,
    int stockActual,
    int stockMinimo,
    float puntajePromedio,
    int unidadesVendidas,
    bool bajoStock,
    Categoria *categoria
)
: codigo(codigo),
  nombre(nombre),
  descripcion(descripcion),
  precioUnitario(precioUnitario),
  stockActual(stockActual),
  stockMinimo(stockMinimo),
  puntajePromedio(puntajePromedio),
  unidadesVendidas(unidadesVendidas),
  bajoStock(bajoStock),
  categoria(categoria)
{
}

Producto::~Producto() = default;

// ... todos los getters y setters que ya tenés ...

vector<ProveedorProducto*> Producto::getProveedores() const
{
    return proveedores;
}

void Producto::agregarProveedor(
    ProveedorProducto* proveedorProducto
)
{
    proveedores.push_back(
        proveedorProducto
    );
}

void Producto::vender(int unidades)
{
    unidadesVendidas += unidades;
    stockActual -= unidades;

    if (stockActual < 0)
        stockActual = 0;
}

bool Producto::estaBajoStock() const
{
    return stockActual <= stockMinimo;
}
