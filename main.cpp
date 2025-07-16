#include <iostream>
#include "Graph.h"
#include "RideMatching.h"
#include "Rider.h"

using namespace std;

int main() {
    Graph cityGraph;
    RideMatching rideSystem(&cityGraph);

    // Adding some locations (edges)
    cityGraph.addEdge(1, 2, 10);
    cityGraph.addEdge(2, 3, 15);
    cityGraph.addEdge(3, 4, 20);
    cityGraph.addEdge(4, 5, 25);
    cityGraph.addEdge(1, 5, 30);

    // Adding drivers
    rideSystem.addDriver(101, "John", 2);
    rideSystem.addDriver(102, "Mike", 3);
    rideSystem.addDriver(103, "Sarah", 5);

    while (true) {
        cout << "\nAvailable Locations:";
        cout << "\n1. Airport\n2. Railway Station\n3. City Mall\n4. Tech Park\n5. Bus Stand\n";

        int choice;
        cout << "\n1. Start New Ride\n2. End a Ride\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int start, destination;
            cout << "Enter the number for your Start Location: ";
            cin >> start;
            cout << "Enter the number for your Destination: ";
            cin >> destination;

            Rider rider(201, "Alice", start);
            if (!rideSystem.assignRide(rider, destination)) {
                cout << "⚠ No available drivers. Try again later.\n";
            }
        } else if (choice == 2) {
            if (!rideSystem.hasActiveRides()) { // ✅ Use method instead of accessing private variable
                cout << "⚠ No active rides to complete.\n";
            } else {
                cout << "Ongoing Rides:\n";
                for (const auto& ride : rideSystem.getActiveRides()) { // ✅ Use getter function
                    cout << "Driver: " << ride.second.name << " (ID: " << ride.second.id << "), "
                         << "Rider: " << ride.first.name << " (ID: " << ride.first.id << ")\n";
                }

                int driverId;
                cout << "Enter the Driver ID of the completed ride: ";
                cin >> driverId;
                rideSystem.endRide(driverId);
            }
        } else if (choice == 3) {
            cout << "🚗 Exiting the Ride Sharing System.\n";
            break;
        } else {
            cout << "⚠ Invalid choice, try again.\n";
        }
    }

    return 0;
}
