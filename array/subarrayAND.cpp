// Q : find subarry and closest to k..or exactly k
// 2 approaches:
//     IDEA : anding with next element can only set a bit 1-> 0.not 0->1
// 1. sliding window
//     keep doing r++ until AND comes below k
//     keep doing l-- until AND crosses k
// 2. set
//     (1 nos) i.e. 1110 or 1101 or 1011 or 0111
//     (1010, 1011) or (0111,0110) or (1101,1100) or (1110) or (...) ... // this is basically at each step one more bit is set to 0, so we have 2 nos one with (1 0, another with 2 0s)
//     // so in next step we will have 1 0, 2 0s, 3 0s,
//     // next 1 0s,2 0s, 3 0s, 4 0s,

