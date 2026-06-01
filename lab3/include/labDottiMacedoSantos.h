#pragma once
#include <iostream>
#include <string>
using namespace std;

class Lab {
public:
    Lab();
    void run();
    string getName() const;

private:
    string name;
};
