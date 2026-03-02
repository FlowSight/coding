Given a list of flight information where each entry includes the start city, destination city, and corresponding ticket price, along with a maximum allowed number of transfers, find the minimum fare itinerary from a specified start point to a destination. The output should include the minimum ticket price and the specific travel route. For example, given the flight information: [London -> Japan, 500] [Japan -> Beijing, 100] [London -> Beijing, 1000], if a maximum of one transfer is allowed, the optimal route is: London -> Japan -> Beijing, with a total cost of 600. If no transfers are allowed, the optimal route is London -> Beijing, with a total cost of 1000.

Example
Input
n = 3
flights = [(0, 1, 100), (1, 2, 100), (0, 2, 500)]
src = 0
dst = 2
K = 1