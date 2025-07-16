#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
using namespace std;

class Driver {
public:
    int id;
    string name;
    int location;
    bool isAvailable;  // New attribute to track availability

    Driver(int id, string name, int location)
        : id(id), name(name), location(location), isAvailable(true) {}  // Default available
};

#endif
