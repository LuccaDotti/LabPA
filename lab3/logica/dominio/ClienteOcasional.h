#pragma once
using namespace std;
#include "Cliente.h"
#include <string>

class ClienteOcasional : public Cliente {
public:
	explicit ClienteOcasional(int id);
	~ClienteOcasional() override;

	string clienteTipo() const override;
};
