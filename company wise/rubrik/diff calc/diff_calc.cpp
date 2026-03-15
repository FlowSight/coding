// 2月份的rubrik店面：
// 题目是之前地里出过的一个变种：
// Write a program to display how file1 is changed to file2, line by line,
// like the unix `diff` tool or a code review tool.
// * If a line is deleted, prefix it with "- ";
// * If a line is inserted, prefix it with "+ ";
// * if a line is unchanged, no prefix is needed, just print as is.
// For example:
// File1 -
// A
// B
// C
// D
// E
// File2 -
// B
// C
// X
// E
// Y
// One possible result is
// - A
// B
// C
// + X
// - D
// E
// + Y
// Input: Two lists of strings representing files. Each element of the list is a line
// - Ex: ['A', 'B', 'C', 'D', 'E'], ['B', 'C', 'X', 'E', 'Y']
// Print the result to std output.
// Hint: Minimum Editing Distance
// edit_dist(a[1:n], b[1:m]) = edit_dist(a[1:n-1], b[1:m-1]), if a[n] == b[m];
// min(edit_dist(a[1:n-1], b[1:m]), edit_dist(a[1:n], b[1:m-1])) + 1, otherwise.

// 楼主太菜了，之前知道大概是用LCS（longest common sequence）做，但输出longest sequence path还是不太会，然后之后根据这个结果，在做string 操作。二维DP当时也没复习，瞎写了一通。妥妥挂了，之前没想到LCS的时候，想了一个naive 用map 存 same charanter list，说了10min，面试官才说不对，然后就也不提示，就看着我在那表演。反正面试体验最差的一家公司了。