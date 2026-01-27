
// Given two classes: Item and DataStore.

// Class Definitions
Struct Item {
    string buyer_name, seller, item_name;
    int price;
}

class DataStore{
    vector<Item> items;
    vector<Item> getAll() // implement this
    void put(Item item)
}

cant change above 2 classes

class TradeInstance{
    DataStore ds;
    TradeInstance(DataStore& ds);

    // arg : 
    // buyItemsMap : map of item and price which user wants to buy
    // return : map of item name to (min price of unsold item available in ds)
    map<string,int> getEligibleItems(const map<string,int>& buyItemsMap){
        // my logic below
        map<string,int> ans;
        auto items = ds.getAll();
        for(auto it : items){
            if(buyItemsMap.find(it.item_name) == buyItemsMap.end()) continue;
            if(buyItemsMap[it.item_name] < it.price) continue;
            ans[it.item_name] = min(it.price,ans[it.item_name]);
        }
        return ans;
    }
}



when i coded this, my code had below bugs:
1. if(buyItemsMap[it.item_name] : const map cant be acccessed like this
2. ans was being accessed before initializing, ans would alwasy be 0
3. didnt check if seller name was empty or not.

I  said tc=O(n) sc = O(n),when actually tc = O(nlogn)

I offered to dry run, interviewer said not needed. ended the interview at 25 min mark.

if allowed to dry run i could have fixed 3. 1 and 2 i did not know.