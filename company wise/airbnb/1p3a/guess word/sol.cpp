#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
    string target;
    int callCount = 0;

    // Returns {bulls, cows}
    // bulls = correct digit in correct position
    // cows = correct digit in wrong position
    pair<int, int> guessServer(const string& guess) {
        callCount++;
        int bulls = 0, cows = 0;
        unordered_map<char, int> targetRemain, guessRemain;
        for (int i = 0; i < 4; i++) {
            if (guess[i] == target[i]) {
                bulls++;
            } else {
                targetRemain[target[i]]++;
                guessRemain[guess[i]]++;
            }
        }
        for (auto& [k, v] : guessRemain) {
            if (targetRemain.count(k))
                cows += min(v, targetRemain[k]);
        }
        return {bulls, cows};
    }

public:
    Solution(const string& target) : target(target) {}

    string guess() {
        callCount = 0;

        // Phase 1: Determine count of each digit (1-6) in target.
        // For "dddd", bulls = count(d) in target (cows is always 0).
        // Only need to test 5 digits; 6th is inferred.
        vector<int> digitCount(7, 0);
        int total = 0;
        for (int d = 1; d <= 5 && total < 4; d++) {
            string g(4, '0' + d);
            auto [bulls, cows] = guessServer(g);
            digitCount[d] = bulls;
            total += bulls;
        }
        digitCount[6] = 4 - total;

        // Build multiset of digits
        vector<int> digits;
        for (int d = 1; d <= 6; d++)
            for (int i = 0; i < digitCount[d]; i++)
                digits.push_back(d);

        // If all digits are the same, no Phase 2 needed
        if (digits[0] == digits[3]) {
            string ans(4, '0' + digits[0]);
            cout << "  Calls: " << callCount << endl;
            return ans;
        }

        // Find filler digit (absent from target, always exists since 4 slots / 6 digits)
        int filler = -1;
        for (int d = 1; d <= 6; d++) {
            if (digitCount[d] == 0) { filler = d; break; }
        }

        // Phase 2: Determine correct positions.
        // Optimization 1: Try sorted arrangement first — if bulls=4, done instantly.
        sort(digits.begin(), digits.end());
        string initGuess(4, '0');
        for (int i = 0; i < 4; i++) initGuess[i] = '0' + digits[i];
        auto [initBulls, initCows] = guessServer(initGuess);
        if (initBulls == 4) {
            cout << "  Calls: " << callCount << endl;
            return initGuess;
        }

        // Optimization 2: Position-by-position with elimination.
        // For each position, try unique candidates. Skip the last one —
        // if all others fail, the last must be correct (saves 1 call/position).
        vector<int> result(4, 0);
        vector<int> remaining = digits;

        for (int pos = 0; pos < 3; pos++) {
            if (remaining.empty()) break;

            // Get unique candidates from remaining
            vector<int> uniqueCands;
            for (int d : remaining)
                if (uniqueCands.empty() || uniqueCands.back() != d)
                    uniqueCands.push_back(d);

            // If only one unique digit remains, it fills this (and all later) positions
            if (uniqueCands.size() == 1) {
                result[pos] = uniqueCands[0];
                remaining.erase(find(remaining.begin(), remaining.end(), uniqueCands[0]));
                continue;
            }

            bool found = false;
            // Try all candidates EXCEPT the last (elimination principle)
            for (int i = 0; i < (int)uniqueCands.size() - 1; i++) {
                string g(4, '0' + filler);
                g[pos] = '0' + uniqueCands[i];
                auto [bulls, cows] = guessServer(g);
                if (bulls == 1) {
                    result[pos] = uniqueCands[i];
                    remaining.erase(find(remaining.begin(), remaining.end(), uniqueCands[i]));
                    found = true;
                    break;
                }
            }
            if (!found) {
                // Last candidate must be correct (elimination)
                int last = uniqueCands.back();
                result[pos] = last;
                remaining.erase(find(remaining.begin(), remaining.end(), last));
            }
        }

        // Position 3 gets whatever remains
        if (!remaining.empty())
            result[3] = remaining[0];

        string ans;
        for (int d : result) ans += ('0' + d);
        cout << "  Calls: " << callCount << endl;
        return ans;
    }
};

// Test
int main() {
    vector<string> tests = {"3264", "1123", "1213", "6666", "1111", "5261", "6543", "2244", "1166"};
    for (const string& t : tests) {
        Solution sol(t);
        string res = sol.guess();
        cout << "Target: " << t << " | Guessed: " << res
             << " | " << (res == t ? "PASS" : "FAIL") << endl << endl;
    }
    return 0;
}