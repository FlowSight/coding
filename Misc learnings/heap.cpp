
//so when creating custom objects...alwsys use operator< 
// set comparator

class SetName{
  public:
  int profit;
  int capital;
  SetName(int p, int c){
    profit = p;
    capital = c;
  }
  bool operator< (const SetName& s1) const {
        return this->profit >= s1.profit;
  }
};


//But if set is made up of struct which doesnt have comparator, thne u have to create comparator function and pass it to set
 struct cmp{
    bool operator() (ListNode* node1, ListNode* node2) const {
        return node1->val < node2->val;
    }
 };
 set<ListNode*, cmp> s;


//set will automatically understand that it has to use this comparator function to sort the elements..so no operator< is used.

same pattern for priority queue, just that the order is reversed
Also, if equal == operator is not defined, then set will not add the element if it is already present in the set.

for priority queue in reverse order, negate the value while push and pop
