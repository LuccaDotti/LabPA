#pragma once
using namespace std;
#include "logica/dominio/Cliente.h"
#include <string>

class ClienteRegistrado : public Cliente {
private:
	int rut;
	string direccion;
	string correo;
	string nombreCompleto;
	float totalFacturado;
public:
	ClienteRegistrado(int id, int rut, const string& direccion, const string& correo, const string& nombreCompleto, float totalFacturado);
	~ClienteRegistrado() override;

	int getRut() const;
	void setRut(int rut);

	string getDireccion() const;
	void setDireccion(const string& direccion);

	string getCorreo() const;
	void setCorreo(const string& correo);

	string getNombreCompleto() const;
	void setNombreCompleto(const string& nombreCompleto);

	float getTotalFacturado() const;
	void setTotalFacturado(float totalFacturado);

	string clienteTipo() const override;

	// Métodos de dominio (stubs)
	void agregarFacturacion(float monto);
};

