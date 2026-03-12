Design and implement an algorithm that accurately identifies outliers in a given experimental data set. Users can define outliers, such as points exceeding two standard deviations from the mean, or extreme values based on quartiles. Input: An array of integers representing the experimental data set, and a string parameter defining the outlier standard. Output: An array of integers representing the data points identified as outliers. Data Scale: The data set does not exceed 10^5 data points. Test Cases:

Input: [1, 2, 3, 100, 2, 3, 1, 3, 2, 1000], 'std'

Input: [1, 2, 3, 4, 100, 5, 6, 7, 100, 8, 9], 'quartile'

Input: [10, 20, 30, 40, 50, 60], 'std'

Input: [100, 200, 300, 400, 500], 'quartile'

Input: [1, 1, 1, 1, 50, 1, 1, 1, 100], 'std'

Example
Input
[1, 2, 3, 100, 2, 3, 1, 3, 2, 1000]
std