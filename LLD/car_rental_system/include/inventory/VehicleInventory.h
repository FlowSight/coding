#pragma once
#include <map>
#include "IVehicleInventory.h"

namespace CarRental {

// Concrete implementation - Single Responsibility: Manages vehicle inventory only
class VehicleInventory : public IVehicleInventory {
private:
    std::map<std::string, Vehicle*> vehicles;

public:
    void addVehicle(Vehicle* vehicle) override {
        vehicles[vehicle->id] = vehicle;
    }
    
    Vehicle* getVehicle(const std::string& vehicleId) override {
        auto it = vehicles.find(vehicleId);
        return (it != vehicles.end()) ? it->second : nullptr;
    }
    
    std::vector<Vehicle*> findByLocation(const std::string& locationId) override {
        std::vector<Vehicle*> result;
        for (auto& entry : vehicles) {
            if (entry.second->locationId == locationId) {
                result.push_back(entry.second);
            }
        }
        return result;
    }
    
    std::vector<Vehicle*> findByType(VehicleType type) override {
        std::vector<Vehicle*> result;
        for (auto& entry : vehicles) {
            if (entry.second->type == type) {
                result.push_back(entry.second);
            }
        }
        return result;
    }
    
    std::vector<Vehicle*> findByLocationAndType(const std::string& locationId, 
                                                VehicleType type) override {
        std::vector<Vehicle*> result;
        for (auto& entry : vehicles) {
            Vehicle* v = entry.second;
            if (v->locationId == locationId && v->type == type) {
                result.push_back(v);
            }
        }
        return result;
    }
    
    ~VehicleInventory() {
        for (auto& v : vehicles) delete v.second;
    }
};

} // namespace CarRental
