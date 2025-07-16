#ifndef RIDEMATCHING_H
#define RIDEMATCHING_H

#include <iostream>
#include <vector>
#include <map>
#include "Graph.h"
#include "Rider.h"
#include <climits>

using namespace std;

class Driver {
public:
    int id;
    string name;
    int location;
    bool available;

    Driver(int id, string name, int location)
        : id(id), name(name), location(location), available(true) {}
};

class RideMatching {
private:
    Graph* cityGraph;
    vector<Driver> drivers;
    vector<pair<Rider, Driver>> activeRides; // ✅ Stores active rides properly

public:
    RideMatching(Graph* graph) : cityGraph(graph) {}

    void addDriver(int id, string name, int location) {
        drivers.push_back(Driver(id, name, location));
    }

    bool assignRide(Rider& rider, int destination) {
        Driver* bestDriver = nullptr;
        int minDistance = INT_MAX;

        // Find the nearest available driver
        for (auto& driver : drivers) {
            if (driver.available) {
                vector<int> path = cityGraph->shortestPath(driver.location, rider.location);
                int distance = path.size(); // ✅ Use path size to determine distance
                if (distance < minDistance) {
                    minDistance = distance;
                    bestDriver = &driver;
                }
            }
        }

        if (bestDriver == nullptr) {
            return false; // No available driver
        }

        bestDriver->available = false;
        rider.isRiding = true;
        activeRides.push_back({rider, *bestDriver}); // ✅ Add ride to active rides

        vector<int> route = cityGraph->shortestPath(rider.location, destination);
        cout << "🚖 Ride assigned to Driver " << bestDriver->name << " (ID: " << bestDriver->id << ").\n";
        cout << "🛣 Route: ";
        for (int loc : route) {
            cout << loc << " ";
        }
        cout << endl;

        return true;
    }

    void endRide(int driverId) {
        for (auto it = activeRides.begin(); it != activeRides.end(); ++it) {
            if (it->second.id == driverId) {
                cout << "✅ Ride with Driver " << it->second.name << " (ID: " << it->second.id << ") has ended.\n";
                it->second.available = true;
                activeRides.erase(it); // ✅ Remove ride from active rides
                return;
            }
        }
        cout << "⚠ No active ride found with this Driver ID.\n";
    }

    // ✅ Get active rides (read-only)
    const vector<pair<Rider, Driver>>& getActiveRides() const {
        return activeRides;
    }

    // ✅ Check if there are active rides
    bool hasActiveRides() const {
        return !activeRides.empty();
    }
};

#endif
