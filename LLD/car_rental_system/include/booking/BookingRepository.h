#pragma once
#include <map>
#include "IBookingRepository.h"

namespace CarRental {

// Single Responsibility: Manages bookings only
class BookingRepository : public IBookingRepository {
private:
    std::map<std::string, Booking*> bookings;

public:
    void addBooking(Booking* booking) override {
        bookings[booking->id] = booking;
    }
    
    Booking* getBooking(const std::string& bookingId) override {
        auto it = bookings.find(bookingId);
        return (it != bookings.end()) ? it->second : nullptr;
    }
    
    std::vector<Booking*> getBookingsByUser(const std::string& userId) override {
        std::vector<Booking*> result;
        for (auto& entry : bookings) {
            if (entry.second->userId == userId) {
                result.push_back(entry.second);
            }
        }
        return result;
    }
    
    std::vector<Booking*> getBookingsByVehicle(const std::string& vehicleId) override {
        std::vector<Booking*> result;
        for (auto& entry : bookings) {
            if (entry.second->vehicleId == vehicleId) {
                result.push_back(entry.second);
            }
        }
        return result;
    }
    
    bool hasConflict(const std::string& vehicleId, const Date& start, const Date& end) override {
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
    
    ~BookingRepository() {
        for (auto& b : bookings) delete b.second;
    }
};

} // namespace CarRental
