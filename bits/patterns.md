# Bit Manipulation Patterns

## 1. Basic Operations
- Set bit i: x | (1 << i)
- Clear bit i: x & ~(1 << i)
- Toggle bit i: x ^ (1 << i)
- Check bit i: (x >> i) & 1
- Lowest set bit: x & (-x)
- Clear lowest set bit: x & (x-1)
- Count set bits: __builtin_popcount(x)

## 2. XOR Properties
- a ^ a = 0, a ^ 0 = a
- XOR is associative and commutative
- Single number: XOR all elements, duplicates cancel
- Two unique numbers: XOR all → get diff bits, partition by any set bit
- Use: single number I/II/III, missing number, find duplicate

## 3. Subset Enumeration with Bitmask
- All subsets of n elements: iterate mask from 0 to (1<<n)-1
- All subsets of a mask: `for(s=mask; s>0; s=(s-1)&mask)`
- Use: DP over subsets, SOS DP, TSP

## 4. Power of Two Checks
- x is power of 2: x > 0 && (x & (x-1)) == 0
- Next power of 2: bit_ceil(x) or manual with shifts
- Use: partition, memory alignment

## 5. Counting Bits / Ranges
- Count bits from 0 to n: dp[i] = dp[i>>1] + (i&1)
- Bitwise AND of range [m,n]: shift both right until equal, shift back
- Use: counting bits (LC 338), range bitwise AND (LC 201)

## 6. Bit Tricks
- Swap without temp: a^=b; b^=a; a^=b
- Absolute value: (x ^ (x>>31)) - (x>>31)
- Sign of product without overflow: XOR sign bits
- Divide by 2: x >> 1 (arithmetic shift for signed)

## Key Gotchas
- Use `1LL << i` for i >= 31 (avoid 32-bit overflow)
- Signed right shift is implementation-defined — prefer unsigned for bit manipulation
- XOR does NOT preserve ordering — can't compare magnitudes
