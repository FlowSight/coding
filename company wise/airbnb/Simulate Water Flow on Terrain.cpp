You are given an array like [5, 4, 3, 2, 1, 3, 4, 0, 3, 4]. Each number represents the height of a column at that index.

Part 1: Print a terrain where each number represents the height of a column at that index.

Part 2: Imagine we pour a certain amount of water at a certain column. The water can flow in whichever direction makes sense. Print the terrain after all the water has fallen.

For example, after calling dumpWater(terrain, waterAmount=8, column=1), the rendered result should be:

+
++[url=http://WWWW+]WWWW+[/url] +
+++WW++ ++
++++W++ ++
+++++++W++
++++++++++ <--- base layer
Example
Input
5 4 3 2 1 3 4 0 3 4
8
1