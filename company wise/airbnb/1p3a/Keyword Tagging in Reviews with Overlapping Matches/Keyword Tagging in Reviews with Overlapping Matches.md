Given a mapping from keywords to tags and a user review, replace the keywords in the review with the format [<tag>]{<keyword>}. For example:

Given mapping:

{
"san": "person",
"francisco": "person",
"san francisco": "city",
"Airbnb": "business",
"city": "location",
}
User review:

"I travelled to San Francisco for work and stayed at Airbnb.
I really loved the city and the home where I stayed.
I stayed with San and Francisco.
They both were really good and san's hospitality was outstanding."
Expected output:

"I travelled to [city]{San Francisco} for work and stayed at [business]{Airbnb}.
I really loved the [location]{city} and the home where I stayed.
I stayed with [person]{San} and [person]{Francisco}.
They both were really good and [person]{san}'s hospitality was outstanding."
Implement a function to achieve the above functionality.

Example
Input
{"san": "person", "francisco": "person", "san francisco": "city", "Airbnb": "business", "city": "location"}
"I travelled to San Francisco for work and stayed at Airbnb.\nI really loved the city and the home where I stayed.\nI stayed with San and Francisco.\nThey both were really good and san's hospitality was outstanding."