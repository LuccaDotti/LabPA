#include "logica/controladores/AdminController.h"

AdminController::AdminController() {}

AdminController::~AdminController() {

    for (Producto* p : productos)
        delete p;

    for (Categoria* c : categorias)
        delete c;

    for (Proveedor* p : proveedores)
        delete p;
}

// ===== PRODUCTOS =====

bool AdminController::agregarProducto(
    int codigo,
    const string& nombre,
    const string& descripcion,
    float precioUnitario,
    int stockActual,
    int stockMinimo,
    Categoria* categoria,
    Proveedor* proveedor
) {

    if (buscarProducto(codigo) != nullptr)
        return false;

    productos.push_back(
        new Producto(
            codigo,
            nombre,
            descripcion,
            precioUnitario,
            stockActual,
            stockMinimo,
            categoria,
            proveedor
        )
    );

    return true;
}

Producto* AdminController::buscarProducto(int codigo) const {

    for (Producto* p : productos)
        if (p->getCodigo() == codigo)
            return p;

    return nullptr;
}

vector<Producto*> AdminController::listarProductos() const {

    return productos;
}

bool AdminController::eliminarProducto(int codigo) {

    for (int i = 0; i < productos.size(); i++) {

        if (productos[i]->getCodigo() == codigo) {

            delete productos[i];

            productos.erase(
                productos.begin() + i
            );

            return true;
        }
    }

    return false;
}

// ===== CATEGORIAS =====

bool AdminController::agregarCategoria(
    const string& nombre,
    const string& descripcion
) {

    if (buscarCategoria(nombre) != nullptr)
        return false;

    categorias.push_back(
        new Categoria(
            nombre,
            descripcion
        )
    );

    return true;
}

Categoria* AdminController::buscarCategoria(
    const string& nombre
) const {

    for (Categoria* c : categorias)
        if (c->getNombre() == nombre)
            return c;

    return nullptr;
}

vector<Categoria*> AdminController::listarCategorias() const {

    return categorias;
}

// ===== PROVEEDORES =====

bool AdminController::agregarProveedor(
    int rut,
    const string& nombreEmpresa,
    int telefono,
    const string& nombreContacto
) {

    if (buscarProveedor(rut) != nullptr)
        return false;

    proveedores.push_back(
        new Proveedor(
            rut,
            nombreEmpresa,
            telefono,
            nombreContacto
        )
    );

    return true;
}

Proveedor* AdminController::buscarProveedor(
    int rut
) const {

    for (Proveedor* p : proveedores)
        if (p->getRut() == rut)
            return p;

    return nullptr;
}

vector<Proveedor*> AdminController::listarProveedores() const {

    return proveedores;
}
