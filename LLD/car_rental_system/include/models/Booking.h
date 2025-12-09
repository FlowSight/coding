#pragma once
#include <string>
#include "../Date.h"
#include "../Enums.h"

namespace CarRental {

class Booking {
public:
    std::string id;
    std::string userId;
    std::string vehicleId;
    Date startDate;
    Date endDate;
    BookingStatus status;
    double totalPrice;
    
    Booking(std::string id, std::string userId, std::string vehicleId, 
            Date start, Date end, double price)
        : id(id), userId(userId), vehicleId(vehicleId), 
          startDate(start), endDate(end), status(PENDING), totalPrice(price) {}
};

} // namespace CarRental
