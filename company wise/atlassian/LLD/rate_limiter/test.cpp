// addon 1: multiple users id

#include "./RateLimiterManager.cpp"

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
        getInput(input);
        int ts = -1;
        rl.addUserStrategy("Anirban",{StrategyType::Sliding,5});
        rl.addUserStrategy("Bob",{StrategyType::Sliding,5});
        for(auto i=0;i<6;i++){
            cout<<"Anirban: "<<rl.addReq("Anirban",i)<<endl;
            cout<<"Bob: "<<rl.addReq("Bob",i)<<endl;
        }
    }
}

int main()
{
    RateLimiter::testSlidingWindow();
    return 0;
}
