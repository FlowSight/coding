
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x = 0, y = 0;  // ALWAYS default-init to avoid garbage

    // Constructor
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
};

struct Event {
    int start = 0, end = 0;
    string name;

    Event() = default;
    Event(int s, int e, string n) : start(s), end(e), name(move(n)) {}

    // operator< — required for set<Event>, map<Event, ...>, sort()
    // Sort by start time, then end time, then name
    bool operator<(const Event& other) const {
        if (start != other.start) return start < other.start;
        if (end != other.end) return end < other.end;
        return name < other.name;
    }

    // operator== — required for unordered_set, unordered_map
    bool operator==(const Event& other) const {
        return start == other.start && end == other.end && name == other.name;
    }

    // Print helper
    friend ostream& operator<<(ostream& os, const Event& e) {
        return os << "[" << e.start << "-" << e.end << " " << e.name << "]";
    }
};

void operatorDemo() {
    cout << "=== OPERATOR OVERLOADING ===" << endl;

    vector<Event> events = {{3,5,"C"}, {1,4,"A"}, {1,3,"B"}, {1,3,"A"}};
    sort(events.begin(), events.end());  // uses operator<
    for (auto& e : events) cout << e << endl;  // uses operator<<

    // set automatically uses operator<
    set<Event> eventSet(events.begin(), events.end());
    cout << "Set size: " << eventSet.size() << endl;
}

// ============================================================
// 3. USING std::tie FOR COMPARISONS — cleaner, less error-prone
// ============================================================

struct Transaction {
    string id;
    long long amount_cents = 0;
    int timestamp = 0;

    bool operator<(const Transaction& o) const {
        return tie(timestamp, amount_cents, id) < tie(o.timestamp, o.amount_cents, o.id);
    }
    bool operator==(const Transaction& o) const {
        return tie(timestamp, amount_cents, id) == tie(o.timestamp, o.amount_cents, o.id);
    }
};

void tieDemo() {
    cout << "\n=== std::tie COMPARISON ===" << endl;
    vector<Transaction> txns = {
        {"t3", 5000, 100},
        {"t1", 3000, 100},
        {"t2", 5000, 50}
    };
    sort(txns.begin(), txns.end());
    for (auto& t : txns)
        cout << t.timestamp << " " << t.amount_cents << " " << t.id << endl;
}

// ============================================================
// 4. CUSTOM COMPARATOR — for sort(), priority_queue, set
//    Use when you can't/don't want to modify the struct
// ============================================================

struct Task {
    int priority = 0;
    string name;
    int deadline = 0;
};

// --- Lambda comparator (most common in interviews) ---
void lambdaComparatorDemo() {
    cout << "\n=== LAMBDA COMPARATOR ===" << endl;

    vector<Task> tasks = {{2,"B",10}, {1,"A",5}, {3,"C",5}, {1,"D",3}};

    // Sort by priority asc, then deadline asc
    sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.priority != b.priority) return a.priority < b.priority;
        return a.deadline < b.deadline;
    });

    for (auto& t : tasks)
        cout << t.priority << " " << t.deadline << " " << t.name << endl;
}

// --- Functor comparator (for set, map, priority_queue) ---
struct TaskCmp {
    bool operator()(const Task& a, const Task& b) const {
        if (a.priority != b.priority) return a.priority < b.priority;
        return a.deadline < b.deadline;
    }
};

void functorComparatorDemo() {
    cout << "\n=== FUNCTOR COMPARATOR (set) ===" << endl;

    // set with custom comparator
    set<Task, TaskCmp> taskSet;
    taskSet.insert({2, "B", 10});
    taskSet.insert({1, "A", 5});
    taskSet.insert({3, "C", 5});

    for (auto& t : taskSet)
        cout << t.priority << " " << t.deadline << " " << t.name << endl;
}

// ============================================================
// 5. PRIORITY QUEUE WITH STRUCTS
//    GOTCHA: pq uses operator< for MAX-heap by default
//    For MIN-heap, reverse the comparison
// ============================================================

void pqDemo() {
    cout << "\n=== PRIORITY QUEUE ===" << endl;

    // --- MAX-HEAP (default) — largest priority first ---
    // Uses operator> in comparator because pq inverts
    auto maxCmp = [](const Task& a, const Task& b) {
        return a.priority < b.priority;  // < gives MAX-heap
    };
    priority_queue<Task, vector<Task>, decltype(maxCmp)> maxPQ(maxCmp);
    maxPQ.push({2, "B", 10});
    maxPQ.push({1, "A", 5});
    maxPQ.push({3, "C", 5});

    cout << "Max-heap (highest priority first):" << endl;
    while (!maxPQ.empty()) {
        auto t = maxPQ.top(); maxPQ.pop();
        cout << "  " << t.priority << " " << t.name << endl;
    }

    // --- MIN-HEAP — smallest priority first ---
    auto minCmp = [](const Task& a, const Task& b) {
        return a.priority > b.priority;  // > gives MIN-heap
    };
    priority_queue<Task, vector<Task>, decltype(minCmp)> minPQ(minCmp);
    minPQ.push({2, "B", 10});
    minPQ.push({1, "A", 5});
    minPQ.push({3, "C", 5});

    cout << "Min-heap (lowest priority first):" << endl;
    while (!minPQ.empty()) {
        auto t = minPQ.top(); minPQ.pop();
        cout << "  " << t.priority << " " << t.name << endl;
    }

    // --- SHORTCUT: use pair/tuple for simple cases ---
    // pair automatically compares lexicographically (first, then second)
    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<>> pairMinPQ;
    pairMinPQ.push({3, "C"});
    pairMinPQ.push({1, "A"});
    pairMinPQ.push({2, "B"});

    cout << "Pair min-heap:" << endl;
    while (!pairMinPQ.empty()) {
        auto [pri, name] = pairMinPQ.top(); pairMinPQ.pop();
        cout << "  " << pri << " " << name << endl;
    }
}

// ============================================================
// 6. STRUCT IN UNORDERED CONTAINERS — needs hash
// ============================================================

struct Edge {
    int from = 0, to = 0;

    bool operator==(const Edge& o) const {
        return from == o.from && to == o.to;
    }
};

// Option A: Hash functor
struct EdgeHash {
    size_t operator()(const Edge& e) const {
        // Combine hashes — standard interview pattern
        size_t h1 = hash<int>{}(e.from);
        size_t h2 = hash<int>{}(e.to);
        return h1 ^ (h2 << 1);  // simple combine
    }
};

void unorderedContainerDemo() {
    cout << "\n=== UNORDERED CONTAINERS WITH STRUCT ===" << endl;

    // Using hash functor
    unordered_set<Edge, EdgeHash> edgeSet;
    edgeSet.insert({1, 2});
    edgeSet.insert({2, 3});
    edgeSet.insert({1, 2});  // duplicate, won't be added
    cout << "Edge set size: " << edgeSet.size() << endl;  // 2

    unordered_map<Edge, int, EdgeHash> edgeWeight;
    edgeWeight[{1, 2}] = 10;
    edgeWeight[{2, 3}] = 20;

    // Option B: Lambda hash (inline, no separate struct)
    auto lambdaHash = [](const Edge& e) {
        return hash<long long>()(((long long)e.from << 32) | e.to);
    };
    unordered_set<Edge, decltype(lambdaHash)> edgeSet2(0, lambdaHash);
    edgeSet2.insert({1, 2});
}

// ============================================================
// 7. STRUCT IN MAP — ordered by struct fields
// ============================================================

void mapDemo() {
    cout << "\n=== MAP WITH STRUCT KEY ===" << endl;

    // map<K,V> requires operator< on K (or custom comparator)
    // Event already has operator<
    map<Event, string> eventStatus;
    eventStatus[{1, 3, "meeting"}] = "confirmed";
    eventStatus[{2, 5, "lunch"}] = "tentative";

    for (auto& [event, status] : eventStatus)
        cout << event << " -> " << status << endl;

    // lower_bound / upper_bound work on struct keys
    Event search{2, 0, ""};
    auto it = eventStatus.lower_bound(search);
    if (it != eventStatus.end())
        cout << "First event at/after time 2: " << it->first << endl;
}

// ============================================================
// 8. STRUCT WITH MULTIPLE SORT ORDERS
//    Same data, different sorting depending on context
// ============================================================

struct Job {
    string id;
    int profit = 0;
    int deadline = 0;
};

void multiSortDemo() {
    cout << "\n=== MULTIPLE SORT ORDERS ===" << endl;

    vector<Job> jobs = {
        {"A", 100, 2}, {"B", 50, 1}, {"C", 200, 2}, {"D", 150, 3}
    };

    // Sort by profit descending (greedy: pick most profitable first)
    auto byProfit = jobs;
    sort(byProfit.begin(), byProfit.end(), [](const Job& a, const Job& b) {
        return a.profit > b.profit;
    });
    cout << "By profit desc: ";
    for (auto& j : byProfit) cout << j.id << "(" << j.profit << ") ";
    cout << endl;

    // Sort by deadline ascending (EDF scheduling)
    auto byDeadline = jobs;
    sort(byDeadline.begin(), byDeadline.end(), [](const Job& a, const Job& b) {
        return a.deadline < b.deadline;
    });
    cout << "By deadline asc: ";
    for (auto& j : byDeadline) cout << j.id << "(d=" << j.deadline << ") ";
    cout << endl;

    // Stable sort — preserves original order for equal elements
    stable_sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.deadline < b.deadline;
    });
}

// ============================================================
// 9. STRUCT SERIALIZATION — to/from string
// ============================================================

struct LogEntry {
    int timestamp = 0;
    string level;
    string message;

    // Serialize to CSV
    string toCSV() const {
        return to_string(timestamp) + "," + level + "," + message;
    }
    bool operator< (const LogEntry& le) const {
        return timestamp < le.timestamp;
    }
    bool operator<= ( LogEntry& le) {
        if(timestamp < le.timestamp) return true;
        return timestamp == le.timestamp;
    }

    // Deserialize from CSV
    static LogEntry fromCSV(const string& line) {
        istringstream ss(line);
        LogEntry e;
        string ts;
        getline(ss, ts, ',');
        e.timestamp = stoi(ts);
        getline(ss, e.level, ',');
        getline(ss, e.message, ',');
        return e;
    }

    friend ostream& operator<<(ostream& os, const LogEntry& e) {
        return os << e.timestamp << " [" << e.level << "] " << e.message;
    }
};

void serializationDemo() {
    cout << "\n=== SERIALIZATION ===" << endl;

    LogEntry entry{1000, "ERROR", "payment failed"},
        entry1{1001, "ERROR1", "payment failed"};
    cout<<(entry < entry1)<<endl;
    cout<<(entry1<=entry)<<endl;
    string csv = entry.toCSV();
    cout << "CSV: " << csv << endl;

    LogEntry parsed = LogEntry::fromCSV(csv);
    cout << "Parsed: " << parsed << endl;
}

// ============================================================
// 10. INTERVAL STRUCT — common interview pattern
// ============================================================

struct Interval {
    int start = 0, end = 0;

    bool overlaps(const Interval& o) const {
        return start < o.end && o.start < end;
    }

    Interval merge(const Interval& o) const {
        return {min(start, o.start), max(end, o.end)};
    }

    bool operator<(const Interval& o) const {
        if (start != o.start) return start < o.start;
        return end < o.end;
    }

    friend ostream& operator<<(ostream& os, const Interval& i) {
        return os << "[" << i.start << "," << i.end << ")";
    }
};

vector<Interval> mergeIntervals(vector<Interval> intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<Interval> merged = {intervals[0]};
    for (int i = 1; i < (int)intervals.size(); i++) {
        if (merged.back().overlaps(intervals[i]))
            merged.back() = merged.back().merge(intervals[i]);
        else
            merged.push_back(intervals[i]);
    }
    return merged;
}

void intervalDemo() {
    cout << "\n=== INTERVALS ===" << endl;

    vector<Interval> intervals = {{1,3}, {2,5}, {7,10}, {8,12}, {15,18}};
    auto merged = mergeIntervals(intervals);
    for (auto& i : merged) cout << i << " ";
    cout << endl;  // [1,5) [7,12) [15,18)
}

// ============================================================
// CHEAT SHEET — what you need for each container
// ============================================================
/*
  Container               | Struct needs
  ------------------------|------------------------------------------
  vector + sort()         | lambda comparator OR operator<
  set<T>                  | operator<  (strict weak ordering)
  map<T, V>               | operator<
  priority_queue<T>       | lambda/functor comparator (reversed logic!)
  unordered_set<T>        | operator== AND hash (functor or lambda)
  unordered_map<T, V>     | operator== AND hash
  
  PQ COMPARATOR TRAP:
    < in comparator  →  MAX-heap (largest first)
    > in comparator  →  MIN-heap (smallest first)
    This is backwards from sort()! pq internally reverses the comparator.

  STRICT WEAK ORDERING (required for set/map/sort):
    - comp(a, a) must be false           (irreflexivity)
    - if comp(a, b) then !comp(b, a)     (asymmetry)
    - if comp(a, b) && comp(b, c)        (transitivity)
      then comp(a, c)
    Common bug: using <= instead of < breaks this.
    ALWAYS use < for less-than comparators, never <=.

  QUICK PATTERNS:
    // Sort by one field
    sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.x < b.x; });

    // Min-heap by one field
    auto cmp = [](auto& a, auto& b) { return a.x > b.x; };
    priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);

    // Unordered container with pair key
    auto h = [](const pair<int,int>& p) {
        return hash<long long>()(((long long)p.first << 32) | p.second);
    };
    unordered_set<pair<int,int>, decltype(h)> s(0, h);
*/

int main() {
    cout << "BUILD OK" << endl;  // canary
    // operatorDemo();
    // tieDemo();
    // lambdaComparatorDemo();
    // functorComparatorDemo();
    // pqDemo();
    // unorderedContainerDemo();
    // mapDemo();
    // multiSortDemo();
    serializationDemo();
    // intervalDemo();
    return 0;
}
