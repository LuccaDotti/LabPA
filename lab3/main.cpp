#include <iostream>

#include "vista/MenuPrincipal.h"

#include "logica/controladores/AdminController.h"
#include "logica/controladores/EmpleadoController.h"
#include "logica/controladores/VentaController.h"

#include "logica/dominio/Fecha.h"
#include "logica/dominio/ClienteRegistrado.h"
#include "logica/dominio/Venta.h"
#include "logica/dominio/Calificacion.h"

using namespace std;

int main() {

	AdminController admin;
	EmpleadoController empleado(admin);
	VentaController ventaCtrl(admin);

	// Datos de ejemplo
	admin.agregarCategoria("Electronica", "Dispositivos y accesorios");

	Categoria* cat = admin.buscarCategoria("Electronica");

	admin.agregarProducto(
		1001,
		"Reloj Inteligente",
		"Reloj con funciones smart",
		199.99f,
		50,
		5,
		cat
	);

	admin.agregarProveedor(12345678, "ACME Ltda.", 222333444, "Juan Perez");

	Fecha* fechaEntrega = new Fecha(1, 6, 2026, 10, 0, 0);

	// Asociar proveedor y producto
	admin.asociarProveedorProducto(12345678, 1001, 150.0f, fechaEntrega);

	// Ya fue copiada por valor dentro de ProveedorProducto, liberar memoria
	delete fechaEntrega;

	// Cliente registrado de ejemplo
	ClienteRegistrado* cliente = new ClienteRegistrado(1, 98765432, "Calle Falsa 123", "cliente@ejemplo.com", "Ana Gomez", 0.0f);
	empleado.agregarCliente(cliente);

	// Registrar una venta simple
	Fecha fechaVenta(2, 6, 2026, 12, 30, 0);
	Venta* venta = new Venta(fechaVenta, cliente);
	ventaCtrl.registrarVenta(venta);

	// Agregar calificacion
	Calificacion* cal = new Calificacion(5, "Excelente producto", &fechaVenta, admin.buscarProducto(1001));
	ventaCtrl.agregarCalificacion(cal);

	// Mostrar menu principal (interactivo)
	MenuPrincipal menu(admin, empleado, ventaCtrl);
	menu.mostrar();

	return 0;
}

#include "vista/MenuPrincipal.h"

int main()
{
    AdminController adminCtrl;

    EmpleadoController empleadoCtrl(adminCtrl);

    VentaController ventaCtrl(adminCtrl);

    MenuPrincipal menu(adminCtrl, empleadoCtrl, ventaCtrl);

    menu.mostrar();

    return 0;
}
