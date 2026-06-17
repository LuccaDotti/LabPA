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

bool AdminController::agregarProducto(
    int codigo, const string& nombre, const string& descripcion, float precioUnitario, int stockActual, int stockMinimo, Categoria* categoria
)
{
    if (buscarProducto(codigo) != nullptr)
    {
        throw runtime_error(
            "Ya existe un producto con ese codigo."
        );
    }

    if (stockActual < 0)
    {
        throw runtime_error(
            "El stock no puede ser negativo."
        );
    }

    productos.push_back(
        new Producto(codigo, nombre, descripcion, precioUnitario, stockActual, stockMinimo, 0.0, 0, false, categoria)
    );

    return true;
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

bool AdminController::modificarProducto(int codigo, const string& nuevoNombre, const string& nuevaDescripcion, float nuevoPrecio, Categoria* nuevaCategoria, int nuevoStockMinimo)
{
    Producto* producto =
        buscarProducto(codigo);

    if (producto == nullptr)
    {
        throw runtime_error(
            "Producto inexistente."
        );
    }

    for (Producto* p : productos)
    {
        if (
            p != producto &&
            p->getNombre() == nuevoNombre
        )
        {
            throw runtime_error(
                "Ya existe un producto con ese nombre."
            );
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

    return true;
}

bool AdminController::eliminarProducto(
    int codigo
)
{
    Producto* producto =
        buscarProducto(codigo);

    if (producto == nullptr)
    {
        throw runtime_error(
            "Producto inexistente."
        );
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

            return true;
        }
    }

    return false;
}

bool AdminController::agregarCategoria(const string& nombre, const string& descripcion)
{
    if (buscarCategoria(nombre) != nullptr)
    {
        throw runtime_error(
            "Ya existe una categoria con ese nombre."
        );
    }

    categorias.push_back(
        new Categoria(
            nombre,
            descripcion
        )
    );

    return true;
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

bool AdminController::modificarCategoria(const string& nombreActual, const string& nuevoNombre, const string& nuevaDescripcion)
{
    Categoria* categoria =
        buscarCategoria(nombreActual);

    if (categoria == nullptr)
    {
        throw runtime_error(
            "La categoria no existe."
        );
    }

    for (Categoria* c : categorias)
    {
        if (
            c != categoria &&
            c->getNombre() == nuevoNombre
        )
        {
            throw runtime_error(
                "Ya existe una categoria con ese nombre."
            );
        }
    }

    categoria->setNombre(
        nuevoNombre
    );

    categoria->setDescripcion(
        nuevaDescripcion
    );

    return true;
}

bool AdminController::agregarProveedor(int rut, const string& nombreEmpresa, int telefono, const string& nombreContacto)
{
    if (buscarProveedor(rut) != nullptr)
    {
        throw runtime_error(
            "Ya existe un proveedor con ese RUT."
        );
    }

    proveedores.push_back(
        new Proveedor(rut, nombreEmpresa, telefono, nombreContacto)
    );

    return true;
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

bool AdminController::modificarProveedor(int rut, const string& nuevoNombreEmpresa, int nuevoTelefono, const string& nuevoNombreContacto)
{
    Proveedor* proveedor =
        buscarProveedor(rut);

    if (proveedor == nullptr)
    {
        throw runtime_error(
            "Proveedor inexistente."
        );
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

    return true;
}

bool AdminController::asociarProveedorProducto(int rutProveedor, int codigoProducto, float precioCompra, Fecha* fechaEntrega)
{
    Proveedor* proveedor =
        buscarProveedor(
            rutProveedor
        );

    if (proveedor == nullptr)
    {
        throw runtime_error(
            "Proveedor inexistente."
        );
    }

    Producto* producto =
        buscarProducto(
            codigoProducto
        );

    if (producto == nullptr)
    {
        throw runtime_error(
            "Producto inexistente."
        );
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

            return true;
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

    return true;
}

vector<ProveedorProducto*>
AdminController::listarProveedorProductos() const
{
    return proveedorProductos;
}
