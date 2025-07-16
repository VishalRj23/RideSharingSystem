#ifndef RIDER_H
#define RIDER_H

#include <iostream>
using namespace std;

class Rider {
public:
    int id;
    string name;
    int location;
    int destination;
    bool isRiding;

    // Constructor ensuring default values when necessary
    Rider(int id, string name, int location, int destination = -1)
        : id(id), name(name), location(location), destination(destination), isRiding(destination != -1) {}

    // Function to end the ride
    void endRide() {
        isRiding = false;
        location = destination; // Update location to final destination
        destination = -1;       // Reset destination
    }
};

#endif
