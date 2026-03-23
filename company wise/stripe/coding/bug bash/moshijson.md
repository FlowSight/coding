https://drive.google.com/file/d/1dMQpNfTRGJbDQSj2AfQ3NhI0otMyD7iA/view


Debugging Task: Moshi JSON Library
The Task
This is a debugging test. You need to find and fix mistakes in a Java library called Moshi. We will give you a link to a GitHub folder. This folder has a version of Moshi with bugs hidden inside on purpose. You must use the included tests and your debugging skills to find these bugs.

This test checks if you can:

Work with code you have not seen before.
Understand difficult code quickly.
Use tools to find errors.
Explain your steps clearly while you work.
Repository: Google Drive

Interview Details
Time: About 45-60 minutes
Setup: Download the code, work on your computer, and share your screen
Language: Java
Process: The interviewer will watch you work. You should speak out loud to explain what you are thinking.
About Moshi
Moshi is a tool for Android and Java made by Square. It parses JSON. It is meant to replace Gson because it is faster and works better with Kotlin. Here are the main features:

Type-Safe Parsing: It safely changes JSON into Java/Kotlin objects.
Streaming API: It uses very little memory when reading large JSON files.
Custom Adapters: You can add your own rules for specific types.
Annotation Support: It uses @Json to match fields and @JsonQualifier for special handling.
Null Safety: It is strict about handling null values or missing data.
Code Example:


Moshi moshi = new Moshi.Builder().build();
JsonAdapter<User> adapter = moshi.adapter(User.class);

// Change JSON string into a Java object
User user = adapter.fromJson("{\"name\":\"John\",\"age\":30}");

// Change Java object back into a JSON string
String json = adapter.toJson(user);
You do not need to know Moshi before taking this test. The code comes with many tests that will help you see what is wrong.

How to Start
Steps to Run
Download the code and go to the debug-moshi folder.
Build the project with this command: ./gradlew build
Run the tests with this command: ./gradlew test
Look at which tests fail and start investigating.
Tips for Debugging
Suggested Plan
Run All Tests: First, see exactly what is broken.

./gradlew test
Focus on One Error: Run only the specific test that failed. This makes it easier to read the output.

./gradlew test --tests "ClassName.testMethodName"
Read the Test: Look at the code to see what the test expects to happen.

Follow the Code: Watch how the code runs from the input until the moment it fails.

Use the Debugger: Set breakpoints where the parsing logic happens.

IntelliJ IDEA: Right-click the test → Debug
Eclipse: Right-click the test → Debug As → JUnit Test
Search: Use key words to find the code responsible for handling the data.