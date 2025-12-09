#pragma once
#include <string>

namespace CarRental {

class Location {
public:
    std::string id;
    std::string name;
    std::string city;
    
    Location(std::string id, std::string name, std::string city) 
        : id(id), name(name), city(city) {}
};

} // namespace CarRental
