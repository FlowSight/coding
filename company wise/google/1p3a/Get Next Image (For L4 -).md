
Hallo - This question can't be practiced for now due to current limitations 🥹

You are to implement the getNext() function such that:

The images from markedFavorites should be returned first.
Then, return the remaining images from allImages that are not in markedFavorites.
Each call to getNext() should return the next image in this combined sequence.
Additional information collected through clarifying questions:

Once the end is reached, getNext() should return null.
getNext() takes no parameters.
You can do some setup in the constructor, but avoid anything too costly.
Assume that markedFavorites[] is a subset of allImages[], and both vectors remain unchanged after construction.
Order among markedFavorites[] and allImages[] should be maintained.
Follow up: What if markedFavorites[] contains photos strictly in order the photos also are in allImages[]?

Example
Input
allImages = ["i1", "i2", "i3", "i4", "i5", "i6", "i7", "i8", "i9", "i10"]
markedFavorites = ["i2", "i5", "i7"}
Output
"i2, i5, i7, i1, i3, i4, i6, i8, i9, i10"