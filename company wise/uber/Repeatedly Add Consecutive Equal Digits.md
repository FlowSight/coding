**See the Image Source section at the very bottom of the page for the original problem statement **

Imagine you're given a string made entirely of digits, and your goal is to transform it by repeatedly applying a special operation whenever there are consecutive identical digits. Here's how it works: if a number has repeated digits, you replace each group of consecutive digits with their sum. For example, the number "999433" would become "2746" because 9 + 9 + 9 equals 27, and 3 + 3 equals 6. You keep doing this until there are no consecutive digits left. For instance, "44488366664" would first transform to "12163244." Keep applying this process until the string no longer has any repeating digits, and that's your final result. The challenge here is to find an approach that gets this done efficiently, though it doesn't need to be the most optimal one.

** Appreciation to Charlotte baby **

Constraints:

Example
Input
number = "999433"
Output
"2746"