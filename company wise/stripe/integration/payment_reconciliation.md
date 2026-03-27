Payment Reconciliation
Task Summary
This is a practical coding test. You need to build a system that checks payment records. You will read data and communicate with a clearing service API. You get a GitHub link that has starter code, practice files, and instructions for the API.

The test has four parts. It starts easy and gets harder. You will parse data, make HTTP requests, handle authentication, and create reports. Focus on writing clean code that looks like professional work.

Repository: Google Drive : https://drive.google.com/file/d/115JTeIoeBckXAEfLaz8KJxHIhZkYWurN/view

Interview Details
Time Limit: About 45 to 60 minutes.
Setup: Clone the code to your computer, work locally, and share your screen.
Languages: You can use Python, JavaScript, Java, Go, C++, Ruby, Rust, Kotlin, or C#.
Style: The interviewer will watch you work. They will not help much—you must lead the solution.
Step 1: Reading Payment Data
Your first job is to read JSON files that hold payment data. Each file has a list of payments with the merchant name, the amount of money, and the currency type.

Requirements:

Open and load the JSON files provided.
Read the payment records and print them so they are easy to read.
Do some math on the data (find the total amount and count the number of transactions).
Sample Data Structure:

[
  {
    "merchant": "acct_707",
    "amt": 91088,
    "currency": "usd"
  },
  {
    "merchant": "acct_707",
    "amt": 77855,
    "currency": "usd"
  }
]
Things to Keep in Mind:

The money amounts are in the smallest unit (like cents for USD).
You might need to process more than one file.
Write your code so it is easy to change for the next steps.
Step 2: Sending Data to the API
Now, you must change the payment data into a specific format called a "clearing file." Then, you must send it to the API.

Requirements:

Convert the data into a fixed-width format.
Log in to the service to get an API key.
Send the file using the /submit_clearing_file endpoint.
Check to make sure the upload worked.
Clearing File Format: Each line uses commas to separate fields. The fields must have a specific width:

Transaction ID
Timestamp
Amount (with zeros added to the front to fill space)
Currency code
Things to Keep in Mind:

The server is very strict about how the file looks. Look at the examples carefully.
You must use a Bearer token for authentication.
Think about what to do if the network fails.
Step 3: Comparing Transactions
Next, download the bank records from the service. You need to compare these records against the data you sent earlier.

Requirements:

Get the bank data from the /get_bank_account_transactions endpoint.
Match these transactions with your clearing file data.
Create a report that shows which items match and which ones do not.
Send this report to /validate_reconciliation_report to check your work.
Things to Keep in Mind:

The time on the records might not match exactly.
Some items might exist in one list but not the other.
The API will tell you if your report is correct.
Step 4: Managing Disputes
Finally, you need to handle "disputes." These are payments that were contested or charged back.

Requirements:

Get the list of disputes from the /get_disputes endpoint.
Add this data to your checking logic.
Update your report to show the disputed amounts.
Handle the new process for sending the data when disputes exist.
Things to Keep in Mind:

Disputes change the final total amount of money.
You might need to send extra information to the API.
The format of your report might need to change.