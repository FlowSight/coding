// LC : 1041
// sev0 :didnt remember the trick..its a maths proof qs

class Solution {
public:
    typedef vector<int> vi;
    typedef vector<vi> vvi;
    vector<char> face = {'U','L','D','R'};
    vvi dirs = {{0,1},{-1,0},{0,-1},{1,0}};
    bool isRobotBounded(string instructions) {
        int diridx = 0, r = 0, c = 0;
        for(auto ch: instructions){
                if(ch == 'G') move(r,c,diridx);
                else if(ch == 'L') diridx = (diridx + 1)%4;
                else diridx = (diridx -1 + 4)%4;
        }
        return (!r && !c) || diridx;
    }
    void move(int& r, int& c, int idx){
        r += dirs[idx][0];
        c += dirs[idx][1];
    }
};
