#include <iostream>
#include <cmath>
using namespace std;

// --- Server APIs (provided via socket, simulated here for testing) ---
// In real interview: these are black-box calls over a socket connection.
static double serverSpeed = 0.0;
static double serverAccel = 0.0;

pair<double, double> getStatus() {
    // Server returns current speed and acceleration
    return {serverSpeed, serverAccel};
}

void setStatus(double acceleration) {
    // Server sets the car's acceleration
    serverAccel = acceleration;
}

// Server simulation step (we don't write this — server does it internally)
// Some unknown resistance model makes speed stabilize for a given accel.
void serverTick() {
    // Unknown internals — could be air resistance, friction, anything
    double resistance = 0.05 * serverSpeed;
    serverSpeed += (serverAccel - resistance) * 0.1;
    if (serverSpeed < 0) serverSpeed = 0;
}

// --- Our solution ---

/*
 * Key insight: We don't know the server's physics model.
 * We just observe speed and adjust acceleration.
 *
 * The server has some unknown resistance that makes speed stabilize
 * for a given acceleration. Pure P-control has steady-state error
 * because as error→0, our acceleration→0, but the server needs
 * non-zero acceleration to maintain speed against its resistance.
 *
 * Fix: Add integral term (PI control). The integral accumulates
 * past error and provides the "baseline" acceleration needed
 * to maintain target speed — without knowing the physics model.
 */
void stabilizeAt(double targetSpeed) {
    double threshold = 0.1;
    double Kp = 0.5;
    double Ki = 0.05;

    double integral = 0.0;

    for (int i = 0; i < 2000; i++) {
        auto [speed, accel] = getStatus();

        if (abs(speed - targetSpeed) < threshold) {
            cout << "Stabilized at speed " << speed
                 << " after " << i << " calls" << endl;
            return;
        }

        double error = targetSpeed - speed;
        integral += error;
        // Clamp integral to avoid windup
        integral = max(-100.0, min(100.0, integral));

        double newAccel = Kp * error + Ki * integral;
        setStatus(newAccel);

        serverTick(); // server processes internally (we just wait/poll)
    }

    auto [speed, accel] = getStatus();
    cout << "Max iterations. Speed: " << speed << endl;
}

int main() {
    stabilizeAt(29.0);
    return 0;
}

