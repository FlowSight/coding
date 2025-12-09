#pragma once
#include <vector>
#include "../inventory/IVehicleInventory.h"
#include "../booking/IBookingRepository.h"

namespace CarRental {

// Single Responsibility: Search logic only
class SearchService {
private:
    IVehicleInventory* inventory;
    IBookingRepository* bookingRepo;

public:
    SearchService(IVehicleInventory* inv, IBookingRepository* repo)
        : inventory(inv), bookingRepo(repo) {}
    
    std::vector<Vehicle*> searchAvailableVehicles(const std::string& locationId,
                                                   VehicleType type,
                                                   const Date& startDate,
                                                   const Date& endDate) {
        std::vector<Vehicle*> candidates = inventory->findByLocationAndType(locationId, type);
        std::vector<Vehicle*> available;
        
        for (Vehicle* v : candidates) {
            if (v->available && !bookingRepo->hasConflict(v->id, startDate, endDate)) {
                available.push_back(v);
            }
        }
        return available;
    }
};

} // namespace CarRental
