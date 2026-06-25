/// Severity: sev0
// Date: 21Jun26
// LC: 2458
// Where I failed: optimize to O(n)
// Pattern: depth + height decomposition
// Notes: additional_notes


/*

have cousins of depth 
sort the cousins by height reverse
depth at i with height j == depth at i+1 with height j-1 == same total height == i+j
when remove a node :
    if last one = beyond this node, no other node in tree whichis at depth >=i so effective heihgt==depth_i-1;
    if max one : second min+depth
    else depth+ max height
*/
