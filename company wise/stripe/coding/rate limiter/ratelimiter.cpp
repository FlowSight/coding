// Design a rate limiter system that begins with a specified capacity (limit) indicating the maximum number of requests allowed within a certain time interval (ttl, unit: Millisecond). When a new request arrives, return true if it is accepted under the current limit. Otherwise, return false.

// Implement the RateLimiter class:

// RateLimiter(int ttl, int limit) Initializes the rate limiter with a time-to-live window ttl in milliseconds and a maximum limit for the number of requests allowed in that time frame.

// boolean allowRequest() Checks if a new request can be served based on recent requests within the ttl window.

#include <queue>
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

class RateLimiter {
private:
public:
    RateLimiter(long ttl, long limit) {
        // TODO: Implement RateLimiter constructor logic.
    }

    bool allowRequest() {
        // TODO: Implement allowRequest logic.
    }

    static void test1() {
        std::cout << "========= Test 1 =========" << std::endl;
        RateLimiter rateLimiter(1000, 5);

        // Make 11 requests at a rate faster than the rate limiter allows
        for (int i = 0; i < 11; i++) {
            std::cout << "Request " << (i + 1) << " accepted (t=" << (i * 100) << "ms)? : " << (rateLimiter.allowRequest() ? "true" : "false") << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100 milliseconds between requests
        }
    }

    static void test2() {
        std::cout << "\n========= Test 2 =========" << std::endl;
        RateLimiter rateLimiter(1000, 5);

        // Make 10 requests at a rate slower than the rate limiter allows
        for (int i = 0; i < 10; i++) {
            std::cout << "Request " << (i + 1) << " accepted (t=" << (i * 300) << "ms)? : " << (rateLimiter.allowRequest() ? "true" : "false") << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 300 milliseconds between requests
        }
    }
};

int main() {
    RateLimiter::test1();
    RateLimiter::test2();
    return 0;
}