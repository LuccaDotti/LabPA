 #pragma once
using namespace std;
#include <string>

class Cliente {
protected:
	int id;
public:
	explicit Cliente(int id);
	virtual ~Cliente();

	int getId() const;
	void setId(int id);

	// Hace la clase abstracta para permitir polimorfismo
	virtual string clienteTipo() const = 0;
};

