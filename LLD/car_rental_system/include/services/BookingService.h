#pragma once
#include <string>
#include "../booking/IBookingRepository.h"
#include "../inventory/IVehicleInventory.h"

namespace CarRental {

// Single Responsibility: Booking business logic
class BookingService {
private:
    IBookingRepository* bookingRepo;
    IVehicleInventory* inventory;
    int bookingCounter;

public:
    BookingService(IBookingRepository* repo, IVehicleInventory* inv)
        : bookingRepo(repo), inventory(inv), bookingCounter(0) {}
    
    Booking* createBooking(const std::string& userId, 
                          const std::string& vehicleId,
                          const Date& startDate,
                          const Date& endDate) {
        // Check for conflicts
        if (bookingRepo->hasConflict(vehicleId, startDate, endDate)) {
            return nullptr;
        }
        
        // Get vehicle and calculate price
        Vehicle* vehicle = inventory->getVehicle(vehicleId);
        if (!vehicle || !vehicle->available) {
            return nullptr;
        }
        
        double price = vehicle->pricePerDay; // Simplified pricing
        
        // Create booking
        std::string bookingId = "B" + std::to_string(++bookingCounter);
        Booking* booking = new Booking(bookingId, userId, vehicleId, startDate, endDate, price);
        booking->status = CONFIRMED;
        
        bookingRepo->addBooking(booking);
        return booking;
    }
    
    bool cancelBooking(const std::string& bookingId) {
        Booking* booking = bookingRepo->getBooking(bookingId);
        if (booking) {
            booking->status = CANCELLED;
            return true;
        }
        return false;
    }
    
    std::vector<Booking*> getUserBookings(const std::string& userId) {
        return bookingRepo->getBookingsByUser(userId);
    }
};

} // namespace CarRental
