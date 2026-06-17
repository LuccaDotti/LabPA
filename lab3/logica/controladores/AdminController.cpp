#include "logica/controladores/AdminController.h"

AdminController* AdminController::instancia = nullptr;

AdminController::AdminController()
{
}

AdminController* AdminController::getInstancia()
{
    if (instancia == nullptr)
    {
        instancia = new AdminController();
    }

    return instancia;
}

AdminController::~AdminController()
{
    for (Producto* p : productos)
        delete p;

    for (Categoria* c : categorias)
        delete c;

    for (Proveedor* p : proveedores)
        delete p;

    for (ProveedorProducto* pp : proveedorProductos)
        delete pp;
}

int AdminController::agregarProducto(int codigo, const string& nombre, const string& descripcion, float precioUnitario, int stockActual, int stockMinimo, Categoria* categoria)
{
    if (buscarProducto(codigo) != nullptr)
    {
        return 1;
    }

    if (stockActual < 0)
    {
        return 2;
    }

    productos.push_back(new Producto(codigo, nombre, descripcion, precioUnitario, stockActual, stockMinimo, 0.0, 0, false, categoria)
    );

    return 0;
}

Producto* AdminController::buscarProducto(int codigo) const
{
    for (Producto* p : productos)
    {
        if (p->getCodigo() == codigo)
            return p;
    }

    return nullptr;
}

vector<Producto*> AdminController::listarProductos() const
{
    return productos;
}

int AdminController::modificarProducto(int codigo, const string& nuevoNombre, const string& nuevaDescripcion, float nuevoPrecio, Categoria* nuevaCategoria, int nuevoStockMinimo)
{
    Producto* producto =
        buscarProducto(codigo);

    if (producto == nullptr)
    {
        return 1;
    }

    for (Producto* p : productos)
    {
        if (
            p != producto &&
            p->getNombre() == nuevoNombre
        )
        {
            return 2;
        }
    }

    producto->setNombre(
        nuevoNombre
    );

    producto->setDescripcion(
        nuevaDescripcion
    );

    producto->setPrecioUnitario(
        nuevoPrecio
    );

    producto->setCategoria(
        nuevaCategoria
    );

    producto->setStockMinimo(
        nuevoStockMinimo
    );

    return 0;
}

int AdminController::eliminarProducto(
    int codigo
)
{
    Producto* producto =
        buscarProducto(codigo);

    if (producto == nullptr)
    {
        return 1;
    }

    for (
        int i = 0;
        i < productos.size();
        i++
    )
    {
        if (
            productos[i]->getCodigo()
            == codigo
        )
        {
            delete productos[i];

            productos.erase(
                productos.begin() + i
            );

            return 0;
        }
    }

    return 2;
}

int AdminController::agregarCategoria(const string& nombre, const string& descripcion)
{
    if (buscarCategoria(nombre) != nullptr)
    {
        return 1;
    }

    categorias.push_back(
        new Categoria(nombre, descripcion)
    );

    return 0;
}

Categoria* AdminController::buscarCategoria(const string& nombre) const
{
    for (Categoria* c : categorias)
    {
        if (c->getNombre() == nombre)
            return c;
    }

    return nullptr;
}

vector<Categoria*> AdminController::listarCategorias() const
{
    return categorias;
}

int AdminController::modificarCategoria(const string& nombreActual, const string& nuevoNombre, const string& nuevaDescripcion)
{
    Categoria* categoria =
        buscarCategoria(nombreActual);

    if (categoria == nullptr)
    {
        return 1;
    }

    for (Categoria* c : categorias)
    {
        if (
            c != categoria &&
            c->getNombre() == nuevoNombre
        )
        {
            return 2;
        }
    }

    categoria->setNombre(
        nuevoNombre
    );

    categoria->setDescripcion(
        nuevaDescripcion
    );

    return 0;
}

int AdminController::agregarProveedor(int rut, const string& nombreEmpresa, int telefono, const string& nombreContacto)
{
    if (buscarProveedor(rut) != nullptr)
    {
        return 1;
    }

    proveedores.push_back(
        new Proveedor(rut, nombreEmpresa, telefono, nombreContacto)
    );

    return 0;
}

Proveedor* AdminController::buscarProveedor(int rut) const
{
    for (Proveedor* p : proveedores)
    {
        if (p->getRut() == rut)
            return p;
    }

    return nullptr;
}

vector<Proveedor*> AdminController::listarProveedores() const
{
    return proveedores;
}

int AdminController::modificarProveedor(int rut, const string& nuevoNombreEmpresa, int nuevoTelefono, const string& nuevoNombreContacto)
{
    Proveedor* proveedor =
        buscarProveedor(rut);

    if (proveedor == nullptr)
    {
        return 1;
    }

    proveedor->setNombreEmpresa(
        nuevoNombreEmpresa
    );

    proveedor->setTelefono(
        nuevoTelefono
    );

    proveedor->setNombreContacto(
        nuevoNombreContacto
    );

    return 0;
}

int AdminController::asociarProveedorProducto(int rutProveedor, int codigoProducto, float precioCompra, Fecha* fechaEntrega)
{
    Proveedor* proveedor =
        buscarProveedor(
            rutProveedor
        );

    if (proveedor == nullptr)
    {
        return 1;
    }

    Producto* producto =
        buscarProducto(
            codigoProducto
        );

    if (producto == nullptr)
    {
        return 2;
    }

    for (
        ProveedorProducto* pp :
        proveedorProductos
    )
    {
        if (
            pp->getProveedor()->getRut()
                == rutProveedor
            &&
            pp->getProducto()->getCodigo()
                == codigoProducto
        )
        {
            pp->setPrecioCompra(
                precioCompra
            );

            return 0;
        }
    }

    ProveedorProducto* relacion =
        new ProveedorProducto(proveedor, producto, precioCompra, *fechaEntrega);

    proveedorProductos.push_back(
        relacion
    );

    proveedor->agregarProducto(
        relacion
    );

    producto->agregarProveedor(
        relacion
    );

    return 0;
}

vector<ProveedorProducto*>
AdminController::listarProveedorProductos() const
{
    return proveedorProductos;
}
