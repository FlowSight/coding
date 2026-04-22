Given a set of firewall rules in CIDR format where each rule either allows or denies specific IP ranges, determine if an input IP address passes through the rules. If an IP address matches multiple rules, the first matching rule should be applied. Implement a program to process these rules and determine if the IP passes. Consider various test cases, such as no matches, multiple matches, and edge cases in rules.

Example
Input
2
192.168.1.0/24 allow
10.0.0.0/8 deny
192.168.1.100