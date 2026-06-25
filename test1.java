/*


Using an HTTP GET method, retrieve information from Wikipedia using a given topic.
Query:
  https://en.wikipedia.org/w/api.php?action=parse&section=0&prop=text&format=json&page=[topic]
to get the topic Wikipedia article. Return the total number of times that the
string [topic] appears in the article's text field.

Notes:
- The search is case-sensitive.
- Your request needs a user-agent string:
  {"User-Agent": "hrw/1.0 (contact: support@hackank.com) requests/{requests.__version__}"}

The query response from the website is a JSON object described below:
- parse: A JSON object representing the article's parsed web page. It has the
  following three fields:
    1. title: The article's title, as specified by the argument topic
    2. pageid: The article's Page ID
    3. text: A JSON object that contains the Wikipedia article as an HTML dump

Function Description:
  Complete the function getTopicCount .

  getTopicCount has the following parameter(s):
    - topic: a string to query

  Returns:
    - int: the number of times the search term topic appears in the returned text field

Note: Please review the header in the code stub to see available libraries for
API requests in the selected language. Required libraries can be imported in order
to solve the question.

Sample Case 0:
  STDIN       Function
  -----       --------
  pizza       topic = 'pizza'
  sample output : 149

Expected output: count of "pizza" in the text field of the Wikipedia article for "pizza"
================================================================================

java signature :
static int getTopicCount(String topic){

}
*/



// Python solution:
// 
// import requests
// 
// def getTopicCount(topic):
//     url = f"https://en.wikipedia.org/w/api.php?action=parse&section=0&prop=text&format=json&page={topic}"
//     headers = {"User-Agent": f"hrw/1.0 (contact: support@hackank.com) requests/{requests.__version__}"}
//     response = requests.get(url, headers=headers)
//     data = response.json()
//     text = data["parse"]["text"]["*"]
//     return text.count(topic)

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;
import java.net.*;
import org.json.simple.*;
import org.json.simple.parser.*;
import java.net.http.*;
import java.nio.charset.StandardCharsets;
import java.net.URI;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import com.google.gson.*;

public class test1 {

    static int getTopicCount(String topic) {
        try {
            String encodedTopic = URLEncoder.encode(topic, "UTF-8");
            String urlStr = "https://en.wikipedia.org/w/api.php?action=parse&section=0&prop=text&format=json&page=" + encodedTopic;

            HttpClient client = HttpClient.newHttpClient();
            HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(urlStr))
                .header("User-Agent", "hrw/1.0 (contact: support@hackank.com) requests/2.28.0")
                .GET()
                .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            String body = response.body();

            JsonObject json = JsonParser.parseString(body).getAsJsonObject();
            JsonObject parseObj = json.getAsJsonObject("parse");
            JsonObject textObj = parseObj.getAsJsonObject("text");
            String text = textObj.get("*").getAsString();

            // Count occurrences (case-sensitive)
            int count = 0;
            int idx = 0;
            while ((idx = text.indexOf(topic, idx)) != -1) {
                count++;
                idx += topic.length();
            }
            return count;
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    public static void main(String[] args) {
        String topic = "pizza";
        System.out.println("Topic: " + topic + " -> Count: " + getTopicCount(topic));
    }
}




