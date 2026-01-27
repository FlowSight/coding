// There are two lists of size n- developmentTime and IntegrationTime. Any feature can be either implemented by development or by integration. While development of multiple features can happen concurrently by multiple developers, integration of features can only be sequential and can only be done by the team lead. Return the least number of hours to implement all the n features. Assume, there are more than n developers.

// Eg: 1- developmentTime = {3,4,5,9} integrationTime = {3,2,5,5}
// O/p - 5
// First 3 are developed and take 5 hours and in the mean while, integration of last one takes place

// 2 - developmentTime = {8,10,6,7} integrationTime = {1,2,2,1}
// o/p- 6
// Sum of all integrations < minimum development time.
//sev0