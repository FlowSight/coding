// 25 apr 2025
// didnt know math..learnt
// sev0 sev0

class Solution {
    public:
        double R, x, y;
        Solution(double radius, double x_center, double y_center) {
            R = radius;
            x = x_center;
            y = y_center;
    
        }
        double randomDoubleFraction(){
            return (double)rand()/RAND_MAX;
        }
        
        vector<double> randPoint() {
            double randRad = sqrt(randomDoubleFraction()) * R, theta = 2*M_PI*randomDoubleFraction();
            double xx = x + sin(theta)*randRad, yy = y + cos(theta)*randRad;
            return {xx,yy};
        }
    };
    
    // if we choose uniform r from [0..R] then equal points 
    // will be on radius r1 and r2 where r1< r2 where in fact
    // it should have been more points in radius r2 than r1 as
    // it involves more area.
    // hence we choose sqrt() on rand(). after applying sqrt on 
    // random() (a point between [0, 1]), the result would be a 
    // value greater than the original random() thus making it 
    // biased more towards the outer end.
    