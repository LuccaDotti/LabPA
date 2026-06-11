#pragma once
using namespace std;
#include "logica/dominio/Calificacion.h"
#include <string>

class ClienteRegistrad
{
private:
	int rut;
	string direccion;
	string correo;
	string nombreCompleto;
	float totalFacturado;

	vector<Calificacion*> calificaciones;
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

	void agregarCalificacion(Calificacion* calificacion);
};

