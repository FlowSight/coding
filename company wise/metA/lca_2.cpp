//30 apr 2025 ..8 min. 
//can do with O(1) space but it will make traverse one round extra..
// there is one unique solution..which can only be memorized..still  putting here..

public Node lowestCommonAncestor(Node p, Node q) {
	Node a = p, b = q;
	while (a != b) {
		a = a == null? q : a.parent;
		b = b == null? p : b.parent;    
	}
	return a;
}

class Solution {
    public:
        Node* lowestCommonAncestor(Node* p, Node * q) {
            unordered_set<Node*> ss;
            while(true) {
                ss.insert(p);
                if((p->parent == p) || (!p->parent)) break; // root
                p = p->parent;
            }
            while(true) {
                if(ss.find(q) != ss.end()) return q;
                if((q->parent == q) || (!q->parent)) break; // root
                q = q->parent;
            }
            return q;
        }
    };
    