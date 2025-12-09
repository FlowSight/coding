# Car Rental System - Low Level Design

## Overview
Minimal LLD for car rental system - interview ready, can be coded in 30 minutes.

## Design Highlights
- **Single header file** (`car_rental.h`) with all classes
- **Core classes**: User, Vehicle, Location, Booking, Date
- **Main system**: CarRentalSystem with search, book, cancel operations
- **SOLID principles**: Single Responsibility (each class has one purpose)
- **No fancy pointers**: Simple raw pointers for interview speed
- **Conflict detection**: Prevents double bookings

## Key Operations
1. `searchVehicles()` - Find available vehicles by location, type, and dates
2. `bookVehicle()` - Create booking with conflict checking
3. `cancelBooking()` - Cancel existing reservation
4. `getUserBookings()` - Get user's booking history

## Build & Run
```bash
g++ -std=c++11 main.cpp -o car_rental
./car_rental
```

## Sample Output
```
=== Searching for SUVs at Downtown ===
Found: Toyota RAV4 - $80/day

=== Booking Toyota RAV4 ===
Booking confirmed! ID: B1, Total: $80

=== Trying double booking ===
Booking failed - vehicle not available!

=== User Bookings ===
Booking B1: Vehicle V2 - Status: CONFIRMED

=== Cancelling Booking ===
Booking cancelled successfully!
```
