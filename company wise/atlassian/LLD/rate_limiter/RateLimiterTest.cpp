// addon 1: multiple users id

#include "./RateLimiter.cpp"

using namespace std;

namespace RateLimiter
{
    void getInput(int &input)
    {
        cout << "Enter input" << endl;
        cout << "Rate Limiter Create or update :  1" << endl;
        cout << "Check Req :  2" << endl;
        cout << "Make req: 3" << endl;
        cout << "Quit: -1" << endl;
        cin >> input;
    }

    void testSlidingWindow()
    {
        RateLimiterManager rl;
        int input = 0;
        //getInput(input);
        int ts = -1;
        SlidingWindowStrategyConfig config1 = {"Anirban",StrategyType::Sliding,5,5},
            config2 =  {"Bob",StrategyType::Sliding,5,6};
        
        cout<<rl.addUserStrategy(config1.userId, config1)<<endl;
        cout<<rl.addUserStrategy(config1.userId, config1)<<endl;
        cout<<rl.addUserStrategy(config2.userId, config2)<<endl;
        
        for(auto i=0;i<6;i++){
            cout<<"Anirban: "<<rl.addReq("Anirban",0)<<endl;
            cout<<"Bob: "<<rl.addReq("Bob",0)<<endl;
        }
    }
}

int main()
{
    RateLimiter::testSlidingWindow();
    return 0;
}
