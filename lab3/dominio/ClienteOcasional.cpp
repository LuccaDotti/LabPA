#include "ClienteOcasional.h"
#include <string>
using namespace std;

ClienteOcasional::ClienteOcasional(int id) : Cliente(id) {}

ClienteOcasional::~ClienteOcasional() = default;

string ClienteOcasional::clienteTipo() const
{
    return "Ocasional";
}
