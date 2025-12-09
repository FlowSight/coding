#pragma once
#include <vector>
#include <string>
#include "../models/Vehicle.h"
#include "../Enums.h"

namespace CarRental {

// Interface for vehicle inventory (DIP - Dependency Inversion)
class IVehicleInventory {
public:
    virtual ~IVehicleInventory() = default;
    
    virtual void addVehicle(Vehicle* vehicle) = 0;
    virtual Vehicle* getVehicle(const std::string& vehicleId) = 0;
    virtual std::vector<Vehicle*> findByLocation(const std::string& locationId) = 0;
    virtual std::vector<Vehicle*> findByType(VehicleType type) = 0;
    virtual std::vector<Vehicle*> findByLocationAndType(const std::string& locationId, 
                                                        VehicleType type) = 0;
};

} // namespace CarRental
