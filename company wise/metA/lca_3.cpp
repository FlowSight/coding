
// below is the most cunning sol..but be careful if you do it in interview
// for interview the naive sol..is better and almost similar 
class Solution {
    public:
        Node* lowestCommonAncestor(Node* p, Node * q) {
            auto node1 = p;
            auto node2 = q;
            while(node1 != node2){
                node1 = (node1 ? node1->parent : p);
                node2 = (node2 ? node2->parent : q);
            }
            return node1;
        }
    };