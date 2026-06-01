cmake_minimum_required(VERSION 3.16)
project(labDottiMacedoSantos VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/DtFecha.cpp
    src/DtDireccion.cpp
    src/Categoria.cpp
    src/Calificacion.cpp
    src/Producto.cpp
    src/Proveedor.cpp
    src/ProveedorProducto.cpp
    src/LineaCompra.cpp
    src/OrdenCompra.cpp
    src/ClienteRegistrado.cpp
    src/LineaDetalle.cpp
    src/Venta.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
