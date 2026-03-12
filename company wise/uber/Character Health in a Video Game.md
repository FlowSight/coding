Note - Feel free to checkout the srce image below for the original statement :)

Imagine a magical adventure where you guide a brave character through a series of enchanting levels. The character begins this journey with an initial health value, a precious resource that fluctuates as they encounter various challenges in each level.

As you progress through these levels, each experience, whether it's a thrilling battle or a rewarding discovery, influences the character’s health. These changes are captured in an array of integers, deltas, where the value at each level determines how much the character's health increases or decreases.

However, there's a twist! If the character's health ever falls below 0, it's lovingly set to 0, ensuring they never completely lose hope. On the other hand, if their health exceeds 100, it gently settles back down to 100, keeping them from becoming too invincible.

Your quest is to guide this character through all the levels, and at the end, discover their final health value after all these adventures. The goal isn’t necessarily to find the most cunning solution, but rather one that reliably determines the character's final health without taking too long.

So, with that in mind, how will your character's health fare by the end of their journey? Let's find out!

Constraints: ``

Example
Input
initialHealth = 12
deltas = [-4, -12, 6, 2]
Output
8