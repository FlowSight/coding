
// im not sure if below algo is correct
// sort listings with availability date
// start from start of user stay : helper(start,listings,end,cap,numswitch, totalcost)
// if(start>end) return;
// if(start == end) {
//     if(totalcost > anscost) return;
//     if((totalcost < anscost) || (numswitch < ansswitch)) anscost = totalcost
// }
// if(dp[start] != -1) return;
//     pick any listing covering that day 
//     ans = min(ans,prices[it][start] + helper(nextday,listings,st,end,cap,numswitch+ isswitch(),totalcost+prices[it][start]))
//     return dp[i] = ans;

// You're building Airbnb's innovative Split Stay feature, which allows guests to book their trip across multiple listings
// when a single property isn't available for their entire stay.
// Given:
// A list of available listings, each with availability windows and nightly rates
// A guest's desired check-in date, check-out date, and party size
// Write an algorithm that finds the optimal combination of listings to cover the guest's entire stay while minimizing total
// cost.
// Rules:
// 1. The guest's stay must be fully covered with no gaps
// 2. Each listing can only be used once per booking
// 3. Listings must accommodate the party size
// 4. Transitions between listings can only happen at midnight (no same-day switches)
// 5. If multiple optimal solutions exist, prefer fewer transitions (fewer listings)
// Input Format:
// check_in : Start date (string, "YYYY-MM-DD")
// check_out : End date (string, "YYYY-MM-DD")
// party_size : Number of guests (integer)
// listings : Array of listing objects with:
// id : Listing identifier (string)
// capacity : Max guests (integer)
// available_from : Start of availability (string, "YYYY-MM-DD")
// available_to : End of availability (string, "YYYY-MM-DD")
// nightly_rate : Cost per night (float)
// Return an array of booking segments, each containing:
// listing_id : The listing to book
// start_date : Check-in for this segment
// end_date : Check-out for this segment
// cost : Total cost for this segment
// Return an empty array if no valid split-stay combination exists.
// Example 1:
// Input: check_in = "2024-06-01" check_out = "2024-06-10" party_size = 2 
//listings = [ 
// {"id": "A", "capacity": 4, "available_from": "2024-06-01", "available_to": "2024-06-05", "nightly_rate": 100},
// {"id": "B", "capacity": 2, "available_from": "2024-06-05", "available_to": "2024-06-10", "nightly_rate": 120} ]
// Output: [ {"listing_id": "A", "start_date": "2024-06-01", "end_date": "2024-06-05", "cost":
// 400}, {"listing_id": "B", "start_date": "2024-06-05", "end_date": "2024-06-10", "cost": 600}
// ]
// Explanation: The guest stays at listing A for 4 nights ($400), then transfers to listing B
// for 5 nights ($600). Total: $1000.
// Example 2:
// Input: check_in = "2024-07-01" check_out = "2024-07-05" party_size = 3 listings = [ {"id":
// "X", "capacity": 2, "available_from": "2024-07-01", "available_to": "2024-07-05",
// "nightly_rate": 80} ]
// Output: []
// Explanation: Listing X cannot accommodate 3 guests (capacity is 2). No valid split-stay
// exists.
// Constraints
// • 1 ≤ party_size ≤ 16
// • 1 ≤ len(listings) ≤ 100
// • Check-out must be after check-in
// • Maximum stay duration: 30 nights
// • 0 < nightly_rate ≤ 10000