#include "./agent_rating_system.cpp"

using namespace CallCenter;

int main(){
    CallCenterManager manager;
    
    // Add ratings for January 2025
    cout << "Adding ratings for January 2025..." << endl;
    manager.addRating("Alice", 5, 1, 1, 2025);
    manager.addRating("Bob", 4, 2, 1, 2025);
    manager.addRating("Alice", 5, 3, 1, 2025);
    manager.addRating("Charlie", 3, 4, 1, 2025);
    manager.addRating("Bob", 5, 5, 1, 2025);
    
    // Add ratings for February 2025
    cout << "Adding ratings for February 2025..." << endl;
    manager.addRating("Alice", 4, 1, 2, 2025);
    manager.addRating("Bob", 5, 2, 2, 2025);
    manager.addRating("Charlie", 5, 3, 2, 2025);
    manager.addRating("Charlie", 4, 4, 2, 2025);
    manager.addRating("David", 5, 5, 2, 2025);
    
    // Add ratings for March 2025
    cout << "Adding ratings for March 2025..." << endl;
    manager.addRating("Alice", 5, 1, 3, 2025);
    manager.addRating("David", 5, 2, 3, 2025);
    manager.addRating("David", 4, 3, 3, 2025);
    
    // Display overall ranking
    manager.getOverallRanking();
    
    // Display monthly ranking for January
    manager.getMonthlyRanking(1, 2025);
    
    // Display monthly ranking for February
    manager.getMonthlyRanking(2, 2025);
    
    // Display monthly ranking for March
    manager.getMonthlyRanking(3, 2025);
    
    // Display all months ranking
    cout << "\n=== All Months Rankings ===" << endl;
    manager.getAllMonthsRanking();
    
    return 0;
}