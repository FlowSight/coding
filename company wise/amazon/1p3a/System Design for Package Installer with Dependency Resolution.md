Design a package installer system that respects dependency resolution between packages.

Example
Input
{'pkgA': ['pkgB'], 'pkgB': [], 'pkgC': ['pkgA']}
Output
['pkgB', 'pkgA', 'pkgC']