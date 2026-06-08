#include "Cliente.h"
#include <string>
using namespace std;

Cliente::Cliente(int id) : id(id) {}

Cliente::~Cliente() {}

int Cliente::getId() const
{
    return id;
}

void Cliente::setId(int id)
{
    this->id = id;
}
