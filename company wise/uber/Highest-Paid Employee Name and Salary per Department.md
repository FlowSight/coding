Given a database with a table named Employees having the following structure:

employee_id (Integer): employee ID, primary key.
name (String): employee name.
department (String): employee department.
salary (Integer): employee salary.
Write an SQL query to find the name and salary of the highest-paid employee in each department. If multiple employees have the same maximum salary, display any one of them.

-- Expected Output Example:
-- +--------------+-------------+
-- | department   | name        |
-- +--------------+-------------+
-- | Engineering  | Alice       |
-- | HR           | Bob         |
-- | Sales        | Charlie     |
-- +--------------+-------------+
Example
Input
员工信息： 1. (1, 'Alice', 'Engineering', 90000) 2. (2, 'Bob', 'HR', 80000) 3. (3, 'Charlie', 'Sales', 85000) 4. (4, 'David', 'Engineering', 85000) 5. (5, 'Eve', 'HR', 80000)