Problem: Implement a BFS Website Crawler (with Error Handling and Retries)
Given a starting URL start_url, implement a crawler that fetches web pages, extracts links, and traverses the site in BFS (breadth-first) order starting from start_url.

Requirements
Traversal:

Traverse pages reachable from start_url using BFS.
Deduplicate visited URLs to avoid repeated fetching.
URL handling (basic normalization):

Resolve relative links into absolute URLs using the current page URL as the base.
Remove URL fragments (e.g., treat https://a.com/p#section as https://a.com/p).
Deduplicate based on the normalized URL.
Scope restriction:

Only crawl links with the same host as start_url. Ignore other hosts.
HTTP fetching and error handling:

Issue an HTTP GET for each URL.
Handle network errors (timeouts, connection failures, etc.) and non-2xx responses.
Retry policy:

Retry failed requests up to max_retries times.
Wait backoff_ms milliseconds before each retry (fixed backoff is fine).
Stopping conditions:

Stop when the number of successfully fetched pages reaches max_pages, or
when the BFS queue becomes empty.
Input
Read from stdin:

Line 1: start_url
Line 2: two integers max_pages max_retries
Line 3: integer backoff_ms
Output
Print:

First line: an integer, the number of successfully fetched pages (HTTP 2xx and content retrieved).
Then, in the BFS-success order, print one normalized URL per line.
Constraints
1 <= max_pages <= 1000
0 <= max_retries <= 5
0 <= backoff_ms <= 5000
Each HTML page size is at most 2MB
Only parse links from HTML <a href="..."> (regex or an HTML parser is acceptable)
Example
Input:

https://example.com
3 2
100
Output (example, not unique):

3
https://example.com
https://example.com/about
https://example.com/contact
Example
Input
https://example.com
3 2
100
Output
3
https://example.com
https://example.com/about
https://example.com/contact