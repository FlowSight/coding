// github-copilot-disable
// copilot disable-file

// vehicles are there of diff types 
// user can book them. 
// user can search if car is available for a day (type,date,duration)
// user can return a car 


// vehicle -> car, sedan, suv, 
// carrentalservice (router)
//     for search : to SearchService
//     for booking : to BookingService

// VehicleInventory (vehicle crud)
// Bookinginventory(booking crud)

enum CARTYPE {
    SEDAN , SUV,HATCHBACK
};

enum BookingType {
    AVAILABLE,Booked,Servicing,UnProvisioned
};

class CarRentalService {

}



int main() {
    CarRentalSystem system;
}