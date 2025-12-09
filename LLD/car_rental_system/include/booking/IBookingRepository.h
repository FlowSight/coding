#pragma once
#include <vector>
#include <string>
#include "../models/Booking.h"

namespace CarRental {

// Interface for booking repository (DIP)
class IBookingRepository {
public:
    virtual ~IBookingRepository() = default;
    
    virtual void addBooking(Booking* booking) = 0;
    virtual Booking* getBooking(const std::string& bookingId) = 0;
    virtual std::vector<Booking*> getBookingsByUser(const std::string& userId) = 0;
    virtual std::vector<Booking*> getBookingsByVehicle(const std::string& vehicleId) = 0;
    virtual bool hasConflict(const std::string& vehicleId, const Date& start, const Date& end) = 0;
};

} // namespace CarRental
