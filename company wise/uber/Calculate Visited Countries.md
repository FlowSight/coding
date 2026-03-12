Uba is introducing a new flight service between n countries with n-1 flight routes connecting them. All flights are bi-directional. The flight network forms a tree. Each country is either classified as Open or Restricted based on their current Covid-19 situation. Uber flights can freely visit any open country but are not allowed to land in or fly from restricted countries. However, it can obtain special permission to convert some restricted to open countries. Due to a hardware malfunction, it can only convert the countries in pairs. Requesting more permissions than the number of restricted countries results in an error. For each country, determine the maximum number of countries that can be visited by Uber flights originating from that country, assuming optimal conversion of restricted to open. Each country obtains special permissions independently. Return the sum of the countries a flight can visit from each country.

Constraints: n <= 50005

Example
Input
n = 7
s = "ROROROO"
a = [1, 1, 3, 3, 5, 5]
Output
33