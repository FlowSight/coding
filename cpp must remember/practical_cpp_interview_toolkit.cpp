// ============================================================
// PRACTICAL C++ INTERVIEW TOOLKIT
// Beyond leetcode — systems/practical patterns for Stripe-style interviews
// ============================================================

#include <bits/stdc++.h>  // use in interviews to avoid missing-include traps
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <nlohmann/json.hpp>  // brew install nlohmann-json
// #include <curl/curl.h>        // brew install curl

using namespace std;

namespace DateTimeExamples {

    // Build a time_t from human-readable components
    time_t makeTime(int yy, int mon, int dd, int hh = 0, int mm = 0, int ss = 0) {
        tm t = {};              // ALWAYS zero-init with {} to avoid garbage
        t.tm_year = yy - 1900;  // years since 1900
        t.tm_mon  = mon - 1;    // 0-based month
        t.tm_mday = dd;
        t.tm_hour = hh;
        t.tm_min  = mm;
        t.tm_sec  = ss;
        return mktime(&t);      // normalizes and converts to epoch seconds
    }

    // Next day: just add 86400 seconds
    time_t nextDay(time_t t) { return t + 86400; }

    // Compare dates: just use < > == on the integer
    // NO custom comparator bugs possible

    // Format to string
    string formatDate(time_t t) {
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
        return string(buf);
    }

    // Difference in days
    int daysBetween(time_t a, time_t b) {
        return (int)difftime(b, a) / 86400;
    }

    void demo() {
        cout << "=== DATE/TIME ===" << endl;
        time_t start = makeTime(2025, 4, 7);
        time_t end   = makeTime(2025, 4, 13, 11, 59, 59);

        cout << "Days between: " << daysBetween(start, end) << endl;

        // Iterate dates in range
        for (time_t t = start; t <= end; t = nextDay(t)) {
            cout << formatDate(t) << endl;
        }
    }
}

// ============================================================
// 2. CSV / FILE PARSING — fstream + istringstream
// ============================================================
namespace CSVExamples {

    // Read CSV file
    void readCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) { cerr << "Cannot open " << filename << endl; return; }

        string line;
        getline(file, line);  // skip header

        while (getline(file, line)) {
            istringstream ss(line);
            string id, amount, date;
            getline(ss, id, ',');
            getline(ss, amount, ',');
            getline(ss, date, ',');
            cout << "ID: " << id << " Amount: " << amount << " Date: " << date << endl;
        }
    }

    // Write CSV file
    void writeCSV(const string& filename) {
        ofstream out(filename);
        out << "id,amount,date\n";
        out << "txn_1,100.50,2025-04-07\n";
        out << "txn_2,200.00,2025-04-08\n";
    }

    // Parse a single CSV line (handles in-memory strings too)
    vector<string> splitCSV(const string& line, char delim = ',') {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    void demo() {
        cout << "\n=== CSV PARSING ===" << endl;
        string line = "txn_123,99.50,2025-04-07,alice";
        auto fields = splitCSV(line);
        for (auto& f : fields) cout << "[" << f << "] ";
        cout << endl;
    }
}

// ============================================================
// 3. STRING <-> NUMBER CONVERSION
// ============================================================
namespace ConversionExamples {

    void demo() {
        cout << "\n=== CONVERSIONS ===" << endl;

        // String to number
        int port = stoi("8080");
        long big = stol("9999999999");
        double amount = stod("99.50");

        // Number to string
        string s = to_string(42);
        string d = to_string(3.14);

        // Formatted string (C-style, always available)
        char buf[64];
        snprintf(buf, sizeof(buf), "$%.2f", 99.5);  // "$99.50"
        cout << buf << endl;

        // Hex conversion
        int val = stoi("FF", nullptr, 16);  // 255
        cout << "Hex FF = " << val << endl;
    }
}

// ============================================================
// 4. JSON (nlohmann/json) — brew install nlohmann-json
// ============================================================
/*
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace JSONExamples {
    void demo() {
        // Create
        json config = {
            {"ttl_ms", 1000},
            {"limit", 5},
            {"users", {
                {"alice", {{"limit", 5}, {"window", 10}}},
                {"bob",   {{"limit", 3}, {"window", 5}}}
            }}
        };

        // Pretty print
        cout << config.dump(2) << endl;

        // Access
        int limit = config["limit"];

        // Parse from string
        string raw = R"({"user":"alice","amount":99.5})";
        json parsed = json::parse(raw);

        // Check & access safely
        if (parsed.contains("user") && parsed["user"].is_string()) {
            string user = parsed["user"];
        }

        // Iterate object
        for (auto& [key, val] : config["users"].items()) {
            cout << key << " -> " << val.dump() << endl;
        }

        // O(1) lookup (object keys, not array scan)
        if (config["users"].contains("alice")) {
            cout << config["users"]["alice"]["limit"] << endl;
        }

        // GOTCHA: brace rules
        // {"a", "b"}             -> array ["a","b"]
        // {{"a", "b"}}           -> object {"a":"b"}
        // {"a", {{"k",1}}}       -> array ["a", {"k":1}]
        // {{"a", {{"k",1}}}}     -> object {"a": {"k":1}}
    }
}
*/

// ============================================================
// 5. CHRONO — measuring time, timeouts, rate limiting
// ============================================================
namespace ChronoExamples {

    void demo() {
        cout << "\n=== CHRONO ===" << endl;

        // Measure elapsed time
        auto t1 = chrono::steady_clock::now();
        this_thread::sleep_for(chrono::milliseconds(50));
        auto t2 = chrono::steady_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
        cout << "Elapsed: " << ms << "ms" << endl;

        // Current time as epoch milliseconds (useful for rate limiters)
        auto now = chrono::system_clock::now();
        long long epoch_ms = chrono::duration_cast<chrono::milliseconds>(
            now.time_since_epoch()).count();
        cout << "Epoch ms: " << epoch_ms << endl;

        // Sleep
        this_thread::sleep_for(chrono::milliseconds(100));
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// ============================================================
// 6. REGEX — pattern matching for logs, validation
// ============================================================
namespace RegexExamples {

    void demo() {
        cout << "\n=== REGEX ===" << endl;

        // Match a date pattern
        regex datePattern(R"((\d{4})-(\d{2})-(\d{2}))");
        string line = "Transaction on 2025-04-07 for $99.50";
        smatch match;
        if (regex_search(line, match, datePattern)) {
            cout << "Year: " << match[1] << " Month: " << match[2] << " Day: " << match[3] << endl;
        }

        // Validate email-like pattern
        regex emailPattern(R"(\w+@\w+\.\w+)");
        cout << "Valid: " << regex_match(string("alice@stripe.com"), emailPattern) << endl;

        // Replace
        string cleaned = regex_replace(line, regex(R"(\$)"), "USD ");
        cout << cleaned << endl;

        // Split by regex (iterate matches)
        regex wordPattern(R"(\w+)");
        sregex_iterator it(line.begin(), line.end(), wordPattern), end;
        for (; it != end; ++it) cout << it->str() << " | ";
        cout << endl;
    }
}

// ============================================================
// 7. THREADING — mutex, condition_variable, atomic
// ============================================================
namespace ThreadExamples {

    // Thread-safe queue (producer-consumer)
    template<typename T>
    class ThreadSafeQueue {
        queue<T> q;
        mutex mtx;
        condition_variable cv;
    public:
        void push(T val) {
            { lock_guard<mutex> lk(mtx); q.push(move(val)); }
            cv.notify_one();
        }
        T pop() {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [&]{ return !q.empty(); });
            T val = move(q.front()); q.pop();
            return val;
        }
        bool empty() {
            lock_guard<mutex> lk(mtx);
            return q.empty();
        }
    };

    // Atomic counter (lock-free)
    void atomicDemo() {
        atomic<int> counter(0);
        vector<thread> threads;
        for (int i = 0; i < 10; i++) {
            threads.emplace_back([&counter]() {
                for (int j = 0; j < 1000; j++) counter.fetch_add(1);
            });
        }
        for (auto& t : threads) t.join();
        cout << "Counter: " << counter.load() << endl;  // always 10000
    }

    void demo() {
        cout << "\n=== THREADING ===" << endl;
        atomicDemo();
    }
}

// ============================================================
// 8. RANDOM — sampling, jitter, ID generation
// ============================================================
namespace RandomExamples {

    // Random number in range
    int randInt(int lo, int hi) {
        static mt19937 rng(random_device{}());
        return uniform_int_distribution<int>(lo, hi)(rng);
    }

    // Random retry jitter (exponential backoff)
    int retryDelay(int attempt) {
        int base = min(1000 * (1 << attempt), 30000);  // cap at 30s
        return base + randInt(0, base / 2);              // add jitter
    }

    // Simple unique ID generator
    string genId(int len = 16) {
        static mt19937 rng(random_device{}());
        static const char hex[] = "0123456789abcdef";
        string id(len, '0');
        for (auto& c : id) c = hex[uniform_int_distribution<int>(0, 15)(rng)];
        return id;
    }

    // Reservoir sampling — pick k random items from a stream
    vector<int> reservoirSample(vector<int>& stream, int k) {
        vector<int> result(stream.begin(), stream.begin() + k);
        for (int i = k; i < (int)stream.size(); i++) {
            int j = randInt(0, i);
            if (j < k) result[j] = stream[i];
        }
        return result;
    }

    void demo() {
        cout << "\n=== RANDOM ===" << endl;
        cout << "Random 1-100: " << randInt(1, 100) << endl;
        cout << "Retry delay (attempt 3): " << retryDelay(3) << "ms" << endl;
        cout << "Generated ID: " << genId() << endl;
    }
}

// ============================================================
// 9. HASHING — dedup, sharding, consistent hashing
// ============================================================
namespace HashExamples {

    void demo() {
        cout << "\n=== HASHING ===" << endl;

        // Built-in hash
        size_t h = hash<string>{}("payment_123");
        cout << "Hash: " << h << endl;

        // Shard assignment
        int numShards = 4;
        int shard = h % numShards;
        cout << "Shard: " << shard << endl;

        // Hash pair as key (custom hash for unordered_map)
        auto pairHash = [](const pair<int,int>& p) {
            return hash<long long>()(((long long)p.first << 32) | p.second);
        };
        unordered_map<pair<int,int>, string, decltype(pairHash)> m(0, pairHash);
        m[{1, 2}] = "edge_1_2";
    }
}

// ============================================================
// 10. ENV VARS / CONFIG
// ============================================================
namespace EnvExamples {

    void demo() {
        cout << "\n=== ENV VARS ===" << endl;
        const char* home = getenv("HOME");
        if (home) cout << "HOME: " << home << endl;
        else      cout << "HOME not set" << endl;

        // Fallback pattern
        const char* port = getenv("PORT");
        int p = port ? stoi(port) : 8080;
        cout << "Port: " << p << endl;
    }
}

// ============================================================
// 11. PRACTICAL PATTERNS — LRU, sliding window, rate limiter
// ============================================================
namespace PracticalPatterns {

    // LRU Cache — list + unordered_map, O(1) everything
    class LRUCache {
        int cap;
        list<pair<int,int>> order;  // front = most recent
        unordered_map<int, list<pair<int,int>>::iterator> lookup;
    public:
        LRUCache(int capacity) : cap(capacity) {}

        int get(int key) {
            if (lookup.find(key) == lookup.end()) return -1;
            // Move to front
            order.splice(order.begin(), order, lookup[key]);
            return lookup[key]->second;
        }

        void put(int key, int val) {
            if (lookup.count(key)) {
                lookup[key]->second = val;
                order.splice(order.begin(), order, lookup[key]);
                return;
            }
            if ((int)order.size() == cap) {
                lookup.erase(order.back().first);
                order.pop_back();
            }
            order.push_front({key, val});
            lookup[key] = order.begin();
        }
    };

    // Sliding window rate limiter using deque
    class RateLimiter {
        int maxReq;
        long windowMs;
        deque<long> timestamps;
    public:
        RateLimiter(int limit, long windowMs) : maxReq(limit), windowMs(windowMs) {}

        bool allow(long nowMs) {
            while (!timestamps.empty() && timestamps.front() <= nowMs - windowMs)
                timestamps.pop_front();
            if ((int)timestamps.size() < maxReq) {
                timestamps.push_back(nowMs);
                return true;
            }
            return false;
        }
    };
}

// ============================================================
// 12. INTERVIEW SURVIVAL TIPS — DO THIS EVERY TIME
// ============================================================
/*
  ===================== BEFORE YOU START CODING =====================

  T1. INCLUDE EVERYTHING EXPLICITLY. Do NOT rely on transitive includes.
      Either list every header you use, or use the nuclear option:
        #include <bits/stdc++.h>
      Transitive includes vary across compilers. Code that compiles
      on your Mac may fail on HackerRank's GCC. You won't get a
      visible error — just stale output from a previous build.

  T2. CANARY LOG — first line of main(), always:
        cout << "BUILD OK" << endl;
      If you don't see "BUILD OK" in output, your code did NOT compile.
      You are looking at stale output from a previous successful build.
      This is the #1 silent killer on managed platforms like HackerRank.

  T3. USE endl ON EVERY cout. Not '\n', use endl.
      endl forces a flush. Without it, if your program hangs (infinite
      loop, deadlock), buffered output stays invisible — you'll think
      your print didn't execute, but it did. This cost me a Stripe
      interview. Just always use endl.

  ===================== STRUCT / CLASS INIT =====================

  T4. ZERO-INIT ALL STRUCT MEMBERS at declaration:


  T5. ZERO-INIT C STRUCTS with {}:
        tm t = {};     // SAFE — all fields zeroed
      NOT:
        tm t;          // GARBAGE in every field

  ===================== DATE / TIME =====================

  T6. NEVER write your own date comparison or next-day logic.
      Use time_t (epoch seconds). It's a single integer.
        time_t a = makeTime(2025, 4, 7);
        time_t b = makeTime(2025, 4, 13);
        if (a < b) ...         // just works
        a += 86400;            // next day, handles month/year rollover
      Custom field-by-field comparison WILL have bugs under pressure.

  ===================== COMPARISONS =====================

  T7. MULTI-FIELD COMPARISON — always check != before <:
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z <= b.z;
      NEVER:
        if (a.x < b.x) return true;   // BUG: falls through to y
        if (a.y < b.y) return true;   // even when x > b.x
      Or better: use std::tie for comparison:
        return tie(a.x, a.y, a.z) <= tie(b.x, b.y, b.z);

  ===================== NUMBERS =====================

  T8. INTEGER OVERFLOW: use long long for anything that could exceed
      2 billion (~2.1 × 10^9). Sums, products, timestamps, IDs.
        long long sum = 0;  // not int
      stoi() throws on overflow — prefer stol() or stoll().

  T9. FLOATING POINT: never compare with ==.
        if (abs(a - b) < 1e-9) ...   // use epsilon
      For money, use integer cents (long long) to avoid rounding:
        long long amount_cents = 9950;  // $99.50

  ===================== DEBUGGING =====================

  T10. PRINT VARIABLES IMMEDIATELY after assignment to verify:
         cout << "start=" << start << " end=" << end << endl;
       Don't wait until the end to check. Catch garbage early.

  T11. ADD LOOP GUARDS to prevent infinite loops during debugging:
         int safety = 0;
         while (condition && safety++ < 100000) { ... }
       Remove before submission, but it prevents interview-killing hangs.

  T12. IF OUTPUT LOOKS WRONG, suspect stale binary first.
       Change the canary: cout << "BUILD v2" << endl;
       If it still says "BUILD OK", you're running old code.

  ===================== PLATFORM TIPS (HackerRank etc.) =====================

  T13. CHECK COMPILATION OUTPUT — it's a separate tab/panel from
       program output. If compile fails, program output shows the
       LAST successful run, not an error.

  T14. endl vs '\n' PERFORMANCE: yes, endl is slower due to flush.
       In interviews, this NEVER matters. Correctness > performance.
       Use endl everywhere. Optimize only if TLE on output-heavy problems.

  T15. COPY YOUR BOILERPLATE before the interview starts:
       - #include <bits/stdc++.h>
       - using namespace std;
       - canary log
       - makeTime() helper if date problems are expected
       - splitCSV() helper
       Have these ready in a snippet file.
*/

// ============================================================
// QUICK REFERENCE TABLE
// ============================================================
/*
  Problem pattern          | Reach for
  -------------------------|------------------------------------------
  Time windows/scheduling  | time_t + integer math (+ 86400 for days)
  Rate limiting            | deque + chrono epoch ms
  Reconciliation/diff      | set_difference, merge on sorted data
  CSV/log parsing          | ifstream + istringstream + getline
  Top-K / streaming median | priority_queue (min + max heap)
  Range queries/intervals  | map::lower_bound / upper_bound
  Running totals/balances  | partial_sum or prefix sum
  Config/nested data       | nlohmann/json or map<string, variant>
  Retry with backoff       | random jitter + exponential delay
  Unique IDs               | random hex gen or hash-based
  Caching                  | LRU = list + unordered_map
  Thread-safe queue        | mutex + condition_variable + queue
*/

int main() {
    DateTimeExamples::demo();
    CSVExamples::demo();
    ConversionExamples::demo();
    ChronoExamples::demo();
    RegexExamples::demo();
    ThreadExamples::demo();
    RandomExamples::demo();
    HashExamples::demo();
    EnvExamples::demo();
    return 0;
}
