Design a Timer class with the following methods:

private void setTimer(int timestamp): Sets a timer, which calls handleTimer when it expires. If called again, it overrides the previous timers, meaning only one timer is kept at any time.

private void handleTimer(): Handles the timer expiration event.

private getCurrentTime(): Returns the current time.

public void setNewTimer(int timestamp): Allows the user to set multiple timers.

Only setNewTimer can be called by the user.

Implement these four methods in the Timer class, and provide sample code for setNewTimer.

Example
Input
5