#include <iostream>
#include "include/CarRentalSystem.h"

using namespace std;
using namespace CarRental;

int main() {
    CarRentalSystem system;
    
    // Setup locations
    Location* loc1 = new Location("L1", "Downtown", "SF");
    Location* loc2 = new Location("L2", "Airport", "SF");
    system.addLocation(loc1);
    system.addLocation(loc2);
    
    // Add vehicles
    Vehicle* v1 = new Vehicle("V1", "Tesla Model 3", SEDAN, "L1", 100.0);
    Vehicle* v2 = new Vehicle("V2", "Toyota RAV4", SUV, "L1", 80.0);
    Vehicle* v3 = new Vehicle("V3", "Ford F150", TRUCK, "L2", 120.0);
    system.addVehicle(v1);
    system.addVehicle(v2);
    system.addVehicle(v3);
    
    // Add user
    User* user1 = new User("U1", "John Doe", "john@example.com");
    system.addUser(user1);
    
    // Search for vehicles
    cout << "=== Searching for SUVs at Downtown ===" << endl;
    Date start(2025, 11, 1);
    Date end(2025, 11, 5);
    vector<Vehicle*> available = system.searchVehicles("L1", SUV, start, end);
    
    for (Vehicle* v : available) {
        cout << "Found: " << v->model << " - $" << v->pricePerDay << "/day" << endl;
    }
    
    // Book a vehicle
    cout << "\n=== Booking Toyota RAV4 ===" << endl;
    Booking* booking = system.bookVehicle("U1", "V2", start, end);
    if (booking) {
        cout << "Booking confirmed! ID: " << booking->id 
             << ", Total: $" << booking->totalPrice << endl;
    }
    
    // Try to book same vehicle (should fail)
    cout << "\n=== Trying double booking ===" << endl;
    Booking* booking2 = system.bookVehicle("U1", "V2", start, end);
    if (!booking2) {
        cout << "Booking failed - vehicle not available!" << endl;
    }
    
    // View user bookings
    cout << "\n=== User Bookings ===" << endl;
    vector<Booking*> userBookings = system.getUserBookings("U1");
    for (Booking* b : userBookings) {
        cout << "Booking " << b->id << ": Vehicle " << b->vehicleId 
             << " - Status: " << (b->status == CONFIRMED ? "CONFIRMED" : "CANCELLED") << endl;
    }
    
    // Cancel booking
    cout << "\n=== Cancelling Booking ===" << endl;
    if (system.cancelBooking(booking->id)) {
        cout << "Booking cancelled successfully!" << endl;
    }
    
    return 0;
}
