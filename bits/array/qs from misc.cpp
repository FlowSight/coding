
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Q:
have an array of n elements.
need to choose pairs (arr[i],arr[j]) so that arr[i]*arr[j] is not square.
you can change k elements, so that such pairs are maximized.


transform : num = p1^i*p2^j => p1^(i%2)*p2^j(j%2)
2=2=2^1
50=2*5^2=2^1
now make map of each such converted numbers, key is converted number, val is frequency.
now qs reduces to finding max no of pairs where both elements are distinct ...and add k in the end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
