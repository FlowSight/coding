
// agent receives ratings via method call (1-5)
// rankAgents() : gets sorted list of agents by their ratings
// Enhanced to support month-wise rating tracking and ranking
// Design Patterns Used: Strategy, Factory, Observer
// SOLID Principles: SRP, OCP, DIP

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

namespace CallCenter
{
    // Value Object for Date (Immutable)
    class MonthYear {
    public:
        int month;
        int year;
        
        MonthYear(int m = 0, int y = 0) : month(m), year(y) {}
        
        string getKey() const {
            return to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month);
        }
        
        bool operator<(const MonthYear& other) const {
            if (year != other.year) return year < other.year;
            return month < other.month;
        }
        
        bool operator==(const MonthYear& other) const {
            return year == other.year && month == other.month;
        }
    };
    
    // Hash function for MonthYear
    struct MonthYearHash {
        size_t operator()(const MonthYear& my) const {
            return hash<int>()(my.year * 100 + my.month);
        }
    };

    // Base Rating Entity
    struct AgentRating {
        string userId;
        int rating;
        
        AgentRating(string _userId, int _rating) : 
            userId(_userId), rating(_rating) {}
        
        virtual ~AgentRating() = default;
    };

    // Extended Rating with Date Information
    struct AgentRatingWithDate : public AgentRating {
        int day, month, year;
        
        AgentRatingWithDate(string _userId, int _rating, int _day, int _month, int _year) :
            AgentRating(_userId, _rating), day(_day), month(_month), year(_year) {}
        
        MonthYear getMonthYear() const {
            return MonthYear(month, year);
        }
    };

    // Interface Segregation - Separate interfaces for different operations
    class IRatingStorage {
    public:
        virtual void addRating(const string& userId, int rating, const MonthYear& period) = 0;
        virtual int getTotalRating(const string& userId) = 0;
        virtual int getMonthlyRating(const string& userId, const MonthYear& period) = 0;
        virtual ~IRatingStorage() = default;
    };

    // Strategy Pattern - Different ranking strategies
    class IRankingStrategy {
    public:
        virtual vector<pair<string, int>> getRanking() = 0;
        virtual void displayRanking() = 0;
        virtual ~IRankingStrategy() = default;
    };

    // Concrete Storage Implementation
    class RatingStorage : public IRatingStorage {
    private:
        // Overall ratings
        unordered_map<string, int> overallRatings;
        
        // Month-wise ratings: userId -> (MonthYear -> rating)
        unordered_map<string, unordered_map<MonthYear, int, MonthYearHash>> monthlyRatings;
        
        // Reverse index for quick ranking: rating -> set of userIds
        map<int, unordered_set<string>, greater<int>> overallScoreMap;
        
        // Month-wise reverse index: MonthYear -> (rating -> set of userIds)
        unordered_map<MonthYear, map<int, unordered_set<string>, greater<int>>, MonthYearHash> monthlyScoreMap;
        
        void updateScoreMap(const string& userId, int oldScore, int newScore);
        void updateMonthlyScoreMap(const string& userId, const MonthYear& period, int oldScore, int newScore);
        
    public:
        void addRating(const string& userId, int rating, const MonthYear& period);
        int getTotalRating(const string& userId);
        int getMonthlyRating(const string& userId, const MonthYear& period);
        
        const map<int, unordered_set<string>, greater<int>>& getOverallScoreMap() const;
        const map<int, unordered_set<string>, greater<int>>& getMonthlyScoreMap(const MonthYear& period) const;
        vector<MonthYear> getAllMonths() const;
    };

    // Overall Ranking Strategy
    class OverallRankingStrategy : public IRankingStrategy {
    private:
        const RatingStorage* storage;
        
    public:
        OverallRankingStrategy(const RatingStorage* store) : storage(store) {}
        
        vector<pair<string, int>> getRanking();
        void displayRanking();
    };

    // Monthly Ranking Strategy
    class MonthlyRankingStrategy : public IRankingStrategy {
    private:
        const RatingStorage* storage;
        MonthYear period;
        
    public:
        MonthlyRankingStrategy(const RatingStorage* store, const MonthYear& p) 
            : storage(store), period(p) {}
        
        vector<pair<string, int>> getRanking();
        void displayRanking();
    };

    // All Months Ranking Strategy
    class AllMonthsRankingStrategy : public IRankingStrategy {
    private:
        const RatingStorage* storage;
        
    public:
        AllMonthsRankingStrategy(const RatingStorage* store) : storage(store) {}
        
        vector<pair<string, int>> getRanking();
        void displayRanking();
    };

    // Repository Pattern - Manages data access
    class AgentRatingRepository {
    private:
        unique_ptr<RatingStorage> storage;
        
    public:
        AgentRatingRepository() : storage(make_unique<RatingStorage>()) {}
        
        void addRating(const string& userId, int rating, const MonthYear& period) {
            storage->addRating(userId, rating, period);
        }
        
        const RatingStorage* getStorage() const {
            return storage.get();
        }
    };

    // Factory Pattern - Creates appropriate ranking strategy
    class RankingStrategyFactory {
    public:
        static unique_ptr<IRankingStrategy> createOverallStrategy(const RatingStorage* storage) {
            return make_unique<OverallRankingStrategy>(storage);
        }
        
        static unique_ptr<IRankingStrategy> createMonthlyStrategy(
            const RatingStorage* storage, const MonthYear& period) {
            return make_unique<MonthlyRankingStrategy>(storage, period);
        }
        
        static unique_ptr<IRankingStrategy> createAllMonthsStrategy(const RatingStorage* storage) {
            return make_unique<AllMonthsRankingStrategy>(storage);
        }
    };

    // Facade Pattern - Simplified interface for clients
    class CallCenterManager {
    private:
        unique_ptr<AgentRatingRepository> repository;
        
    public:
        CallCenterManager() : repository(make_unique<AgentRatingRepository>()) {}
        
        void addRating(const string& userId, int rating, int day, int month, int year) {
            MonthYear period(month, year);
            repository->addRating(userId, rating, period);
        }
        
        void getOverallRanking() const {
            auto strategy = RankingStrategyFactory::createOverallStrategy(repository->getStorage());
            strategy->displayRanking();
        }
        
        void getMonthlyRanking(int month, int year) const {
            MonthYear period(month, year);
            auto strategy = RankingStrategyFactory::createMonthlyStrategy(repository->getStorage(), period);
            strategy->displayRanking();
        }
        
        void getAllMonthsRanking() const {
            auto strategy = RankingStrategyFactory::createAllMonthsStrategy(repository->getStorage());
            strategy->displayRanking();
        }
    };

    // ========================== IMPLEMENTATION ==========================

    void RatingStorage::updateScoreMap(const string& userId, int oldScore, int newScore) {
        if (oldScore > 0) {
            auto it = overallScoreMap.find(oldScore);
            if (it != overallScoreMap.end()) {
                it->second.erase(userId);
                if (it->second.empty()) {
                    overallScoreMap.erase(it);
                }
            }
        }
        overallScoreMap[newScore].insert(userId);
    }

    void RatingStorage::updateMonthlyScoreMap(const string& userId, const MonthYear& period, 
                                               int oldScore, int newScore) {
        auto& scoreMap = monthlyScoreMap[period];
        
        if (oldScore > 0) {
            auto it = scoreMap.find(oldScore);
            if (it != scoreMap.end()) {
                it->second.erase(userId);
                if (it->second.empty()) {
                    scoreMap.erase(it);
                }
            }
        }
        scoreMap[newScore].insert(userId);
    }

    void RatingStorage::addRating(const string& userId, int rating, const MonthYear& period) {
        // Update overall rating
        int oldOverallScore = overallRatings[userId];
        int newOverallScore = oldOverallScore + rating;
        overallRatings[userId] = newOverallScore;
        updateScoreMap(userId, oldOverallScore, newOverallScore);
        
        // Update monthly rating
        int oldMonthlyScore = monthlyRatings[userId][period];
        int newMonthlyScore = oldMonthlyScore + rating;
        monthlyRatings[userId][period] = newMonthlyScore;
        updateMonthlyScoreMap(userId, period, oldMonthlyScore, newMonthlyScore);
    }

    int RatingStorage::getTotalRating(const string& userId) {
        auto it = overallRatings.find(userId);
        return (it != overallRatings.end()) ? it->second : 0;
    }

    int RatingStorage::getMonthlyRating(const string& userId, const MonthYear& period) {
        auto userIt = monthlyRatings.find(userId);
        if (userIt != monthlyRatings.end()) {
            auto monthIt = userIt->second.find(period);
            if (monthIt != userIt->second.end()) {
                return monthIt->second;
            }
        }
        return 0;
    }

    const map<int, unordered_set<string>, greater<int>>& RatingStorage::getOverallScoreMap() const {
        return overallScoreMap;
    }

    const map<int, unordered_set<string>, greater<int>>& RatingStorage::getMonthlyScoreMap(const MonthYear& period) const {
        static const map<int, unordered_set<string>, greater<int>> emptyMap;
        auto it = monthlyScoreMap.find(period);
        return (it != monthlyScoreMap.end()) ? it->second : emptyMap;
    }

    vector<MonthYear> RatingStorage::getAllMonths() const {
        unordered_set<int> uniqueMonths;
        vector<MonthYear> result;
        
        for (const auto& userEntry : monthlyRatings) {
            for (const auto& monthEntry : userEntry.second) {
                int key = monthEntry.first.year * 100 + monthEntry.first.month;
                if (uniqueMonths.insert(key).second) {
                    result.push_back(monthEntry.first);
                }
            }
        }
        
        sort(result.begin(), result.end());
        return result;
    }

    vector<pair<string, int>> OverallRankingStrategy::getRanking() {
        vector<pair<string, int>> ranking;
        const auto& scoreMap = storage->getOverallScoreMap();
        
        for (const auto& [score, users] : scoreMap) {
            for (const auto& userId : users) {
                ranking.push_back({userId, score});
            }
        }
        return ranking;
    }

    void OverallRankingStrategy::displayRanking() {
        cout << "\n=== Overall Agent Ranking ===" << endl;
        cout << left << setw(20) << "Agent" << "Total Rating" << endl;
        cout << string(40, '-') << endl;
        
        auto ranking = getRanking();
        int rank = 1;
        for (const auto& [userId, score] : ranking) {
            cout << rank++ << ". " << left << setw(17) << userId << score << endl;
        }
    }

    vector<pair<string, int>> MonthlyRankingStrategy::getRanking() {
        vector<pair<string, int>> ranking;
        const auto& scoreMap = storage->getMonthlyScoreMap(period);
        
        for (const auto& [score, users] : scoreMap) {
            for (const auto& userId : users) {
                ranking.push_back({userId, score});
            }
        }
        return ranking;
    }

    void MonthlyRankingStrategy::displayRanking() {
        cout << "\n=== Monthly Agent Ranking (" << period.getKey() << ") ===" << endl;
        cout << left << setw(20) << "Agent" << "Monthly Rating" << endl;
        cout << string(40, '-') << endl;
        
        auto ranking = getRanking();
        if (ranking.empty()) {
            cout << "No ratings for this month." << endl;
            return;
        }
        
        int rank = 1;
        for (const auto& [userId, score] : ranking) {
            cout << rank++ << ". " << left << setw(17) << userId << score << endl;
        }
    }

    vector<pair<string, int>> AllMonthsRankingStrategy::getRanking() {
        // Returns empty - this strategy is for display only
        return {};
    }

    void AllMonthsRankingStrategy::displayRanking() {
        auto months = storage->getAllMonths();
        
        if (months.empty()) {
            cout << "\nNo monthly data available." << endl;
            return;
        }
        
        for (const auto& month : months) {
            MonthlyRankingStrategy monthStrategy(storage, month);
            monthStrategy.displayRanking();
        }
    }
}

// #endif