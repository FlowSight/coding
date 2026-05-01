#include <bits/stdc++.h>
using namespace std;

enum Party { NoParty = -1, Demo = 1, Repub = 2 };

struct Person {
    string name;
    Party party;
    int durationMs;
};

// Min-heap: shortest duration person at top
struct CmpDuration {
    bool operator()(const Person& a, const Person& b) {
        return a.durationMs > b.durationMs;  // min-heap
    }
};

class PoliticalBathroom {
public:
    explicit PoliticalBathroom(int cap = 3) : cap_(cap) {}

    void useBathroom(string name, Party party, int durationMs) {
        {
            unique_lock<mutex> ul(mtx);

            // Enqueue into party-specific min-heap
            if (party == Demo)
                demoHeap.push({name, party, durationMs});
            else
                repubHeap.push({name, party, durationMs});

            // Wait until: my party's turn, I'm at the top of my heap, and room available
            cv.wait(ul, [&] {
                auto& myHeap = getHeap(party);
                bool imNext = !myHeap.empty() && myHeap.top().name == name;
                if (!imNext) return false;

                if (curparty == party && curcount < cap_) {
                    // Same party occupying, room available
                    // But block new entries if the OTHER party is waiting
                    // and we've already admitted cap_ people this epoch
                    Party other = (party == Demo) ? Repub : Demo;
                    if (!getHeap(other).empty() && epochCount >= cap_) return false;
                    return true;
                }
                if (curparty == NoParty) {
                    // Bathroom empty — pick the party with priority
                    Party chosen = chooseNextParty();
                    return chosen == party;
                }
                return false;
            });

            // Admitted — pop myself from the heap
            getHeap(party).pop();
            if (curparty != party) epochCount = 0;  // new party, reset epoch
            curparty = party;
            curcount++;
            epochCount++;
        }

        cout << "IN:  " << name << " (party=" << party
             << ", dur=" << durationMs << "ms, inside=" << curcount << ")" << endl;

        this_thread::sleep_for(chrono::milliseconds(durationMs));

        {
            unique_lock<mutex> ul(mtx);
            curcount--;
            if (curcount == 0) {
                lastParty = curparty;
                curparty = NoParty;
            }
            cv.notify_all();
            cout << "OUT: " << name << " (party=" << party
                 << ", remaining=" << curcount << ")" << endl;
        }
    }

private:
    int cap_;
    int curcount = 0;
    int epochCount = 0;
    Party curparty = NoParty;
    Party lastParty = NoParty;
    mutex mtx;
    condition_variable cv;

    priority_queue<Person, vector<Person>, CmpDuration> demoHeap;
    priority_queue<Person, vector<Person>, CmpDuration> repubHeap;

    priority_queue<Person, vector<Person>, CmpDuration>& getHeap(Party p) {
        return (p == Demo) ? demoHeap : repubHeap;
    }

    // Choose which party goes next when bathroom is empty.
    // Pick the party whose shortest job is shorter (SJF at batch level).
    // Tie-break: prefer the party that didn't go last (fairness).
    Party chooseNextParty() {
        bool demoWaiting = !demoHeap.empty();
        bool repubWaiting = !repubHeap.empty();

        if (demoWaiting && !repubWaiting) return Demo;
        if (!demoWaiting && repubWaiting) return Repub;
        if (!demoWaiting && !repubWaiting) return NoParty;

        // Both waiting — prefer party that didn't go last
        if (lastParty == Demo) return Repub;
        if (lastParty == Repub) return Demo;

        // Neither went last (first run) — pick shortest job
        if (demoHeap.top().durationMs <= repubHeap.top().durationMs)
            return Demo;
        return Repub;
    }
};

// ─────────────────────────────────────────────
// Test
// ─────────────────────────────────────────────

void test() {
    PoliticalBathroom pb(3);
    vector<thread> threads;

    // Democrats: short, medium, long
    threads.emplace_back([&] { pb.useBathroom("D1_100ms",  Demo, 100); });
    threads.emplace_back([&] { pb.useBathroom("D2_200ms",  Demo, 200); });
    threads.emplace_back([&] { pb.useBathroom("D3_5000ms", Demo, 5000); });

    // Republican: very short
    threads.emplace_back([&] { pb.useBathroom("R1_50ms",   Repub, 50); });
    threads.emplace_back([&] { pb.useBathroom("R2_80ms",   Repub, 80); });

    // More Democrats arriving later
    this_thread::sleep_for(chrono::milliseconds(50));
    threads.emplace_back([&] { pb.useBathroom("D4_150ms",  Demo, 150); });
    threads.emplace_back([&] { pb.useBathroom("D5_300ms",  Demo, 300); });

    for (auto& t : threads) t.join();
    cout << "\nAll done.\n";
}

int main() {
    test();
    return 0;
}
