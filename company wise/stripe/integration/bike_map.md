Bike Map Challenge
Challenge Summary
In this interview, you will work with existing code to connect to a map visualization API. You will get a GitHub link with starter code, JSON data, and a list of tasks. This test checks if you can read instructions, use HTTP APIs, handle files, and build a solution step-by-step.

Your goal is to make a tool that reads location data (coordinates), sends it to a map service, and saves the resulting map image.

Interview Details
Time: 45-60 minutes
Setup: You clone a repository, work on your own computer, and share your screen.
Language: Python, JavaScript/Node.js, Java, or others.
Style: You write the code. The interviewer watches but gives very little help.
📂 Starter Code: You will receive code and data similar to this example: Google Drive Link (https://drive.google.com/file/d/1vkbj9jaUaLqg4uk-eBhyQrEHfzSRvIIX/view?usp=sharing)

Step 1: Read Location Data
Your first job is to open a JSON file. This file contains a list of location coordinates (latitude and longitude).

Requirements:

Load the JSON file from the given path.
Get the first N coordinates (usually 10) from the list.
Print these coordinates to the screen.
Tips:

Look at how the data is organized.
Check the order of the numbers. Is it Latitude first or Longitude first? You will need this later.
Make sure your code does not crash if the file is missing or broken.
Step 2: Download a Map
Now, send an HTTP POST request to a map API. You will use a JSON configuration provided in the starter code. This request will return an image of a map centered on the Stripe office.

Requirements:

Read the request settings (JSON payload) provided in the code.
Send an HTTP POST request to the map URL.
Get the response, which is binary data (an image).
Save this image to a file on your computer.
Tips:

The response is an image, not text or JSON.
You must write "bytes" to the file, not strings.
Check that you can open the saved image file and see the map.
Step 3: Draw the Route
Now, combine the work from Step 1 and Step 2. You will modify the API request to include the coordinates you read earlier. This will draw a line (route) on the map.

Requirements:

Take the parsing logic from Step 1 and the API logic from Step 2.
Add the coordinates to the JSON payload sent to the API.
You might need to add details like line color or thickness.
Save the new image. It should show the map with a line drawn on it.
Tips:

Check the API rules. The order is often [longitude, latitude] (GeoJSON format), which is the opposite of Google Maps.
The final image should look like the map from Step 2, but with a clear path drawn on top.
Optional Extra Steps
If you have extra time, you might be asked to:

Change the line color, thickness, or style.
Draw multiple different routes.
Add specific markers to the map.
Break the route into segments based on data.
Discussion Questions
After coding, the interviewer may ask about real-world scenarios:

How would you handle this if you had thousands of coordinates?
How would you design this if it were a service used by many people?
What happens if the API is slow or gives an error?
How would you write tests for this code?
How to Prepare
Because the interviewer provides little help, you must be very comfortable with these tasks in your chosen language.

Making HTTP Requests
Practice sending data to an API.

Python (requests library):

import requests

# Send POST request with JSON data
response = requests.post(
    url="https://api.example.com/endpoint",
    json={"key": "value"},
    headers={"Content-Type": "application/json"}
)

# Check the result
print(response.status_code)
print(response.json())  # Use this if the response is text/JSON
JavaScript/Node.js (fetch or axios):


// Using fetch
const response = await fetch('https://api.example.com/endpoint', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({ key: 'value' })
});
const data = await response.json();

// Using axios
const axios = require('axios');
const axiosResponse = await axios.post('https://api.example.com/endpoint', {
  key: 'value'
});
Java (HttpClient):


import java.net.http.*;
import java.net.URI;

HttpClient client = HttpClient.newHttpClient();
HttpRequest request = HttpRequest.newBuilder()
    .uri(URI.create("https://api.example.com/endpoint"))
    .header("Content-Type", "application/json")
    .POST(HttpRequest.BodyPublishers.ofString("{\"key\": \"value\"}"))
    .build();

HttpResponse<String> response = client.send(request,
    HttpResponse.BodyHandlers.ofString());
Saving Image Files
The API sends back an image (binary data). You need to know how to save it.

Python:

response = requests.post(url, json=payload)

# Write the binary data (bytes) to a file
with open('map.png', 'wb') as f:
    f.write(response.content)
JavaScript/Node.js:


const fs = require('fs');
const response = await fetch(url, {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify(payload)
});
// Convert response to a buffer and save
const buffer = await response.arrayBuffer();
fs.writeFileSync('map.png', Buffer.from(buffer));
Java:


// Tell Java to expect a byte array response
HttpRequest request = HttpRequest.newBuilder()
    .uri(URI.create(url))
    .header("Content-Type", "application/json")
    .POST(HttpRequest.BodyPublishers.ofString(jsonPayload))
    .build();

HttpResponse<byte[]> response = client.send(request,
    HttpResponse.BodyHandlers.ofByteArray());
Files.write(Path.of("map.png"), response.body());
Working with JSON Files
Practice reading and editing JSON files on your computer.

Python:

import json

# Open and read the file
with open('coordinates.json', 'r') as f:
    data = json.load(f)

# Get the first 10 items from the list
coordinates = data['coordinates'][:10]

# Add a new field and save the file
data['newField'] = 'value'
with open('output.json', 'w') as f:
    json.dump(data, f, indent=2)
JavaScript/Node.js:


const fs = require('fs');

// Read and parse the file
const data = JSON.parse(fs.readFileSync('coordinates.json', 'utf8'));

// Get the first 10 items
const coordinates = data.coordinates.slice(0, 10);

// Add data and save to a new file
data.newField = 'value';
fs.writeFileSync('output.json', JSON.stringify(data, null, 2));
Java (Jackson/Gson):


// Use ObjectMapper to read the file
ObjectMapper mapper = new ObjectMapper();
Map<String, Object> data = mapper.readValue(
    new File("coordinates.json"),
    new TypeReference<Map<String, Object>>() {}
);

// Get the list and grab the first 10 items
List<Map<String, Object>> coordinates =
    ((List<Map<String, Object>>) data.get("coordinates"))
    .subList(0, 10);

// Add new data and write to a file
data.put("newField", "value");
mapper.writerWithDefaultPrettyPrinter()
    .writeValue(new File("output.json"), data);