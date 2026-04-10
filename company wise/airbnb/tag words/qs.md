Assume that Airbnb decided to enable search on user reviews. In order to make the search better you were requested to tag specific words in the review .

Search team has given you a bunch of key value pairs where the keys denote words which may or may not present in a review and the value corresponds to the search metadata. Your task is to prepend the metadata tag and highlight the specific review word in brackets. You should make sure the original case is maintained in the result string.

Test case #1 [ no confliction ]

Input:

Review:
"I visited San Francisco for work and stayed at Airbnb.
I really loved the city and the home where I stayed."

Tags: {
"airbnb": "business",
"san francisco": "city",
}

Output:
"I visited [city]{San Francisco} for work and stayed at [business]{Airbnb}.
I really loved the city and the home where I stayed."

Test case #2 [ with confliction ]

Input

Review:
"I travelled to San Francisco for work and stayed at Airbnb.
I really loved the city and the home where I stayed.
I stayed with San and Francisco.
They both were really good and san's hospitality was outstanding."

Tags: {
"san": "person",
"francisco": "person",
"san francisco": "city",
"Airbnb": "business",
"city": "location",
}

Output:
"I travelled to [city]{San Francisco} for work and stayed at [business]{Airbnb}.
I really loved the [location]{city} and the home where I stayed.
I stayed with [person]{San} and [person]{Francisco}.
They both were really good and [person]{san}'s hospitality was outstanding."