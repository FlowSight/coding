There's a car simulator on a server. The task is to connect using a socket and call two APIs: 
`getStatus()` to get the current speed and acceleration, and 
`setStatus(acceleration)` to modify the car's acceleration. 
For each acceleration, the car will continuously accelerate until it reaches a stable speed.
 The problem is to write a wrapper function to stabilize the car's speed at 29 mph. 

 
  
   The acceleration formula is Vt^2 - Vo^2 = 2as. For an object undergoing uniform acceleration over a distance S, the sum of the initial velocities minus the sum of the initial velocities equals twice the distance multiplied by the acceleration.
    Va = (Vo + Vt)/2 = V(t/2). The average velocity is equal to the average of the initial velocity and the velocity at time t/2, which is also equal to the instantaneous velocity at time t/2. 
    S2 - S1 = at^2. 
    An object undergoes uniformly accelerated linear motion, and the distances it travels in two consecutive and equal time intervals are S1 and S2 respectively. The difference between the distances at the two ends is equal to at^2.
