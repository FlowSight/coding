HTTP Request Language Matching
Problem Summary
You are building a system that shows content to users in their preferred language. When a browser sends an HTTP request, it sends an Accept-Language header. This header lists the languages the user wants, in order of preference.

Your server only has a specific list of languages available. You need to figure out which of the user's requested languages you can actually provide. You must return a list of matching languages, keeping the user's preference order.

This problem has four parts, starting simple and getting harder:

Exact Matches: Match strings exactly (e.g., "en-US" only matches "en-US").
Prefix Matches: Allow short codes to match specific regions (e.g., "en" matches "en-US").
Wildcards: Handle the * symbol, which means "any other language."
Quality Scores: specific preferences using scores like "q=0.8".
Input Details
Your function takes two inputs:

Accept-Language Header (string): A list of language tags separated by commas.
Example: "en-US, fr-CA, fr-FR"
Supported Languages (list/set): The languages your server has.
Example: ["en-US", "fr-FR", "es-ES"]
Output Details
Return a list of language tags that:

Are in the user's header (or match the rules).
Are supported by your server.
The list must follow the user's order of preference.

Part 1: Exact Matches
Problem Requirements
Write a function called parse_accept_language(accept_header, supported_languages). It should find the languages that are in both the header and the supported list.

For now, only count exact matches. "en-US" matches "en-US", but it does not match "en".

Examples
Example 1:

parse_accept_language(
    "en-US, fr-CA, fr-FR",
    ["fr-FR", "en-US"]
)
# Returns: ["en-US", "fr-FR"]
# en-US is first in the header, so it is first here.
# fr-FR is third in the header.
# fr-CA is not in the supported list.
Example 2:

parse_accept_language(
    "fr-CA, fr-FR",
    ["en-US", "fr-FR"]
)
# Returns: ["fr-FR"]
# Only fr-FR exists in both lists.
Example 3:

parse_accept_language(
    "en-US",
    ["en-US", "fr-CA"]
)
# Returns: ["en-US"]
Key Tasks
Split the header string into separate language tags.
Check if each tag is in the supported list.
Keep the order from the header.
Return only the matches.
Questions to Ask
Does case matter (e.g., "en-us" vs "en-US")?
What if the header string is messy or broken?
Should we remove spaces around the tags?
What do we return if nothing matches?
Part 2: Prefix Matching
Problem Requirements
Update your function to handle "generic" language codes. These are codes without a region, like "en" or "fr".

A generic tag like "en" should match any English variation your server has (like "en-US" or "en-GB").

Language tags usually look like language-REGION:

Language: Before the hyphen (e.g., "en").
Region: After the hyphen (e.g., "US").
Rules
Exact matches come first: If the user asks for "en-US", look for that exact string first.
Generics match all variants: "en" matches "en-US", "en-GB", etc.
No duplicates: If a language is already matched, do not list it again.
Examples
Example 1:

parse_accept_language(
    "en",
    ["en-US", "fr-CA", "fr-FR"]
)
# Returns: ["en-US"]
# "en" matches the supported "en-US".
Example 2:

parse_accept_language(
    "fr",
    ["en-US", "fr-CA", "fr-FR"]
)
# Returns: ["fr-CA", "fr-FR"]
# "fr" matches both French versions.
Example 3:

parse_accept_language(
    "fr-FR, fr",
    ["en-US", "fr-CA", "fr-FR"]
)
# Returns: ["fr-FR", "fr-CA"]
# fr-FR is an exact match, so it comes first.
# "fr" matches fr-CA. (fr-FR is skipped because it's already used).
Key Tasks
Split tags by the hyphen (-) to get the main language code.
Match generic codes to all regional versions in your supported list.
Do not return the same language twice.
Keep the header's order.
Questions to Ask
If we match "en", in what order should "en-US" and "en-GB" appear?
Should "en" match complex tags like "zh-Hans-CN"?
Part 3: Handling Wildcards
Problem Requirements
The header might contain an asterisk (*). This is a wildcard. It means "any language I haven't mentioned yet."

When you see a *, you should include all supported languages that haven't been matched by previous rules.

Rules
Read the header from left to right.
Keep a list of languages you have already used.
If you see *, add every supported language that isn't on your used list.
Place these languages where the * was found.
Examples
Example 1:

parse_accept_language(
    "en-US, *",
    ["en-US", "fr-CA", "fr-FR"]
)
# Returns: ["en-US", "fr-CA", "fr-FR"]
# en-US matches exactly.
# * grabs everything else (fr-CA and fr-FR).
Example 2:

parse_accept_language(
    "fr-FR, fr, *",
    ["en-US", "fr-CA", "fr-FR"]
)
# Returns: ["fr-FR", "fr-CA", "en-US"]
# fr-FR matches exactly.
# "fr" matches fr-CA.
# * grabs the last one: en-US.
Example 3:

parse_accept_language(
    "*",
    ["en-US", "fr-FR", "es-ES"]
)
# Returns: ["en-US", "fr-FR", "es-ES"]
# * matches everything.
Key Tasks
Remember which languages are already matched.
When you hit *, loop through supported languages and add any missing ones.
Keep the order consistent.
Part 4: Quality Scores (q-factors)
Problem Requirements
Sometimes the header includes "q-factors". These are numbers between 0.0 and 1.0 that tell you how much the user wants a language.

Higher number: Stronger preference.
No number: Defaults to 1.0 (highest).
0: Means "I do not want this."
The format looks like language;q=value (e.g., "en-US;q=0.8").

You must parse these numbers and sort the final list by score (highest to lowest).

Rules
If there is no q, assume it is 1.0.
If q=0, put it last or ignore it.
If scores are equal, keep the original order (Stable Sort).
The wildcard * can also have a score.
Examples
Example 1:

parse_accept_language(
    "fr-FR;q=1, fr-CA;q=0, fr;q=0.5",
    ["fr-FR", "fr-CA", "fr-BG"]
)
# Returns: ["fr-FR", "fr-BG", "fr-CA"]
# fr-FR: q=1.0 (Highest)
# "fr" matches fr-BG: q=0.5 (Middle)
# fr-CA: q=0 (Lowest)
Example 2:

parse_accept_language(
    "fr-FR;q=1, fr-CA;q=0, *;q=0.5",
    ["fr-FR", "fr-CA", "fr-BG", "en-US"]
)
# Returns: ["fr-FR", "fr-BG", "en-US", "fr-CA"]
# fr-FR: q=1.0
# * matches fr-BG and en-US: q=0.5
# fr-CA: q=0
Example 3:

parse_accept_language(
    "en;q=0.8, fr;q=0.9, de;q=0.7",
    ["en-US", "fr-FR", "de-DE"]
)
# Returns: ["fr-FR", "en-US", "de-DE"]
# Sorted by score: 0.9, 0.8, 0.7
Key Tasks
Extract the q=value part from the string.
Assign 1.0 if no value exists.
Sort the result list by score (descending).
Use a stable sort (Python's sort is stable by default).
Questions to Ask
Should we completely remove q=0 languages or just put them last?
How many decimal places can the score have?
What if the score is invalid (like q=5)?
How to Solve It
Part 1: Solution (Exact Matches)
Plan:

Split the header string by commas.
Clean up spaces around the words.
Turn the supported languages list into a Set (for fast O(1) checking).
Loop through the requested languages. If one is in the Set, add it to the result.
Complexity:

Time: O(n + m) (n = requested items, m = supported items).
Space: O(m) to store the Set.
Code:

def parse_accept_language(accept_header, supported_languages):
    # Get requested languages from header
    requested = [lang.strip() for lang in accept_header.split(',')]

    # Use a set for fast lookup
    supported_set = set(supported_languages)

    # Only keep languages that are supported
    result = []
    for lang in requested:
        if lang in supported_set:
            result.append(lang)

    return result
Edge Cases:

Header is empty.
Supported list is empty.
Extra spaces or commas.
Part 2: Solution (Prefix Matches)
Plan:

Get the requested languages.
For every request:
First, check if it matches a supported language exactly.
If not, check if it is a generic code (no hyphen).
If generic, find all supported languages that start with that code.
Use a matched Set to make sure we don't add the same language twice.
Key Detail: A generic code like "en" should check if a supported language starts with "en-".

Code:

def parse_accept_language(accept_header, supported_languages):
    requested = [lang.strip() for lang in accept_header.split(',')]
    supported_set = set(supported_languages)

    result = []
    matched = set()

    for req_lang in requested:
        # 1. Try exact match first
        if req_lang in supported_set and req_lang not in matched:
            result.append(req_lang)
            matched.add(req_lang)
        # 2. Try generic match (if no region code)
        elif '-' not in req_lang:
            # Find all supported languages starting with this prefix
            for sup_lang in supported_languages:
                if sup_lang.startswith(req_lang + '-') and sup_lang not in matched:
                    result.append(sup_lang)
                    matched.add(sup_lang)

    return result
Part 3: Solution (Wildcards)
Plan:

Add a check for *.
If we find *, loop through all supported languages.
Add any supported language that is not in our matched Set yet.
Code:

def parse_accept_language(accept_header, supported_languages):
    requested = [lang.strip() for lang in accept_header.split(',')]
    supported_set = set(supported_languages)

    result = []
    matched = set()

    for req_lang in requested:
        if req_lang == '*':
            # Wildcard: add everything left
            for sup_lang in supported_languages:
                if sup_lang not in matched:
                    result.append(sup_lang)
                    matched.add(sup_lang)
        elif req_lang in supported_set and req_lang not in matched:
            # Exact match
            result.append(req_lang)
            matched.add(req_lang)
        elif '-' not in req_lang:
            # Generic match
            for sup_lang in supported_languages:
                if sup_lang.startswith(req_lang + '-') and sup_lang not in matched:
                    result.append(sup_lang)
                    matched.add(sup_lang)

    return result
Part 4: Solution (Quality Scores)
Plan:

Write a helper function to separate the name and the score (q=).
Store matches as a pair: (language_name, score).
Perform the matching logic (Exact, Generic, Wildcard) just like before, but attach the score to every match found.
At the end, sort the list by score (highest first).
Return just the language names.
Code:

def parse_accept_language(accept_header, supported_languages):
    # Parse requested languages and their scores
    requested = []
    for entry in accept_header.split(','):
        lang, q_factor = parse_language_with_q(entry.strip())
        requested.append((lang, q_factor))

    supported_set = set(supported_languages)
    matched = set()
    results_with_q = []

    for req_lang, q_factor in requested:
        if req_lang == '*':
            # Wildcard matches everything remaining
            for sup_lang in supported_languages:
                if sup_lang not in matched:
                    results_with_q.append((sup_lang, q_factor))
                    matched.add(sup_lang)
        elif req_lang in supported_set and req_lang not in matched:
            # Exact match
            results_with_q.append((req_lang, q_factor))
            matched.add(req_lang)
        elif '-' not in req_lang:
            # Generic match
            for sup_lang in supported_languages:
                if sup_lang.startswith(req_lang + '-') and sup_lang not in matched:
                    results_with_q.append((sup_lang, q_factor))
                    matched.add(sup_lang)

    # Sort by score (descending). Ties stay in original order.
    results_with_q.sort(key=lambda x: x[1], reverse=True)

    # Return only the language names
    return [lang for lang, q in results_with_q]

def parse_language_with_q(entry):
    parts = entry.split(';')
    lang = parts[0].strip()
    q_factor = 1.0

    if len(parts) > 1:
        q_part = parts[1].strip()
        if q_part.startswith('q='):
            q_factor = float(q_part[2:])

    return lang, q_factor