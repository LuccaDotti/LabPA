#include "logica/controladores/AdminController.h"

AdminController* AdminController::instancia = NULL;

AdminController::AdminController()
{
    usuarios.push_back(new Usuario("Administrador", "admin@gmail.com", "admin2026", Rol::ADMINISTRADOR));
    usuarios.push_back(new Usuario("Empleado", "empleado@gmail.com", "empleado1234", Rol::EMPLEADO));

    // ===== Categorías =====
    Categoria* catBebidas = new Categoria("Bebidas", "Bebidas frias y calientes");
    Categoria* catAlmacen = new Categoria("Almacen", "Productos no perecederos");
    Categoria* catLimpieza = new Categoria("Limpieza", "Articulos de limpieza");
    categorias.push_back(catBebidas);
    categorias.push_back(catAlmacen);
    categorias.push_back(catLimpieza);

    // ===== Productos =====
    Producto* p1 = new Producto(1001, "Coca Cola 1.5L", "Gaseosa cola", 95.0f, 50, 10, 0.0f, 0, false, catBebidas);
    Producto* p2 = new Producto(1002, "Agua Salus 1.5L", "Agua mineral", 60.0f, 40, 10, 0.0f, 0, false, catBebidas);
    Producto* p3 = new Producto(2001, "Arroz 1kg", "Arroz blanco", 55.0f, 30, 5, 0.0f, 0, false, catAlmacen);
    Producto* p4 = new Producto(2002, "Fideos 500g", "Fideos secos", 48.0f, 25, 5, 0.0f, 0, false, catAlmacen);
    Producto* p5 = new Producto(3001, "Detergente 750ml", "Detergente liquido", 120.0f, 3, 5, 0.0f, 0, true, catLimpieza);
    productos.push_back(p1);
    productos.push_back(p2);
    productos.push_back(p3);
    productos.push_back(p4);
    productos.push_back(p5);

    // ===== Proveedores =====
    Proveedor* prov1 = new Proveedor(100111222, "Distribuidora Norte", 29001122, "Juan Perez");
    Proveedor* prov2 = new Proveedor(200333444, "Almacen Mayorista SA", 29003344, "Maria Gomez");
    proveedores.push_back(prov1);
    proveedores.push_back(prov2);

    // ===== ProveedorProducto (asociaciones) =====
    ProveedorProducto* pp1 = new ProveedorProducto(prov1, p1, 70.0f, Fecha(1, 7, 2026, 0, 0, 0));
    ProveedorProducto* pp2 = new ProveedorProducto(prov2, p3, 40.0f, Fecha(5, 7, 2026, 0, 0, 0));
    proveedorProductos.push_back(pp1);
    proveedorProductos.push_back(pp2);
    p1->agregarProveedor(pp1);
    p3->agregarProveedor(pp2);
    prov1->agregarProducto(pp1);
    prov2->agregarProducto(pp2);
}

AdminController* AdminController::getInstancia()
{
    if (instancia == NULL)
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

         for (Usuario* u : usuarios)
            delete u;
    }

TipoRet AdminController::agregarProducto(int codigo, const string& nombre, const string& descripcion, float precioUnitario, int stockActual, int stockMinimo, Categoria* categoria)
{
    if (buscarProducto(codigo) != NULL)
        return TipoRet::ERROR_PRODUCTO_EXISTENTE;

    if (stockActual < 0 || stockMinimo < 0)
        return TipoRet::ERROR_STOCK_NEGATIVO;

    productos.push_back(
        new Producto(codigo, nombre, descripcion, precioUnitario, stockActual, stockMinimo, 0.0, 0, false, categoria)
    );

    return TipoRet::OK;
}

Producto* AdminController::buscarProducto(int codigo) const
{
    for (Producto* p : productos)
    {
        if (p->getCodigo() == codigo)
            return p;
    }

    return NULL;
}

vector<Producto*> AdminController::listarProductos() const
{
    return productos;
}

TipoRet AdminController::modificarProducto(int codigo, const string& nuevoNombre, const string& nuevaDescripcion, float nuevoPrecio, Categoria* nuevaCategoria, int nuevoStockMinimo)
{
    Producto* producto = buscarProducto(codigo);

    if (producto == NULL)
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;

    for (Producto* p : productos)
    {
        if (
            p != producto &&
            p->getNombre() == nuevoNombre
        )
        {
            return TipoRet::ERROR_PRODUCTO_EXISTENTE;
        }
    }

    if (nuevoStockMinimo < 0)
        return TipoRet::ERROR_STOCK_NEGATIVO;

    producto->setNombre(nuevoNombre);
    producto->setDescripcion(nuevaDescripcion);
    producto->setPrecioUnitario(nuevoPrecio);
    producto->setCategoria(nuevaCategoria);
    producto->setStockMinimo(nuevoStockMinimo);

    return TipoRet::OK;
}

TipoRet AdminController::eliminarProducto(int codigo)
{
    Producto* producto = buscarProducto(codigo);

    if (producto == NULL)
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;

    for (unsigned int i = 0; i < productos.size(); i++)
    {
        if (productos[i]->getCodigo() == codigo)
        {
            delete productos[i];

            productos.erase(
                productos.begin() + i
            );

            return TipoRet::OK;
        }
    }

    return TipoRet::ERROR_PRODUCTO_INEXISTENTE;
}

TipoRet AdminController::agregarCategoria(const string& nombre, const string& descripcion)
{
    if (buscarCategoria(nombre) != NULL)
        return TipoRet::ERROR_CATEGORIA_EXISTENTE;

    categorias.push_back(
        new Categoria(nombre, descripcion)
    );

    return TipoRet::OK;
}

Categoria* AdminController::buscarCategoria(const string& nombre) const
{
    for (Categoria* c : categorias)
    {
        if (c->getNombre() == nombre)
            return c;
    }

    return NULL;
}

vector<Categoria*> AdminController::listarCategorias() const
{
    return categorias;
}

TipoRet AdminController::modificarCategoria(const string& nombreActual, const string& nuevoNombre, const string& nuevaDescripcion)
{
    Categoria* categoria =
        buscarCategoria(nombreActual);

    if (categoria == NULL)
        return TipoRet::ERROR_CATEGORIA_INEXISTENTE;

    for (Categoria* c : categorias)
    {
        if (
            c != categoria &&
            c->getNombre() == nuevoNombre
        )
        {
            return TipoRet::ERROR_CATEGORIA_EXISTENTE;
        }
    }

    categoria->setNombre(nuevoNombre);
    categoria->setDescripcion(nuevaDescripcion);

    return TipoRet::OK;
}

TipoRet AdminController::agregarProveedor(int rut, const string& nombreEmpresa, int telefono, const string& nombreContacto)
{
    if (buscarProveedor(rut) != NULL)
        return TipoRet::ERROR_PROVEEDOR_EXISTENTE;

    proveedores.push_back(
        new Proveedor(rut, nombreEmpresa, telefono, nombreContacto)
    );

    return TipoRet::OK;
}

Proveedor* AdminController::buscarProveedor(int rut) const
{
    for (Proveedor* p : proveedores)
    {
        if (p->getRut() == rut)
            return p;
    }

    return NULL;
}

vector<Proveedor*> AdminController::listarProveedores() const
{
    return proveedores;
}

TipoRet AdminController::modificarProveedor(int rut, const string& nuevoNombreEmpresa, int nuevoTelefono, const string& nuevoNombreContacto)
{
    Proveedor* proveedor =
        buscarProveedor(rut);

    if (proveedor == NULL)
        return TipoRet::ERROR_PROVEEDOR_INEXISTENTE;

    proveedor->setNombreEmpresa(
        nuevoNombreEmpresa
    );

    proveedor->setTelefono(
        nuevoTelefono
    );

    proveedor->setNombreContacto(
        nuevoNombreContacto
    );

    return TipoRet::OK;
}

TipoRet AdminController::asociarProveedorProducto(int rutProveedor, int codigoProducto, float precioCompra, Fecha* fechaEntrega)
{
    Proveedor* proveedor =
        buscarProveedor(rutProveedor);

    if (proveedor == NULL)
        return TipoRet::ERROR_PROVEEDOR_INEXISTENTE;

    Producto* producto =
        buscarProducto(codigoProducto);

    if (producto == NULL)
        return TipoRet::ERROR_PRODUCTO_INEXISTENTE;

    for (ProveedorProducto* pp : proveedorProductos)
    {
        if (
            pp->getProveedor()->getRut() == rutProveedor &&
            pp->getProducto()->getCodigo() == codigoProducto
        )
        {
            pp->setPrecioCompra(
                precioCompra
            );

            return TipoRet::OK;
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

    return TipoRet::OK;
}

vector<ProveedorProducto*> AdminController::listarProveedorProductos() const
{
    return proveedorProductos;
}

TipoRet AdminController::agregarUsuario(const string& nombre, const string& email, const string& password, Rol rol)
{
    for (Usuario* u : usuarios)
    {
        if (u->getEmail() == email)
            return TipoRet::ERROR_USUARIO_EXISTENTE;
    }

    Usuario* nuevo = new Usuario(nombre, email, password, rol);
    usuarios.push_back(nuevo);
    return TipoRet::OK;
}

Usuario* AdminController::buscarUsuarioPorEmail(const string& email) const
{
    for (Usuario* u : usuarios)
    {
        if (u->getEmail() == email)
            return u;
    }
    return nullptr;
}

vector<Usuario*> AdminController::listarUsuarios() const
{
    return usuarios;
}

TipoRet AdminController::eliminarUsuario(const string& email)
{
    for (size_t i = 0; i < usuarios.size(); i++)
    {
        if (usuarios[i]->getEmail() == email)
        {
            delete usuarios[i];
            usuarios.erase(usuarios.begin() + i);
                return TipoRet::OK;
        }
    }
    return TipoRet::ERROR_CREDENCIALES_INVALIDAS;
}
