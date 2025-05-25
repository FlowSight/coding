// 6 apr 
// got the core idea and everything...missed the direction bit while in a cell..
// sev1


 class Solution {
    public:
        vector<vector<int>> dirs = {{-1,0},{0,-1},{1,0},{0,1}};
        set<pair<int,int>> visited;
        void cleanRoom(Robot& robot) {
            visited.clear();
            helper(robot,0,0);
        }
    
        void helper(Robot& robot, int r, int c, int face = 0){
            if(visited.find({r,c}) != visited.end()) return;
            visited.insert({r,c});
    
            robot.clean();
    
            for(auto i=0;i<4;i++) {
                 if(robot.move()) {
                    helper(robot,r+dirs[(face+i)%4][0],c+dirs[(face+i)%4][1],(face+i)%4);
                    robot.turnLeft();
                    robot.turnLeft();
                    robot.move();
                    robot.turnLeft();
                    robot.turnLeft();
                 }
                  robot.turnLeft(); // make ready for next cell visit
            }
        }
    };



    // key is : FACE