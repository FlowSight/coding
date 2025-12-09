#pragma once
#include <map>
#include "inventory/VehicleInventory.h"
#include "booking/BookingRepository.h"
#include "services/SearchService.h"
#include "services/BookingService.h"
#include "models/User.h"
#include "models/Location.h"

namespace CarRental {

// Facade Pattern: Coordinates between different subsystems
// This is a high-level coordinator that delegates to specialized classes
class CarRentalSystem {
private:
    // Repositories (Data layer)
    VehicleInventory* vehicleInventory;
    BookingRepository* bookingRepository;
    
    // Services (Business logic layer)
    SearchService* searchService;
    BookingService* bookingService;
    
    // Simple storage for users and locations
    std::map<std::string, User*> users;
    std::map<std::string, Location*> locations;

public:
    CarRentalSystem() {
        // Initialize repositories
        vehicleInventory = new VehicleInventory();
        bookingRepository = new BookingRepository();
        
        // Initialize services with dependencies (Dependency Injection)
        searchService = new SearchService(vehicleInventory, bookingRepository);
        bookingService = new BookingService(bookingRepository, vehicleInventory);
    }
    
    // Delegates to appropriate subsystems
    void addLocation(Location* loc) { 
        locations[loc->id] = loc; 
    }
    
    void addVehicle(Vehicle* v) { 
        vehicleInventory->addVehicle(v); 
    }
    
    void addUser(User* u) { 
        users[u->id] = u; 
    }
    
    std::vector<Vehicle*> searchVehicles(const std::string& locationId, 
                                        VehicleType type,
                                        const Date& startDate, 
                                        const Date& endDate) {
        return searchService->searchAvailableVehicles(locationId, type, startDate, endDate);
    }
    
    Booking* bookVehicle(const std::string& userId, 
                        const std::string& vehicleId,
                        const Date& startDate, 
                        const Date& endDate) {
        return bookingService->createBooking(userId, vehicleId, startDate, endDate);
    }
    
    bool cancelBooking(const std::string& bookingId) {
        return bookingService->cancelBooking(bookingId);
    }
    
    std::vector<Booking*> getUserBookings(const std::string& userId) {
        return bookingService->getUserBookings(userId);
    }
    
    ~CarRentalSystem() {
        delete vehicleInventory;
        delete bookingRepository;
        delete searchService;
        delete bookingService;
        
        for (auto& u : users) delete u.second;
        for (auto& l : locations) delete l.second;
    }
};

} // namespace CarRental
