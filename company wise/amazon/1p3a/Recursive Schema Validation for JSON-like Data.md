Problem: Schema Validation (JSON-like data)
Implement a schema validation system. Given a JSON-like value data and a schema definition schema, determine whether data conforms to schema.

You must validate nested structures recursively (objects containing objects, arrays containing objects, etc.).

Data types
data may contain only:

null
bool
int/float
string
list
dict
Schema representation (you may design it, but it must be precise)
At minimum, support:

Primitive validation: string/number/bool/null
Object validation:
declared fields and their child schemas
recursive validation for nested fields
Array validation:
an item schema that every element must satisfy
Output
Return True/False. Consider edge cases such as missing fields, type mismatches, and nested validation failures.

Example (illustrative)
schema = {"type": "object", "properties": {"name": {"type": "string"}, "scores": {"type": "array", "items": {"type": "number"}}}}
data = {"name": "bob", "scores": [1, 2, 3]} -> True
data = {"name": "bob", "scores": [1, "x"]} -> False
Scale
Total node count N in data can be up to 1e5; implement efficient validation without redundant traversals.

Example
Input
schema={"type":"number"}
data=1
Output
True