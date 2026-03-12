Given a 2D strictly convex function and four coordinate values: xlb, xub, ylb, yub, you need to find the minimum value of the function within this range. First, write a function to solve the minimization problem for a 1D strictly convex function, and then apply it to the 2D case. Provide a complete problem description, including function signature, boundary conditions, and test cases.

Example
Input
{"f": "lambda x, y: (x-1)**2 + (y-1)**2", "xlb": 0, "xub": 2, "ylb": 0, "yub": 2}