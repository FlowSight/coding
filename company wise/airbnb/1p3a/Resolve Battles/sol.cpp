// LC#: N/A | Severity: Medium | Pattern: Simulation
// Airbnb: Resolve Battles (Diplomacy-style)
//
// Algorithm:
// 1. Parse actions: Hold (stay), Support (boost ally), Move (attack location)
// 2. Invalidate support: if a supporter's location is attacked, its support is cut
// 3. Strength = 1 + number of valid supports
// 4. For each contested location: highest unique strength wins, ties → all die
// 5. Movers who lose → dead; holders who lose → dead

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

struct Army {
    string name;
    string location;
    string action;   // "Hold", "Support", "Move"
    string target;   // target army name (Support) or target location (Move)
    int strength = 1;
    bool supportValid = true;
    bool alive = true;
};

vector<string> resolveBattles(vector<string>& actions) {
    vector<Army> order; // preserve input order
    unordered_map<string, int> nameToIdx;

    // Step 1: Parse
    for (int i = 0; i < actions.size(); i++) {
        istringstream iss(actions[i]);
        Army a;
        iss >> a.name >> a.location >> a.action;
        if (a.action == "Support" || a.action == "Move") {
            iss >> a.target;
        }
        nameToIdx[a.name] = i;
        order.push_back(a);
    }

    // Step 2: Invalidate support — if anyone moves to a supporter's location, cut it
    for (auto& army : order) {
        if (army.action == "Move") {
            for (auto& other : order) {
                if (other.action == "Support" && other.location == army.target) {
                    other.supportValid = false;
                }
            }
        }
    }

    // Step 3: Calculate strengths
    for (auto& army : order) {
        if (army.action == "Support" && army.supportValid) {
            int idx = nameToIdx[army.target];
            order[idx].strength++;
        }
    }

    // Step 4: Resolve — group armies by final location
    // Each army's "claimed" location:
    //   Hold/Support → army.location
    //   Move → army.target
    unordered_map<string, vector<int>> locContenders;
    for (int i = 0; i < order.size(); i++) {
        string dest = (order[i].action == "Move") ? order[i].target : order[i].location;
        locContenders[dest].push_back(i);
    }

    for (auto& [loc, contenders] : locContenders) {
        if (contenders.size() <= 1) continue;

        int maxStr = 0;
        for (int idx : contenders)
            maxStr = max(maxStr, order[idx].strength);

        int maxCount = 0;
        for (int idx : contenders)
            if (order[idx].strength == maxStr) maxCount++;

        if (maxCount > 1) {
            // tie at max → everyone at this location dies
            for (int idx : contenders)
                order[idx].alive = false;
        } else {
            // only the weaker armies die
            for (int idx : contenders)
                if (order[idx].strength < maxStr)
                    order[idx].alive = false;
        }
    }

    // Step 5: Build result
    vector<string> result;
    for (auto& a : order) {
        if (!a.alive) {
            result.push_back(a.name + " [dead]");
        } else if (a.action == "Move") {
            result.push_back(a.name + " " + a.target);
        } else {
            result.push_back(a.name + " " + a.location);
        }
    }
    return result;
}

int main() {
    // Test 1: Basic — support defends against attack
    vector<string> t1 = {"A Munich Hold", "B Warsaw Support A", "C Bohemia Move Munich"};
    auto r1 = resolveBattles(t1);
    cout << "Test 1:" << endl;
    for (auto& s : r1) cout << "  " << s << endl;
    // Expected: A Munich, B Warsaw, C [dead]

    // Test 2: Support gets cut — attacker hits the supporter
    vector<string> t2 = {"A Munich Hold", "B Warsaw Support A", "C Bohemia Move Warsaw"};
    auto r2 = resolveBattles(t2);
    cout << "Test 2 (support cut):" << endl;
    for (auto& s : r2) cout << "  " << s << endl;
    // B's support cut → B(1) vs C(1) at Warsaw → tie → both dead
    // A stays in Munich (strength 1, uncontested)
    // Expected: A Munich, B [dead], C [dead]

    // Test 3: Equal strength attack — both die
    vector<string> t3 = {"A Munich Hold", "C Bohemia Move Munich"};
    auto r3 = resolveBattles(t3);
    cout << "Test 3 (equal strength):" << endl;
    for (auto& s : r3) cout << "  " << s << endl;
    // A(1) vs C(1) at Munich → tie → both dead
    // Expected: A [dead], C [dead]

    // Test 4: Attacker with support overpowers holder
    vector<string> t4 = {"A Munich Hold", "B Warsaw Support C", "C Bohemia Move Munich"};
    auto r4 = resolveBattles(t4);
    cout << "Test 4 (attacker wins):" << endl;
    for (auto& s : r4) cout << "  " << s << endl;
    // C gets support from B → C strength 2, A strength 1
    // Expected: A [dead], B Warsaw, C Munich

    return 0;
}
