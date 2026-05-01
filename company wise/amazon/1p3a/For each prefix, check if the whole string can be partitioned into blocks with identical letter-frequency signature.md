Problem
Given a string packages consisting only of uppercase letters A-Z (length L). For each prefix packages[0:i] where 1 <= i <= L, determine whether the whole string packages can be partitioned into consecutive blocks such that:

Every block has length i;
The 26-letter frequency vector (signature) of each block is exactly the same as the prefix's signature.
For each prefix, output 0 if it is valid, otherwise output 1 (equivalently, output an array/string of length L over {0,1}).

Notes
A signature is the 26-dimensional vector cnt['A']..cnt['Z'].
The string must be split into an integer number of blocks, so L % i == 0 is required.
Constraints
1 <= L <= 2*10^5
Characters are A-Z
Sample Tests
packages="ABAB" -> 1 0 1 0
packages="AAAA" -> 0 0 0 0
packages="ABCD" -> 1 1 1 0
packages="AABAAB" -> 0 1 0 1 1 0
packages="ABCABCABC" -> 1 1 0 1 1 0 1 1 0
Example
Input
ABAB
Output
1 0 1 0

static boolean isValid(String s, int blockSize) {
    int L = s.length();
    if (L % blockSize != 0) return false;
    
    int[] prefixFreq = getFreq(s, 0, blockSize);
    
    for (int j = blockSize; j < L; j += blockSize) {
        int[] blockFreq = getFreq(s, j, blockSize);
        if (!areFreqEqual(prefixFreq, blockFreq)) {
            return false;
        }
    }
    return true;
}