// Low level design code for api rate limiter
// 1. getReqRemaining()
// 2. canAccept()
// 3. accept()
// 4. extensible based on method of rate limiting
// 5. credit based model,.reqs not used in curr slot, will be transferred as credit in next slot
// 6. multithreaded

#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>
#include <ctime>

using namespace std;

// ============= REQUIREMENT 1: Basic Rate Limiter =============

class RateLimiter {
private:
    struct ClientData {
        deque<int> timestamps;  // stores request timestamps
        int limit;              // max requests allowed in window
        int windowSize;         // time window in seconds
        
        ClientData(int lim, int window) : limit(lim), windowSize(window) {}
    };
    
    unordered_map<string, ClientData> clients;
    int defaultLimit;
    int defaultWindow;
    
    int getCurrentTime() {
        return time(nullptr);
    }
    
    void removeExpiredRequests(ClientData& data) {
        int currentTime = getCurrentTime();
        int cutoffTime = currentTime - data.windowSize;
        
        while (!data.timestamps.empty() && data.timestamps.front() < cutoffTime) {
            data.timestamps.pop_front();
        }
    }
    
    ClientData& getClientData(const string& clientId) {
        if (clients.find(clientId) == clients.end()) {
            clients.emplace(clientId, ClientData(defaultLimit, defaultWindow));
        }
        return clients[clientId];
    }
    
public:
    RateLimiter(int limit, int windowSizeSeconds) 
        : defaultLimit(limit), defaultWindow(windowSizeSeconds) {}
    
    // Returns remaining requests for client
    int getReqRemaining(const string& clientId) {
        ClientData& data = getClientData(clientId);
        removeExpiredRequests(data);
        return data.limit - data.timestamps.size();
    }
    
    // Check if request can be accepted
    bool canAccept(const string& clientId) {
        ClientData& data = getClientData(clientId);
        removeExpiredRequests(data);
        return data.timestamps.size() < data.limit;
    }
    
    // Accept a request (throws if limit exceeded)
    void accept(const string& clientId) {
        ClientData& data = getClientData(clientId);
        removeExpiredRequests(data);
        
        if (data.timestamps.size() >= data.limit) {
            throw runtime_error("Rate limit exceeded for client: " + clientId);
        }
        
        data.timestamps.push_back(getCurrentTime());
    }
};

// ============= DEMO =============

int main() {
    cout << "=== Requirement 1: Basic Rate Limiter ===" << endl;
    
    // Create rate limiter: 5 requests per 10 seconds
    RateLimiter limiter(5, 10);
    
    string client1 = "user123";
    
    cout << "\nInitial remaining requests: " << limiter.getReqRemaining(client1) << endl;
    
    // Simulate API requests
    cout << "\nMaking requests..." << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Request " << (i+1) << ": ";
        if (limiter.canAccept(client1)) {
            limiter.accept(client1);
            cout << "Accepted. Remaining: " << limiter.getReqRemaining(client1) << endl;
        } else {
            cout << "Rejected! Remaining: " << limiter.getReqRemaining(client1) << endl;
        }
    }
    
    // Test exception handling
    cout << "\nTesting exception..." << endl;
    try {
        limiter.accept(client1);
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    
    // Multiple clients
    cout << "\nTesting multiple clients..." << endl;
    string client2 = "user456";
    cout << "Client1 remaining: " << limiter.getReqRemaining(client1) << endl;
    cout << "Client2 remaining: " << limiter.getReqRemaining(client2) << endl;
    
    return 0;
}