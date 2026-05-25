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
