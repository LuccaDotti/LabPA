#include "labDottiMacedoSantos.h"
using namespace std;

Lab::Lab() : name("labDottiMacedoSantos") {}

void Lab::run()
{
    cout << "Proyecto: " << name << endl;
    cout << "Iniciando laboratorio..." << endl;
}

string Lab::getName() const
{
    return name;
}
