Given a 2D terrain map with various heights, water drops from a specific point and can flow from higher to lower heights. Identify all points that get wet. Provide function signature, test cases, and data constraints.

Requirements
Implement a function def find_wet_points(terrain: List[List[int]], water_source: Tuple[int, int]) -> List[Tuple[int, int]]:
terrain is a 2D list representing the heights of the terrain.
water_source is a tuple representing the initial drop point of water.
Return a list of all wet points the water flows through.
Input/Output Example
Example 1: Input: terrain = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]], water_source = (0, 0) Output: [(0, 0), (1, 0), (0, 1)]
Data Constraints
terrain size: 1 <= m, n <= 200
Height constraints: 0 <= terrain[i][j] <= 100000
Example
Input
terrain = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]], water_source = (0, 0)