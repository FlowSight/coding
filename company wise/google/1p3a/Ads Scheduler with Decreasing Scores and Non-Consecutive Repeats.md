Implement two interfaces insertAd(content, score) and getAd():

insertAd(content, score): Insert an ad with its content and score
getAd(): Return the ad with the highest score, but the score decreases by 1 each time it is called, and the same content cannot be returned consecutively. Consider using an appropriate data structure to optimize method calls.
Example Input:

insertAd("Ad1", 5)
insertAd("Ad2", 3)
getAd()  # Returns Ad1
getAd()  # Returns Ad2
getAd()  # Returns Ad1 or Ad2 depending on the state
Example
Input
insertAd("Ad1", 5)
insertAd("Ad2", 3)
getAd()
getAd()
getAd()