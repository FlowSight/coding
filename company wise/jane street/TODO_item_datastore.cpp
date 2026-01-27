// Task Description
// Implement two classes: Item and DataStore.

// Class Definitions
// Item:

// buyer: Optional string (buyer's name).
// seller: String (seller's name).
// price: Integer.
// item_name: String.
// DataStore:

// update(item_name, buyer_name=None): Updates an item. If a sale occurs, buyer changes from null to the specified buyer_name.
// getAll(): Returns current information of all Items, in chronological order of transactions.
// Transaction Logic
// Given a mapping map(item_name -> Item) representing items to be purchased (with buyer's intended price and name):

// Price Determination: Return map(item_name -> price), representing the final sold price. This should be the lowest price among items with the same name in DataStore that is also below the buyer's intended price.
// Update: Update the DataStore with the transaction.
// Refund & Charge Logic
// Handle transaction failures and return charge/refund info (buyer_name, refund/charge_amount) based on:

// Scenario 1 (Sale Failure): An item's sale fails, putting it back for sale.
// If subsequent transactions succeed, refund transaction amounts and the item is resold.
// If the same item later sells successfully at a higher price, do nothing.
// Scenario 2 (Payment Failure): A buyer's payment fails due to lack of stock.
// Only charge the amount (before failure) if the buyer attempts to purchase after the failed sale in chronological order.
// Input/Output
// Input: Initialized DataStore and Item objects.
// Output: Price map and charge/refund information.
// Example Usage
// # item_name1 -> Item(seller='A', price=90, buyer='')
// data_store.update('item_name1', 'buyer_name')
// # item_name1 -> Item(seller='A', price=70, buyer='buyer_name')
// charge_info = data_store.get_charge_info()

#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Item {
    public:
    string buyer_name, seller, item_name;
    int price;
    Item(string b,string i_name,int _p, string _s = ""){
        buyer_name = b;
        price = _p;
        item_name = i_name;
        this->seller = _s;
    }
};

class DataStore{
    public:

    vector<Item> items;
    vector<Item> getAll() {
        return items;
    }
    void put(Item item){
        items.push_back(item);
    }
};

class TradeInstance{
    public:
    DataStore ds;
    TradeInstance(DataStore& _ds){
        ds = _ds;
    }

    // arg : 
    // buyItemsMap : map of item and price which user wants to buy
    // return : map of item name to (min price of unsold item available in ds)
    map<string,int> getEligibleItems(const map<string,int>& buyItemsMap){
        // my logic below
        map<string,int> ans;
        auto items = ds.getAll();
        for(auto it : items){
            auto it_buy = buyItemsMap.find(it.item_name);
            if(it_buy == buyItemsMap.end()) continue;
            if(it_buy->second < it.price) continue;
            if(ans.find(it.item_name) == ans.end()) ans[it.item_name] = it.price;
            else ans[it.item_name] = min(it.price,ans[it.item_name]);
        }
        return ans;
    }
};

int main(){
    DataStore ds;
    for(auto i=0;i<4;i++)ds.put(Item("Anirban","itemname",i+1));
    TradeInstance ti(ds);
    map<string,int> buyItemsMap;
    buyItemsMap["itemname"] = 3;
    auto ans = ti.getEligibleItems(buyItemsMap);
    for(auto it : ans){
        cout<<it.first<<" "<<it.second<<"\n";
    }
    return 0;
}