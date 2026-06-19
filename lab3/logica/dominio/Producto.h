#pragma once

#include <string>
#include <vector>

using namespace std;

class Categoria; // forward declaration
class ProveedorProducto; // forward declaration

class Producto
{
private:
    int codigo;
    string nombre;
    string descripcion;
    float precioUnitario;
    int stockActual;
    int stockMinimo;

    float puntajePromedio;
    int unidadesVendidas;
    bool bajoStock;
    Categoria *categoria;
    
    // Relación a proveedores (ProveedorProducto)
    std::vector<ProveedorProducto*> proveedores;

public:

    Producto(
        int codigo,
        const string &nombre,
        const string &descripcion,
        float precioUnitario,
        int stockActual,
        int stockMinimo,
        float puntajePromedio,
        int unidadesVendidas,
        bool bajoStock,
        Categoria *categoria = nullptr
    );

    ~Producto();

    int getCodigo() const;
    void setCodigo(int codigo);

    string getNombre() const;
    void setNombre(const string &nombre);

    string getDescripcion() const;
    void setDescripcion(const string &descripcion);

    float getPrecioUnitario() const;
    void setPrecioUnitario(float precioUnitario);

    int getStockActual() const;
    void setStockActual(int stockActual);

    int getStockMinimo() const;
    void setStockMinimo(int stockMinimo);

    float getPuntajePromedio() const;
    void setPuntajePromedio(float puntajePromedio);

    int getUnidadesVendidas() const;
    void setUnidadesVendidas(int unidadesVendidas);

    bool isBajoStock() const;
    void setBajoStock(bool bajoStock);

    Categoria* getCategoria() const;
    void setCategoria(Categoria *categoria);

    void agregarProveedor(ProveedorProducto* proveedorProducto);
    std::vector<ProveedorProducto*> getProveedores() const;

    // Métodos de dominio (stubs)
    void vender(int unidades);
    bool estaBajoStock() const;
};
