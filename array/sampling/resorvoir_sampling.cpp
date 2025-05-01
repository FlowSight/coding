// An efficient program to randomly select
// k items from a stream of items 
#include <bits/stdc++.h>
#include <time.h> 
using namespace std; 

// A utility function to print an array 
void printArray(int stream[], int n) 
{ 
	for (int i = 0; i < n; i++) 
		cout << stream[i] << " "; 
	cout << endl;
} 

// A function to randomly select 
// k items from stream[0..n-1]. 
void selectKItems(int stream[], int n, int k) 
{ 
	int i; 
	int reservoir[k]; 
	for (i = 0; i < k; i++) 
		reservoir[i] = stream[i]; 

	// Iterate from the (k+1)th element to nth element 
	for (; i < n; i++) 
	{ 
		int j = rand() % (i + 1); 
		if (j < k) 
		reservoir[j] = stream[i]; 
	} 
} 


// proof:

// Case 1: For last n-k stream items, i.e., for stream[i] where k <= i < n 
// For every such stream item stream[i], we pick a random index from 0 to i and if the picked index is one of the first k indexes, we replace the element at picked index with stream[i]
// To simplify the proof, let us first consider the last item. The probability that the last item is in final reservoir = The probability that one of the first k indexes is picked for last item = k/n (the probability of picking one of the k items from a list of size n)
// Let us now consider the second last item. The probability that the second last item is in final reservoir[] = [Probability that one of the first k indexes is picked in iteration for stream[n-2]] X [Probability that the index picked in iteration for stream[n-1] 
    // is not same as index picked for stream[n-2] ] = [k/(n-1)]*[(n-1)/n] = k/n.
// Similarly, we can consider other items for all stream items from stream[n-1] to stream[k] and generalize the proof.

// Case 2: For first k stream items, i.e., for stream[i] where 0 <= i < k 
// The first k items are initially copied to reservoir[] and may be removed later in iterations for stream[k] to stream[n]. 
// The probability that an item from stream[0..k-1] is in final array = Probability that the item is not picked when items stream[k], stream[k+1], …. stream[n-1] are considered = [k/(k+1)] x [(k+1)/(k+2)] x [(k+2)/(k+3)] x … x [(n-1)/n] = k/n

