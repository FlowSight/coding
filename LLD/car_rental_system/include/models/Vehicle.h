#pragma once
#include <string>
#include "../Enums.h"

namespace CarRental {

class Vehicle {
public:
    std::string id;
    std::string model;
    VehicleType type;
    std::string locationId;
    bool available;
    double pricePerDay;
    
    Vehicle(std::string id, std::string model, VehicleType type, 
            std::string locationId, double price)
        : id(id), model(model), type(type), locationId(locationId), 
          available(true), pricePerDay(price) {}
};

} // namespace CarRental
