#pragma once
#include <string>

namespace CarRental {

class User {
public:
    std::string id;
    std::string name;
    std::string email;
    
    User(std::string id, std::string name, std::string email)
        : id(id), name(name), email(email) {}
};

} // namespace CarRental
