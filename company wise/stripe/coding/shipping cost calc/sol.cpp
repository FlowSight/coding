#include <iostream>

using namespace std;

struct Item {
    public:
    string product;
    int quan;
    Item(string _prod, int _q) {
        product = _prod;
        quan = _q;
    }
    Item() = default;
};

struct Order {
    public:
    string country;
    unordered_map<string,int> pricemap;
    Order(string _country, vector<Item> _prices) {
        for(auto it : _prices) {
            pricemap[it.product] = it.quan;
        }
        country = _country;
    }
    Order() = default;
};

struct TierPrice {
    vector<vector<int>> prices;
    TierPrice() = default;
    TierPrice(vector<vector<int>> _prices){
        prices = _prices;
        sort(prices.begin(),prices.end(),[](vector<int> v1, vector<int> v2){
            return v1[1] < v2[1];
        });
    }
};

struct ItemCost {
        public:
    string prodname;
    TierPrice tp;
    ItemCost(string _prd, TierPrice _tp){
        prodname = _prd;
        tp = _tp;
    }
};


struct ShippingCost {
        public:
    unordered_map<string,unordered_map<string, TierPrice>> cntry2prices;
    vector<ItemCost> itarr;
    ShippingCost() = default;
    void addCountry(string country, vector<ItemCost> pricearr){
        for(auto it : pricearr){
            cntry2prices[country][it.prodname] = it.tp;
        }
    }
};

class ShippingHelper {
    public:
    ShippingHelper() = default;
    void calculate_shipping_cost(Order order, ShippingCost sc){
        int ans = 0;
        auto it = sc.cntry2prices.find(order.country);
        if(it == sc.cntry2prices.end()) return;
        auto cntrymap = sc.cntry2prices[order.country];
        //order items iteration
        for(auto it1 : order.pricemap){
            if(cntrymap.find(it1.first) != cntrymap.end()) {
                int quantity = it1.second;
                for(auto it2 : cntrymap[it1.first].prices){
                    if(quantity == 0) break;
                    int applicable = min(quantity,(it2[2] == -1 ? quantity :  it2[2]));
                    quantity -= applicable;
                    int cost = it2[0] ? it2[3] : applicable * it2[3];
                    ans += cost;
                }
            }
        }
        cout<<ans<<endl;
    }
};

// incr = 0, fixed = 1

void testmethod() {
    vector<Item> itemsus = {
        {"mouse",20},
        {"laptop",5}
    };
    Order order_us("US",itemsus);
    vector<Item> itemsca = {
        {"mouse",20},
        {"laptop",5}
    };
    Order order_ca("CA",itemsca);

    ShippingCost sc;
    vector<ItemCost> itemcostsus = {
        ItemCost("mouse",TierPrice({{0,0,-1,550}})),
        ItemCost("laptop",TierPrice({{1,0,2,1000},{0,3,-1,900}})),
    };
    vector<ItemCost> itemcostsca = {
        ItemCost("mouse",TierPrice({{0,0,-1,750}})),
        ItemCost("laptop",TierPrice({{1,0,2,1100},{0,3,-1,1000}})),
    };
    sc.addCountry("US",itemcostsus);
    sc.addCountry("CA",itemcostsca);

    ShippingHelper sh;
    sh.calculate_shipping_cost(order_us,sc);
    sh.calculate_shipping_cost(order_ca,sc);
}

int main() {
    testmethod();
    return 0;
}