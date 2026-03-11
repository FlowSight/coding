The developers are trying to optimize their horizontal pod autoscaler for their micro-services. There are n micro-services where the number of pods for the ith micro-service is pods[i]. According to traffic, the number of pods of a service can increase or decrease. Also, at specific times when there is expected traffic, all services with fewer than x pods are assigned x pods. There is an event log of size m, which is described as a 2D array logs where logs[i] is an array of integers of size = 3. The interpretation of these logs are shown.

[1, p, x]: the number of pods of the pth micro-service is changed to x (1 <= p ≤ n).
[2, -1, x]: all the micro-services whose number of pods is less than x are changed to x.
Find the resulting number of pods for the micro-services.

Function Description

Complete the function findPodCount in the editor below.

findPodCount has the following parameters:

int pods[n]: the number of pods for the micro-services
int logs[m][3]: the event log of the horizontal pod autoscaler
Returns

int[n]: the # element represents the final pod count of the mth micro-service

Constraints: :)

Example
Input
pods = [2, 4, 1, 4]
logs = [[1, 2, 30], [1, 3, 4], [2, -1, 10]]
Output
[10, 30, 10, 10]