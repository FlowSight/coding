Business Account Data Verification
Problem Requirements
You are building a system to verify new business accounts. This is a "Know Your Customer" (KYC) system. The system reads business data from a CSV string. You must decide if each account is VERIFIED or NOT VERIFIED.

You will build the solution in five steps. Each step adds a new rule:

Check for Missing Info: Make sure all fields have data.
Check Description Length: Make sure the description is the right length.
Block Bad Words: Flag businesses using forbidden generic words.
Match Business Names: Check if the name matches the description fields.
Return Specific Error Codes: Tell the user exactly why verification failed.
Input Format
You get a string formatted as a CSV (Comma Separated Values).

col1,col2,col3,col4,col5,col6
BIZ001,Pawsome Pets Inc.,pawsomepets.com,Pawsome,PAWSOME PETS INC,Premium pet supplies
BIZ002,Bean Bliss Coffee,beanbliss.com,,,Artisan coffee roasters
The first line is the header. Every line after that is a business account with 6 columns:

col1: Business ID
col2: Legal Name
col3: Website URL
col4: Short Description
col5: Full Description
col6: Product Details
Output Format
For every business (skip the header), print one line like this:

VERIFIED: <business_name>
Or like this:

NOT VERIFIED: <business_name>
You must keep the output in the same order as the input.

Part 1: Check for Missing Info
What You Need To Do
Write a function called validate_businesses(csv_data). This function checks if a business provided all the required information. A business is VERIFIED only if every field has text in it.

If a field only contains spaces, count it as empty.

Example
Input:

csv_data = """col1,col2,col3,col4,col5,col6
BIZ001,Pawsome Pets Inc.,pawsomepets.com,Pawsome,PAWSOME PETS INC,Premium pet supplies
BIZ002,Bean Bliss Coffee,beanbliss.com,,,Artisan coffee roasters
BIZ003,,,,,
BIZ004,Tech Solutions,techsol.io,Tech,TECH SOLUTIONS,Software consulting"""
Output:

VERIFIED: Pawsome Pets Inc.
NOT VERIFIED: Bean Bliss Coffee
NOT VERIFIED:
VERIFIED: Tech Solutions
Explanation:

BIZ001: Has all 6 fields. -> VERIFIED
BIZ002: Missing col4 and col5. -> NOT VERIFIED
BIZ003: Only has col1. -> NOT VERIFIED (Name is empty, so output name is blank)
BIZ004: Has all fields. -> VERIFIED
Rules
All 6 columns must have data (remove whitespace first).
Ignore the first row (the header).
Keep the order of the businesses the same.
Handle cases where the business name (col2) is missing.
Questions to Ask the Interviewer
Can I assume the CSV format is perfect, or should I check for errors?
What if a row is missing columns completely?
What do I print if the business name itself is empty?
Do special characters count as "empty"?
Part 2: Check Description Length
What You Need To Do
Update your code to check the length of the Full Description (col5). It must follow Stripe's rules. The length must be between 5 and 31 characters (inclusive).

Remove extra spaces before counting. If the length is wrong, mark it NOT VERIFIED.

Example
Input:

csv_data = """col1,col2,col3,col4,col5,col6
BIZ001,Pawsome Pets Inc.,pawsomepets.com,Pawsome,PAWSOME PETS INC,Premium pet supplies
BIZ002,Bean Bliss Coffee,beanbliss.com,Bean,Bean,Artisan coffee roasters
BIZ003,Oakridge Furniture,oakridge.com,Oak,OAKRIDGE CUSTOM WOODWORKING AND FURNITURE EMPORIUM,Custom furniture
BIZ004,Tech Solutions,techsol.io,Tech,ITCS,Software consulting"""
Output:

VERIFIED: Pawsome Pets Inc.
NOT VERIFIED: Bean Bliss Coffee
NOT VERIFIED: Oakridge Furniture
NOT VERIFIED: Tech Solutions
Explanation:

BIZ001: Length is 16. This is okay. -> VERIFIED
BIZ002: Length is 4. Too short. -> NOT VERIFIED
BIZ003: Length is 50. Too long. -> NOT VERIFIED
BIZ004: Length is 4. Too short. -> NOT VERIFIED
Rules
Remove whitespace from col5 before checking.
Length must be between 5 and 31.
Check this after checking for missing fields (Part 1).
Part 3: Block Bad Words
What You Need To Do
To stop fraud, we must block generic business names in the Full Description (col5). If col5 contains any of these words, mark the account NOT VERIFIED:

Blocked Words (Case-Insensitive):

ONLINE STORE
ECOMMERCE
RETAIL
SHOP
GENERAL MERCHANDISE
Case-insensitive means "Shop", "SHOP", and "shop" are all blocked.

Example
Input:

csv_data = """col1,col2,col3,col4,col5,col6
BIZ001,Pawsome Pets Inc.,pawsomepets.com,Pawsome,PAWSOME PETS INC,Premium pet supplies
BIZ002,Global Goods Market,globalgoods.com,Global,ONLINE STORE,Various products
BIZ003,Northwest Tech,nwtech.com,NW Tech,NORTHWEST INNOVATION TECH,Technology solutions
BIZ004,Sweet Dreams,sweetdreams.com,Sweet,SWEET DREAMS CREAMERY,Ice cream shop"""
Output:

VERIFIED: Pawsome Pets Inc.
NOT VERIFIED: Global Goods Market
VERIFIED: Northwest Tech
VERIFIED: Sweet Dreams
Explanation:

BIZ001: No bad words. -> VERIFIED
BIZ002: Contains "ONLINE STORE". -> NOT VERIFIED
BIZ003: No bad words. -> VERIFIED
BIZ004: col5 does not have bad words (we ignore col6). -> VERIFIED
Rules
Check col5 for blocked terms.
Ignore upper/lower case.
Do this check in addition to Part 1 and Part 2.
Questions to Ask the Interviewer
Do I block the word if it is part of another word? (e.g., does "WORKSHOP" count as "SHOP"?)
Are there other words to block?
Should I check other columns too?
Part 4: Match Business Names
What You Need To Do
Make sure the Business Name (col2) matches the descriptions (col4 or col5). At least 50% of the words in the Business Name must appear in either the Short Description (col4) or Full Description (col5).

How to Match Words:

Split col2, col4, and col5 into words using spaces.
Remove "LLC" and "Inc" from the lists.
Ignore upper/lower case.
Check if half of the name's words exist in the description fields.
Example
Input:

csv_data = """col1,col2,col3,col4,col5,col6
BIZ001,land water,landwater.com,land,land water LLC,Environmental services
BIZ002,Acme Global Trading,acme.com,Acme,XYZ ENTERPRISES,Import export services
BIZ003,Maple Ridge Bakery,maplebakery.com,Maple,MAPLE RIDGE BAKERY LLC,Artisan baked goods
BIZ004,Innovation Labs Inc,innovlabs.com,Labs,INNOVATION RESEARCH,R&D services"""
Output:

VERIFIED: land water
NOT VERIFIED: Acme Global Trading
VERIFIED: Maple Ridge Bakery
VERIFIED: Innovation Labs Inc
Explanation:

BIZ001: "land water" (2 words). Both are in col5. Match: 100%. -> VERIFIED
BIZ002: "Acme Global Trading" (3 words). Only "Acme" is found. Match: 33% (less than 50%). -> NOT VERIFIED
BIZ003: "Maple Ridge Bakery" (3 words). All 3 match. Match: 100%. -> VERIFIED
BIZ004: "Innovation Labs Inc" (2 words, ignoring Inc). Both match. Match: 100%. -> VERIFIED
Rules
Split text by whitespace.
Ignore "LLC" and "Inc".
Comparison is case-insensitive.
You need >= 50% match.
Questions to Ask the Interviewer
Can I combine col4 and col5 for the check?
How do I handle punctuation (like "Ben & Jerry's")?
What if the name becomes empty after removing "LLC"?
Part 5: Return Specific Error Codes
What You Need To Do
Do not just say "NOT VERIFIED". Return a specific code explaining the error. If there are multiple errors, return the first one you find.

Order of Checks:

Empty fields → ERROR_MISSING_FIELDS
Bad length → ERROR_INVALID_LENGTH
Blocked word → ERROR_GENERIC_NAME
Name mismatch → ERROR_NAME_MISMATCH
Example
Input:

csv_data = """col1,col2,col3,col4,col5,col6
BIZ001,Pawsome Pets Inc.,pawsomepets.com,Pawsome,PAWSOME PETS INC,Premium pet supplies
BIZ002,Bean Bliss Coffee,beanbliss.com,,,Artisan coffee roasters
BIZ003,Short Name,short.com,Short,SHRT,Products
BIZ004,Generic Store,generic.com,Store,RETAIL,Various items
BIZ005,Mismatched Corp,mismatch.com,Wrong,DIFFERENT BUSINESS,Services"""
Output:

VERIFIED: Pawsome Pets Inc.
ERROR_MISSING_FIELDS: Bean Bliss Coffee
ERROR_INVALID_LENGTH: Short Name
ERROR_GENERIC_NAME: Generic Store
ERROR_NAME_MISMATCH: Mismatched Corp
Rules
Check rules in the order listed above.
Stop at the first error.
Only return VERIFIED if everything passes.
Solution Details
Step 1: Checking for Missing Info
Plan:

Read the CSV string and split it by lines.
Ignore the first line (header).
Loop through every data row:
Split the row by commas.
Check if all 6 items have text.
Print the result.
Complexity: O(n × m) (n = rows, m = row length). Memory: O(n) to store the lines.

Code:

def validate_businesses(csv_data):
    lines = csv_data.strip().split('\n')
    results = []

    for i, line in enumerate(lines):
        if i == 0:  # Skip header
            continue

        fields = [field.strip() for field in line.split(',')]

        # Ensure we have exactly 6 fields
        if len(fields) != 6:
            results.append(f"NOT VERIFIED: {fields[1] if len(fields) > 1 else ''}")
            continue

        # Check if all fields are non-empty
        all_filled = all(field for field in fields)
        business_name = fields[1]

        if all_filled:
            results.append(f"VERIFIED: {business_name}")
        else:
            results.append(f"NOT VERIFIED: {business_name}")

    return '\n'.join(results)
Things to Watch Out For:

Empty lines.
Rows with missing columns.
Fields with only spaces.
Step 2: Checking Description Length
Plan:

Add a check for column 5 length.
Do this after ensuring fields are not empty.
Range is 5 to 31.
Code:

def validate_businesses(csv_data):
    lines = csv_data.strip().split('\n')
    results = []

    for i, line in enumerate(lines):
        if i == 0:  # Skip header
            continue

        fields = [field.strip() for field in line.split(',')]

        if len(fields) != 6:
            results.append(f"NOT VERIFIED: {fields[1] if len(fields) > 1 else ''}")
            continue

        business_name = fields[1]
        full_descriptor = fields[4]

        # Check 1: All fields non-empty
        if not all(field for field in fields):
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        # Check 2: Descriptor length
        descriptor_len = len(full_descriptor)
        if descriptor_len < 5 or descriptor_len > 31:
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        results.append(f"VERIFIED: {business_name}")

    return '\n'.join(results)
Note: We use strip() to remove spaces before checking length.

Step 3: Blocking Generic Names
Plan:

Create a list of blocked words.
Check if col5 contains any of them.
Convert text to uppercase so case doesn't matter.
Code:

def validate_businesses(csv_data):
    BLOCKED_TERMS = {
        'ONLINE STORE',
        'ECOMMERCE',
        'RETAIL',
        'SHOP',
        'GENERAL MERCHANDISE'
    }

    lines = csv_data.strip().split('\n')
    results = []

    for i, line in enumerate(lines):
        if i == 0:
            continue

        fields = [field.strip() for field in line.split(',')]

        if len(fields) != 6:
            results.append(f"NOT VERIFIED: {fields[1] if len(fields) > 1 else ''}")
            continue

        business_name = fields[1]
        full_descriptor = fields[4]

        # Check 1: All fields non-empty
        if not all(field for field in fields):
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        # Check 2: Descriptor length
        if len(full_descriptor) < 5 or len(full_descriptor) > 31:
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        # Check 3: Blocked terms
        descriptor_upper = full_descriptor.upper()
        has_blocked_term = any(term in descriptor_upper for term in BLOCKED_TERMS)

        if has_blocked_term:
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        results.append(f"VERIFIED: {business_name}")

    return '\n'.join(results)
Note: This logic checks if the blocked term is inside the text (substring match).

Step 4: Matching Business Names
Plan:

Split names into word lists.
Filter out "LLC" and "Inc".
Count how many name words appear in the descriptions.
If matches / total_words >= 0.5, it passes.
Code:

def validate_businesses(csv_data):
    BLOCKED_TERMS = {
        'ONLINE STORE', 'ECOMMERCE', 'RETAIL', 'SHOP', 'GENERAL MERCHANDISE'
    }
    IGNORED_WORDS = {'llc', 'inc'}

    def get_words(text):
        """Extract and normalize words, removing ignored terms."""
        words = text.lower().split()
        return [w for w in words if w not in IGNORED_WORDS]

    def check_name_match(business_name, short_desc, full_desc):
        """Check if at least 50% of business name words match descriptors."""
        name_words = set(get_words(business_name))
        short_words = set(get_words(short_desc))
        full_words = set(get_words(full_desc))

        if not name_words:  # Edge case: no valid words in business name
            return False

        # Count matches in either short or full descriptor
        combined_descriptor_words = short_words | full_words
        matches = len(name_words & combined_descriptor_words)

        match_percentage = matches / len(name_words)
        return match_percentage >= 0.5

    lines = csv_data.strip().split('\n')
    results = []

    for i, line in enumerate(lines):
        if i == 0:
            continue

        fields = [field.strip() for field in line.split(',')]

        if len(fields) != 6:
            results.append(f"NOT VERIFIED: {fields[1] if len(fields) > 1 else ''}")
            continue

        business_name = fields[1]
        short_descriptor = fields[3]
        full_descriptor = fields[4]

        # Check 1: All fields non-empty
        if not all(field for field in fields):
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        # Check 2: Descriptor length
        if len(full_descriptor) < 5 or len(full_descriptor) > 31:
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        # Check 3: Blocked terms
        descriptor_upper = full_descriptor.upper()
        if any(term in descriptor_upper for term in BLOCKED_TERMS):
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        # Check 4: Name consistency
        if not check_name_match(business_name, short_descriptor, full_descriptor):
            results.append(f"NOT VERIFIED: {business_name}")
            continue

        results.append(f"VERIFIED: {business_name}")

    return '\n'.join(results)
Key Details:

Uses set for faster lookups.
& finds the intersection (common words).
| joins two sets together.
Complexity: O(n × w) (w = average words per field).

Step 5: Returning Error Codes
Plan:

Keep the order of checks the same.
Change the output string to the specific error code.
Return immediately when an error is found.
Code:

def validate_businesses(csv_data):
    BLOCKED_TERMS = {
        'ONLINE STORE', 'ECOMMERCE', 'RETAIL', 'SHOP', 'GENERAL MERCHANDISE'
    }
    IGNORED_WORDS = {'llc', 'inc'}

    def get_words(text):
        words = text.lower().split()
        return [w for w in words if w not in IGNORED_WORDS]

    def check_name_match(business_name, short_desc, full_desc):
        name_words = set(get_words(business_name))
        short_words = set(get_words(short_desc))
        full_words = set(get_words(full_desc))

        if not name_words:
            return False

        combined_descriptor_words = short_words | full_words
        matches = len(name_words & combined_descriptor_words)
        return matches / len(name_words) >= 0.5

    lines = csv_data.strip().split('\n')
    results = []

    for i, line in enumerate(lines):
        if i == 0:
            continue

        fields = [field.strip() for field in line.split(',')]

        if len(fields) != 6:
            results.append(f"ERROR_MISSING_FIELDS: {fields[1] if len(fields) > 1 else ''}")
            continue

        business_name = fields[1]
        short_descriptor = fields[3]
        full_descriptor = fields[4]

        # Validation 1: All fields non-empty
        if not all(field for field in fields):
            results.append(f"ERROR_MISSING_FIELDS: {business_name}")
            continue

        # Validation 2: Descriptor length
        if len(full_descriptor) < 5 or len(full_descriptor) > 31:
            results.append(f"ERROR_INVALID_LENGTH: {business_name}")
            continue

        # Validation 3: Blocked terms
        descriptor_upper = full_descriptor.upper()
        if any(term in descriptor_upper for term in BLOCKED_TERMS):
            results.append(f"ERROR_GENERIC_NAME: {business_name}")
            continue

        # Validation 4: Name consistency
        if not check_name_match(business_name, short_descriptor, full_descriptor):
            results.append(f"ERROR_NAME_MISMATCH: {business_name}")
            continue

        results.append(f"VERIFIED: {business_name}")

    return '\n'.join(results)
Extra Questions to Prepare For
Question: What tricky edge cases might break this code?

CSV Issues:

Commas inside fields: If a name is "Smith, Jones, and Co", simple splitting fails. You need a real CSV parser.
Special Characters: Emojis or accents in names.
Huge Files: If the file is too big for memory, you must process it line-by-line using a stream.
Code Example for Robustness:

import csv
from io import StringIO

def validate_businesses_robust(csv_data):
    """Handle edge cases like fields containing commas."""
    reader = csv.reader(StringIO(csv_data))
    next(reader)  # Skip header

    results = []
    for row in reader:
        if len(row) != 6:  # Handle inconsistent column count
            continue
        # Process with proper CSV escaping
Data Issues:

Weird Names: A business named "Inc" would have 0 words after filtering.
Abbreviations: "IBM" vs "International Business Machines".
Security: Users trying to inject SQL or HTML into the fields.