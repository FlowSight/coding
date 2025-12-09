#pragma once
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

// Simple date class
class Date {
public:
    int year, month, day;
    
    Date() : year(2025), month(1), day(1) {}
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    bool operator<=(const Date& other) const {
        return *this < other || *this == other;
    }
    
    bool operator>(const Date& other) const {
        return other < *this;
    }
    
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
};

// Enums
enum VehicleType { SEDAN, SUV, TRUCK };
enum BookingStatus { PENDING, CONFIRMED, CANCELLED };

// Location
class Location {
public:
    string id;
    string name;
    string city;
    
    Location(string id, string name, string city) 
        : id(id), name(name), city(city) {}
};

// Vehicle
class Vehicle {
public:
    string id;
    string model;
    VehicleType type;
    string locationId;
    bool available;
    double pricePerDay;
    
    Vehicle(string id, string model, VehicleType type, string locationId, double price)
        : id(id), model(model), type(type), locationId(locationId), 
          available(true), pricePerDay(price) {}
};

// User
class User {
public:
    string id;
    string name;
    string email;
    
    User(string id, string name, string email)
        : id(id), name(name), email(email) {}
};

// Booking
class Booking {
public:
    string id;
    string userId;
    string vehicleId;
    Date startDate;
    Date endDate;
    BookingStatus status;
    double totalPrice;
    
    Booking(string id, string userId, string vehicleId, Date start, Date end, double price)
        : id(id), userId(userId), vehicleId(vehicleId), 
          startDate(start), endDate(end), status(PENDING), totalPrice(price) {}
};

// Main Rental System
class CarRentalSystem {
private:
    map<string, Vehicle*> vehicles;
    map<string, User*> users;
    map<string, Location*> locations;
    map<string, Booking*> bookings;
    int bookingCounter = 0;
    
    bool hasConflict(string vehicleId, Date start, Date end) {
        for (auto& entry : bookings) {
            Booking* b = entry.second;
            if (b->vehicleId == vehicleId && b->status != CANCELLED) {
                // Check date overlap
                if (!(end < b->startDate || start > b->endDate)) {
                    return true;
                }
            }
        }
        return false;
    }
    
public:
    // Add entities
    void addLocation(Location* loc) { locations[loc->id] = loc; }
    void addVehicle(Vehicle* v) { vehicles[v->id] = v; }
    void addUser(User* u) { users[u->id] = u; }
    
    // Search available vehicles
    vector<Vehicle*> searchVehicles(string locationId, VehicleType type, Date start, Date end) {
        vector<Vehicle*> result;
        for (auto& entry : vehicles) {
            Vehicle* v = entry.second;
            if (v->locationId == locationId && v->type == type && v->available) {
                if (!hasConflict(v->id, start, end)) {
                    result.push_back(v);
                }
            }
        }
        return result;
    }
    
    // Book a vehicle
    Booking* bookVehicle(string userId, string vehicleId, Date start, Date end) {
        if (hasConflict(vehicleId, start, end)) {
            return nullptr; // Conflict exists
        }
        
        Vehicle* v = vehicles[vehicleId];
        int days = 1; // Simplified calculation
        double price = v->pricePerDay * days;
        
        string bookingId = "B" + to_string(++bookingCounter);
        Booking* booking = new Booking(bookingId, userId, vehicleId, start, end, price);
        booking->status = CONFIRMED;
        bookings[bookingId] = booking;
        
        return booking;
    }
    
    // Cancel booking
    bool cancelBooking(string bookingId) {
        if (bookings.find(bookingId) != bookings.end()) {
            bookings[bookingId]->status = CANCELLED;
            return true;
        }
        return false;
    }
    
    // Get user bookings
    vector<Booking*> getUserBookings(string userId) {
        vector<Booking*> result;
        for (auto& entry : bookings) {
            if (entry.second->userId == userId) {
                result.push_back(entry.second);
            }
        }
        return result;
    }
    
    ~CarRentalSystem() {
        for (auto& v : vehicles) delete v.second;
        for (auto& u : users) delete u.second;
        for (auto& l : locations) delete l.second;
        for (auto& b : bookings) delete b.second;
    }
};
