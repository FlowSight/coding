Implement a linear regression model using backpropagation to update model parameters. The input consists of a 2D array X and a 1D array y representing the dataset, where each row of X is a sample and each column is a feature, with y being the corresponding labels. The output should be the predicted results and the trained model parameters.

Input
A 2D array X with dimensions m x n, where m is the number of samples and n is the number of features.
A 1D array y of size m, representing the label for each sample.
A float learning_rate representing the learning rate.
An integer epochs representing the number of training iterations.
Output
A 1D array predictions, representing the results of the model prediction.
A 1D array weights and a float bias, representing the trained model parameters.
Example
Input:
X = [[1, 2], [3, 4], [5, 6]]
y = [3, 7, 11]
learning_rate = 0.01
epochs = 1000
Output:
predictions = [3.0, 7.0, 11.0]
weights = [1.0, 1.0]
bias = 0.0
Data Limits
m and n are both up to 1000.
Example
Input
3
2
1 2
3 4
5 6
3 7 11
0.01
1000