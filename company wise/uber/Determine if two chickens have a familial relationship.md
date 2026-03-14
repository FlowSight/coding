Suppose you have a group of chickens, and you know the parent-child relationship for each chicken. Write a function to determine if there is a familial relationship between two given chickens.

# Example function signature
# def have_relationship(chicken1: str, chicken2: str, relations: Dict[str, List[str]]) -> bool:
# Takes two chicken names and a dictionary of parent-child relationships, returns whether they have a familial relationship

relations = {
    "parent1": ["child1", "child2"],
    "parent2": ["child3"],
    # further definitions
}

have_relationship("chicken1", "chicken2", relations)
Example
Input
chicken1 = 'chicken1'
chicken2 = 'chicken2'
relations = {
    'parent1': ['chicken1', 'chicken3'],
    'chicken3': ['chicken2']
}
Output
True