# Math Patterns

## 1. Digit DP
- Count numbers in [0, N] satisfying some digit-based property
- State: position, tight constraint, started flag, + problem-specific state
- Use: count of digit 1 in [1..N], numbers with non-repeating digits, numbers divisible by K

## 2. Modular Arithmetic
- (a + b) % m = ((a%m) + (b%m)) % m
- (a * b) % m = ((a%m) * (b%m)) % m
- Modular inverse: a^(-1) mod p = a^(p-2) mod p (Fermat's, p prime)
- Use nCr mod p via precomputed factorials + inverse factorials
- **Gotcha**: subtraction needs +mod before %mod to avoid negatives
- **Gotcha**: (a % mod) / b ≠ (a/b) % mod — division under mod requires modular inverse, never plain /
- **Gotcha**: recursive mypow with memoization only works if base is constant across calls. For different bases (e.g., computing inverse of 2, 3, 4...), use iterative pow or precompute inverses.

## 3. GCD / LCM
- Euclidean: gcd(a,b) = gcd(b, a%b), base gcd(a,0) = a
- lcm(a,b) = a / gcd(a,b) * b (divide first to avoid overflow)
- Extended GCD: find x,y s.t. ax + by = gcd(a,b)
    - Use: Bezout's identity, modular inverse when gcd=1
- if (gcd(a,k) * gcd(b,k))%k == 0, then (a*b)%k = 0 lc 2183

## 4. Sieve of Eratosthenes
- O(n log log n) to find all primes up to n
- Linear sieve: O(n), each composite marked by its smallest prime factor
- Segmented sieve for large ranges [L, R]
- Use: prime factorization, counting primes, Euler's totient

## 5. Fast Exponentiation
- a^n in O(log n): square-and-multiply
- Matrix exponentiation: solve linear recurrences in O(k^3 log n)
- Use: Fibonacci, power mod, counting paths of length n in graph

## 6. Combinatorics
- nCr = n! / (r! * (n-r)!) — precompute factorials for O(1) queries
- Pascal's triangle: nCr = (n-1)C(r-1) + (n-1)Cr
- Stars and bars: distributing n identical items into k bins = C(n+k-1, k-1)
- Inclusion-exclusion: |A∪B∪C| = |A|+|B|+|C| - |A∩B| - ... + |A∩B∩C|
- Catalan number: C(n) = C(2n,n)/(n+1) — valid parentheses, BSTs, triangulations

## 7. Number Theory
- Euler's totient φ(n): count of integers ≤ n coprime to n
- φ(p^k) = p^k - p^(k-1); φ is multiplicative for coprime
- Chinese Remainder Theorem: solve system of modular equations
- Use: RSA, order finding, counting coprime pairs

## 8. Geometry Basics
- Cross product: orientation test (left/right/collinear)
- Convex hull: Graham scan O(n log n) or Andrew's monotone chain
- Line intersection, point-in-polygon (ray casting)
- Use: closest pair of points, sweep line problems

## 9. Optimal Splitting into 3s (AM-GM Optimization)
- To maximize the product of positive integers summing to n, break into as many 3s as possible
- Why 3: maximizing x^(1/x) over reals peaks near x=e≈2.718; among integers, 3 beats 2 for the same sum (2×2×2=8 < 3×3=9 for sum 6)
- Handle n%3 remainder specially — this is the actual trick, not just "divide by 3":
    - remainder 0: use all 3s, nothing extra
    - remainder 1: DON'T leave a trailing 1 (wasteful: 3×1=3 < 2×2=4) — combine the last 3 with the +1 to make a 4 (equivalently, use one 4 = 2×2 instead of a 3 and a 1)
    - remainder 2: use as-is (a single trailing 2 is fine, 2 > nothing)
- Implementation trick: loop `while(n>4)` (NOT `n>3`) peeling off 3s — this naturally leaves a final chunk of 2, 3, or 4 (never 1), avoiding a separate remainder-case branch
- Use: LC 343 (Integer Break) — maximize product of parts summing to n

## 10. Bucket Sort / Pigeonhole Principle
- Core idea: prove the answer must be ≥ some computable average, then design buckets sized so "small" differences are provably below that average — you then only need to check "large" (across-bucket) differences, never within-bucket ones
- Worked example (LC 164, Maximum Gap):
    - n numbers sorted have n-1 gaps summing to (max-min) → average gap = (max-min)/(n-1)
    - Since it's an average, the TRUE max gap ≥ this average (can't all be below average) — this is the pigeonhole step
    - Set bucketSize = floor((max-min)/(n-1)); every bucket's width is ≤ average gap, so any two numbers in the SAME bucket are ≤ bucketSize apart, i.e. ≤ average ≤ true max gap
    - Conclusion: within-bucket gaps can NEVER be the answer — only track bucketMin[]/bucketMax[] per bucket, then scan across adjacent non-empty buckets (min of next − max of prev) for the actual answer
    - This is why the algorithm can safely ignore what happens to elements inside the same bucket — it's not an approximation, it's mathematically guaranteed those gaps are too small
- **Gotcha**: bucketSize can be 0 if max==min or n==1 — guard with `max(1, ...)` and handle n<2 as a trivial base case (answer 0)
- Use: LC 164 (Maximum Gap), radix-sort-adjacent problems, any "min/max gap after sort in O(n)" question
