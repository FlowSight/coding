#ifndef RATE_LIMITER_H
#define RATE_LIMITER_H

#include <iostream>
#include <algorithm>
#include <string>
#include <deque>
#include <unordered_map>
#include <memory>

using namespace std;

namespace RateLimiter {

enum StrategyType
{
    Sliding,
    SlidingCredit,
    TokenBucket,
    NoStrategy
};

struct StrategyConfig
{
    public:
    string userId;
    int strategyType;
    int windowSize;
    
    virtual ~StrategyConfig() = default;
};

struct SlidingWindowStrategyConfig : public StrategyConfig {
    public:
    int limit;
    
    SlidingWindowStrategyConfig() = default;
    
    SlidingWindowStrategyConfig(string _userId, int _strategyType, int _windowSize, int _limit) {
        userId = _userId;
        strategyType = _strategyType;
        windowSize = _windowSize;
        limit = _limit;
    }
};

struct SlidingWindowCreditBasedStrategyConfig : public SlidingWindowStrategyConfig {
    public:
    int credit;
    
    SlidingWindowCreditBasedStrategyConfig() = default;
    
    SlidingWindowCreditBasedStrategyConfig(string _userId, int _strategyType, int _windowSize, int _limit, int _credit = 0) 
        : SlidingWindowStrategyConfig(_userId, _strategyType, _windowSize, _limit) {
        credit = _credit;
    }
};

struct FixedWindowStrategyConfig : public StrategyConfig {
    int limit;
    FixedWindowStrategyConfig() = default;
    
    FixedWindowStrategyConfig(string _userId, int _strategyType, int _windowSize, int _limit) {
        userId = _userId;
        strategyType = _strategyType;
        windowSize = _windowSize;
        limit = _limit;
    }
};

class UserData {
public:
    string id;
    string dataType;
    deque<int> reqTs;
    
    UserData(string _id) : id(_id) {}
    virtual ~UserData() = default;
    virtual int getLimit() = 0;  // Make abstract for polymorphism
};

class SlidingWindowUserData : public UserData {
public:
    int windowSize;
    int reqLimit;
    
    SlidingWindowUserData(string _userId = "default", int _windowSize = 10, int _limit = 10) 
        : UserData(_userId), windowSize(_windowSize), reqLimit(_limit) {
            dataType = "SlidingWindow";
    }

    int getLimit() override {
        return reqLimit;
    }
};

class SlidingWindowCreditUserData : public SlidingWindowUserData
{
public:
    int credit;
    
    SlidingWindowCreditUserData(string _id, int _window = 10, int limit = 10, int _credit = 0) 
        : SlidingWindowUserData(_id, _window, limit)
    {
        credit = _credit;
        dataType = "SlidingWindowCredit";
    }
    
    int getLimit() override
    {
        return credit + reqLimit;
    }
};

class FixedWindowUserData : public UserData {
    int windowSize;
    int reqLimit;
    FixedWindowUserData(string _userId = "default", int _windowSize = 10, int _limit = 10) 
        : UserData(_userId), windowSize(_windowSize), reqLimit(_limit) {
            dataType = "FixedWindow";
    }

    int getLimit() override {
        return reqLimit;
    }
};

// SRP: Single responsibility - manage user data storage/retrieval
// LSP: Works with base UserData type for proper polymorphism
class UserDataRepository {
private:
    unordered_map<string, shared_ptr<UserData>> userDataMap;

public:
    bool hasUser(const string& userId) const {
        return userDataMap.find(userId) != userDataMap.end();
    }

    shared_ptr<UserData> getUserData(const string& userId) {
        auto it = userDataMap.find(userId);
        if (it == userDataMap.end()) return nullptr;
        return it->second;
    }

    bool addUser(const string& userId, shared_ptr<UserData> userData) {
        if (hasUser(userId)) return false;
        userDataMap[userId] = userData;
        return true;
    }

    bool removeUser(const string& userId) {
        return userDataMap.erase(userId) > 0;
    }
};


// ISP: Segregate interfaces - clients should not depend on methods they don't use

// Core rate limiting interface - all strategies must support these
class RateLimitStrategy {
public:
    virtual ~RateLimitStrategy() = default;
    
    virtual bool canAccept(const string& userId, int ts) = 0;
    virtual bool doAccept(const string& userId, int ts) = 0;
};

// ISP: Separate interface for strategies that need user configuration
class ConfigurableStrategy {
public:
    virtual ~ConfigurableStrategy() = default;
    virtual int addUserData(StrategyConfig& config) = 0;
};

// ISP: Separate interface for strategies that provide quota information
class QuotaProvider {
public:
    virtual ~QuotaProvider() = default;
    virtual int getLimit(const string& userId) = 0;
    virtual int getRemainingQuota(const string& userId, int ts) = 0;
};


// ISP: Implements only the interfaces it actually needs
class SlidingWindowRateLimitStrategy : public RateLimitStrategy, 
                                        public ConfigurableStrategy,
                                        public QuotaProvider
{
protected:
    UserDataRepository* repository;

public:
    SlidingWindowRateLimitStrategy(UserDataRepository* repo) : repository(repo) {}

    // RateLimitStrategy interface
    bool canAccept(const string& userId, int ts) override
    {
        auto userData = repository->getUserData(userId);
        if (!userData) return false;
        
        auto swUserData = dynamic_pointer_cast<SlidingWindowUserData>(userData);
        if (!swUserData) return false;
        
        pruneOldReq(userId, ts);
        return userData->reqTs.size() < swUserData->reqLimit;
    }

    bool doAccept(const string& userId, int ts) override
    {
        if (!repository->hasUser(userId)) return false;
        
        if (canAccept(userId, ts))
        {
            auto userData = repository->getUserData(userId);
            userData->reqTs.push_front(ts);
            return true;
        }
        return false;
    }

    // ConfigurableStrategy interface
    int addUserData(StrategyConfig& config) override
    {
        SlidingWindowStrategyConfig& swConfig = dynamic_cast<SlidingWindowStrategyConfig&>(config);
        auto userData = make_shared<SlidingWindowUserData>(swConfig.userId, swConfig.windowSize, swConfig.limit);
        return repository->addUser(swConfig.userId, userData) ? 1 : 0;
    }
    
    // QuotaProvider interface
    int getLimit(const string& userId) override
    {
        auto userData = repository->getUserData(userId);
        if (!userData) return 0;
        return userData->getLimit();
    }

    int getRemainingQuota(const string& userId, int ts) override
    {
        auto userData = repository->getUserData(userId);
        if (!userData) return 0;
        
        auto swUserData = dynamic_pointer_cast<SlidingWindowUserData>(userData);
        if (!swUserData) return 0;
        
        pruneOldReq(userId, ts);
        return swUserData->reqLimit - userData->reqTs.size();
    }

private:
    int pruneOldReq(string userId, int ts)
    {
        auto userData = repository->getUserData(userId);
        if (!userData) return 0;
        
        auto swUserData = dynamic_pointer_cast<SlidingWindowUserData>(userData);
        if (!swUserData) return 0;
        
        auto &reqQ = userData->reqTs;
        while (!reqQ.empty() && (reqQ.back() <= ts - swUserData->windowSize))
            reqQ.pop_back();
        return 1;
    }
};

// LSP: Properly extends parent, only overrides what's different (credit logic)
// Child can substitute parent without breaking behavior
class SlidingWindowCreditBasedRateLimitStrategy : public SlidingWindowRateLimitStrategy
{
public:
    SlidingWindowCreditBasedRateLimitStrategy(UserDataRepository* repo) 
        : SlidingWindowRateLimitStrategy(repo) {}

    // LSP: Override addUserData to use credit-based user data with proper config
    int addUserData(StrategyConfig& config) override
    {
        SlidingWindowCreditBasedStrategyConfig& creditConfig = dynamic_cast<SlidingWindowCreditBasedStrategyConfig&>(config);
        
        // Create credit-based user data polymorphically
        auto userData = make_shared<SlidingWindowCreditUserData>(
            creditConfig.userId, 
            creditConfig.windowSize, 
            creditConfig.limit,
            creditConfig.credit
        );
        
        return repository->addUser(creditConfig.userId, userData) ? 1 : 0;
    }

    // LSP: All other methods (canAccept, doAccept, pruneOldReq, windowUpdate) 
    // are inherited and work correctly through polymorphism
    // No need to duplicate them - that's the whole point of inheritance!
};

// DIP: Factory abstraction - high-level code depends on this, not concrete strategies
class RateLimitStrategyFactory {
public:
    virtual ~RateLimitStrategyFactory() = default;
    
    virtual shared_ptr<RateLimitStrategy> createStrategy(
        StrategyType type, 
        UserDataRepository* repository
    ) = 0;
    
    virtual shared_ptr<ConfigurableStrategy> createConfigurableStrategy(
        StrategyType type,
        UserDataRepository* repository
    ) = 0;
};

// DIP: Concrete factory implements the abstraction
class DefaultRateLimitStrategyFactory : public RateLimitStrategyFactory {
public:
    shared_ptr<RateLimitStrategy> createStrategy(
        StrategyType type, 
        UserDataRepository* repository
    ) override {
        switch(type) {
            case StrategyType::Sliding:
                return make_shared<SlidingWindowRateLimitStrategy>(repository);
            case StrategyType::SlidingCredit:
                return make_shared<SlidingWindowCreditBasedRateLimitStrategy>(repository);
            default:
                return nullptr;
        }
    }
    
    shared_ptr<ConfigurableStrategy> createConfigurableStrategy(
        StrategyType type,
        UserDataRepository* repository
    ) override {
        // Same strategies implement both interfaces
        return dynamic_pointer_cast<ConfigurableStrategy>(
            createStrategy(type, repository)
        );
    }
};

// SRP: Single responsibility - manage user to strategy type mapping
class UserStrategyRegistry {
private:
    unordered_map<string, StrategyType> userStrategyMap;

public:
    bool hasUser(const string& userId) const {
        return userStrategyMap.find(userId) != userStrategyMap.end();
    }

    StrategyType getStrategy(const string& userId) const {
        auto it = userStrategyMap.find(userId);
        return (it != userStrategyMap.end()) ? it->second : StrategyType::NoStrategy;
    }

    bool registerUser(const string& userId, StrategyType strategyType) {
        if (hasUser(userId)) return false;
        userStrategyMap[userId] = strategyType;
        return true;
    }

    bool unregisterUser(const string& userId) {
        return userStrategyMap.erase(userId) > 0;
    }
};

// DIP: High-level module depends on abstractions (factory interface), not concrete classes
class RateLimiterManager
{
private:
    UserStrategyRegistry strategyRegistry;
    UserDataRepository dataRepository;
    shared_ptr<RateLimitStrategyFactory> strategyFactory;  // DIP: Depend on abstraction
    
    // Store strategy instances
    unordered_map<StrategyType, shared_ptr<RateLimitStrategy>> strategies;
    unordered_map<StrategyType, shared_ptr<ConfigurableStrategy>> configurableStrategies;

public:
    // DIP: Dependency injection through constructor - testable and flexible
    RateLimiterManager(shared_ptr<RateLimitStrategyFactory> factory = nullptr) 
        : strategyFactory(factory ? factory : make_shared<DefaultRateLimitStrategyFactory>())
    {
        // DIP: Use factory abstraction to create strategies
        initializeStrategies();
    }

private:
    void initializeStrategies() {
        // Register available strategy types
        vector<StrategyType> availableTypes = {
            StrategyType::Sliding,
            StrategyType::SlidingCredit
        };
        
        for (auto type : availableTypes) {
            auto strategy = strategyFactory->createStrategy(type, &dataRepository);
            auto configurableStrategy = strategyFactory->createConfigurableStrategy(type, &dataRepository);
            
            if (strategy) {
                strategies[type] = strategy;
            }
            if (configurableStrategy) {
                configurableStrategies[type] = configurableStrategy;
            }
        }
    }

public:
    // DIP: Works through abstraction (RateLimitStrategy interface)
    int addReq(string userId, int ts)
    {
        if (!strategyRegistry.hasUser(userId))
        {
            cout << "User does not exist" << endl;
            return -1;
        }

        StrategyType type = strategyRegistry.getStrategy(userId);
        auto it = strategies.find(type);
        if (it != strategies.end())
        {
            return it->second->doAccept(userId, ts);
        }
        return -1;
    }

    // DIP: Works through abstraction (ConfigurableStrategy interface)
    int addUserStrategy(string userId, StrategyConfig& config)
    {
        if (strategyRegistry.hasUser(userId))
            return -1;

        StrategyType type = static_cast<StrategyType>(config.strategyType);
        auto it = configurableStrategies.find(type);
        
        if (it != configurableStrategies.end())
        {
            strategyRegistry.registerUser(userId, type);
            return it->second->addUserData(config);
        }
        
        return -1;
    }

    StrategyType getStrategy(string userId)
    {
        return strategyRegistry.getStrategy(userId);
    }
};

} // namespace RateLimiter

#endif
