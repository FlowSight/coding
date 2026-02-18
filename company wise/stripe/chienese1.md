Programming exercise
Coding：bitmap, Bitmap
Send email
coding: email schedule, The interviewer might sort the output from the same day according to a specific weight.

The first part was coding, which was basically a repetition of the phone interview, but this time it required using built-in libraries. I only got two parts right. The interviewer seemed a bit disappointed because I wasn't very familiar with these libraries and had to look them up a lot.


Subscription: A list of users {name, plan, begin_date, duration}, emails should be sent in order (a welcome email on the day the plan is signed, an upcoming expiration email after -15 days, and an expire email on the day the plan expires). 
Second question: Add a change in plans: a list of changes {name, new_plan, change_date}. 
Third question: Bonus, adding a renewal to the second question, with the change list containing entries {name, extension, change_date}.


For example:
users = [{name: A, plan: X, begin_date = 0, duration = 30}, {name: B, plan: Y, begin_date = 1, duration = 15}],
output
0: [Welcome] A, subscribe in plan X
1: [Welcome] B, subscribe in plan Y
1: [Upcoming expiration] B, subscribe in plan Y
15: [Upcoming expiration] A, subscribe in plan X
16: [Expired] B, subscribe in plan Y
30: [Expired] A, subscribe in plan X

For example, the second question:
users = [{name: A, plan: X, begin_date = 0, duration = 30}, {name: B, plan: Y, begin_date = 1, duration = 15}]
changes = [{name: A, new_plan: Y, change_date = 5}]
output
0: [Welcome] A, subscribe in plan X
1: [Welcome] B, subscribe in plan Y
1: [Upcoming expiration] B, subscribe in plan Y
5: [Changed] A, subscribe in plan Y
15: [Upcoming expiration] A, subscribe in plan Y
16: [Expired] B, subscribe in plan Y
30: [Expired] A, subscribe in plan Y

For example, the third question:
users = [{name: A, plan: X, begin_date = 0, duration = 30}, {name: B, plan: Y, begin_date = 1, duration = 15}]
changes = [{name: A, new_plan: Y, change_date: 5}, {name: B, extension: 15, change_date: 3}]
output
0: [Welcome] A, subscribe in plan X
1: [Welcome] B, subscribe in plan Y
1: [Upcoming expiration] B, subscribe in plan Y
3: [Renewed] B, subscribe in plan Y
5: [Changed] A, subscribe in plan Y
15: [Upcoming expiration] A, subscribe in plan Y
16: [Upcoming expiration] B, subcribe in plan Y
30: [Expired] A, subscribe in plan Y
30: Expired] B, subscribe in plan Y

card question
part1
Give a string of characters to represent many cards, the format is [len][card][len][card]...
Process characters, extract each card according to len, maintain order


part2
On the basis of part 1, add a system supported card, return support, and maintain order. As I write this, I start to think of the http header question, and follow a similar idea.
After finishing this part and running the example given, he posted a bunch of test cases and passed them all. At this time, it is still ten minutes to do part 3.


part3
On the basis of part 2, add the card number of generic to the string. As long as there is a card starting with it in the system supported, the result will be stored. Here we need to pay attention to maintaining order and uniqueness.


Classic exchange rate question
Old exchange rate conversion questions
Give a long string containing the exchange rates of multiple currencies.
It is required to write a function that returns the exchange rate of two currencies.

example input:
USD:CAD:1.26, USD:AUD:0.75, USD:JPY:109.23

example expected output:
CAD:USD => 0.794

I use a double-layer map to save. The key is currency1 and the value is map of currency2 to rate.

Part 1
It is required to return the exchange rate between two currencies. Both currencies are directly related in the input string.
eg, USD:AUD:0.75 and AUD:USD:1.33


Part 2
It is required to return the exchange rate between two currencies. The two currencies are not directly related in the input string.
Can be connected through an intermediate currency.
For example, request the exchange rate of CAD->AUD. It can be calculated using USD as an intermediate variable, CAD->USD->AUD.
final rate = 0.75 * (1/1.26) = 0.595

Part 3
In the end, I didn’t have enough time, so I could only briefly sketch out my ideas. The question probably means that if there are multiple currencies to be connected in the middle.
Because part2 has only one middle currency, there should be an uncertain number of part3.
As for the solution, I think we can use graph dfs traverse + backtrack to find it.
For each further step, rate * curRate. If sub dfs is not found, rate/curRate.
［/hide］


Processing csv format text
/*
Part 1 prompt: Stripe in Brazil is obliged to register customer's transactions for each merchant with the central bank as an aggregated unit per day.
These are called receivables. A receivable is identified by 3 identifiers:
* merchant_id (String): The id of the merchant on Stripe side.
* card_type (String): The type of the card used for the transaction (e.g. Visa)
* payout_date (String): String date of the funds available to the merchant by Stripe.

A payment transaction in Stripe API can be represented as the following object:
```
Transaction {
    string customer_id
    string merchant_id
    string payout_date
    string card_type
    int amount
}
```

Implement register_receivables function that takes a string in CSV format
where each line represents a transaction and returns the registered aggregated receivables using the rules above.
Print the returned receivables to console using the format below.
Feel free to parse the CSV using a standard or a 3rd party library or implement it yourself.

You can assume the following about the input:
* The first line of the input is a header. The header is always the same so it can be ignored or hardcoded
* You can assume that the input has
already been read from a file and checked for correctness
* No data fields in this file will include commas or whitespace surrounding the field values.

You can also assume the following about the output:
* The first line of the output is the header. The header is always the same so it can be hardcoded
* Order of the output does not matter

Example input 1:
```
customer_id,merchant_id,payout_date,card_type,amount
cust1,merchantA,2021-12-30,Visa,150
cust2,merchantA,2021-12-30,Visa,200
cust3,merchantB,2021-12-31,MasterCard,300
cust4,merchantA,2021-12-30,Visa,50
```

Output 1:
```
merchant_id,card_type,payout_date,amount
merchantA,Visa,2021-12-30,400
merchantB,MasterCard,2021-12-31,300
```


Example input 2:
```
customer_id,merchant_id,payout_date,card_type,amount
cust1,merchantA,2021-12-29,MasterCard,50
cust2,merchantA,2021-12-29,Visa,150
cust3,merchantB,2021-12-31,Visa,300
cust4,merchantB,2021-12-29,MasterCard,200
```

Output 2
```
merchant_id,card_type,payout_date,amount
merchantA,MasterCard,2021-12-29,50
merchantA,Visa,2021-12-29,150
merchantB,Visa,2021-12-31,300
merchantB,MasterCard,2021-12-29,200
```
*/
part2
/*
In Brazil, settlement times can take up to 30 days for domestic card transaction. i.e. A merchant selling items online
will receive their money from a customer after a month of selling an item. This has created a need where merchants
are looking for ways to receive their money faster.

Per the regulations, merchants can sell their receivables to a financial institution. The financial institution
will pay the funds to the merchant earlier and receive the funds from Stripe instead on the payout date.

An agreement between the merchant and a financial institution is called a contract. Stripe is obliged to respect
those contracts and update the registered receivables. Each contract is mapped to one receivable based on the
same 3 identifiers as above:
* merchant_id (String): The id of the merchant on Stripe side.
* card_type (String): The type of the card used for the transaction (e.g. Visa)
* payout_date (String): String date of the funds available to the merchant by Stripe.

A contract sent to Stripe is represented as follows:
```
Contract {
    string contract_id
    string merchant_id
    string payout_date
    string card_type
    integer amount
}
```

Implement update_receivables function that takes the list of registered receivables from part 1 and additional parameter of list of contracts.
The result should be the updated list of receivables.
For each contract, a receivable should be created for the contract id, and the corresponding merchant receivable should be removed.


Example input 1:

Transactions:
```
customer_id,merchant_id,payout_date,card_type,amount
cust1,merchantA,2022-01-05,Visa,300
cust2,merchantA,2022-01-05,Visa,200
cust3,merchantB,2022-01-06,MasterCard,1000
```

Contracts:
```
contract_id,merchant_id,payout_date,card_type,amount
contract1,merchantA,2022-01-05,Visa,500
```

=> update_receivables(registered_receivables, input_contracts)

Output 1:
```
id,card_type,payout_date,amount
contract1,Visa,2022-01-05,500
merchantB,MasterCard,2022-01-06,1000
```


Example input 2:
Transactions:
```
customer_id,merchant_id,payout_date,card_type,amount
cust1,merchantA,2022-01-07,Visa,500
cust2,merchantA,2022-01-07,Visa,250
cust3,merchantB,2022-01-08,MasterCard,1250
cust4,merchantC,2022-01-09,Visa,1500
```

Contracts:
```
contract_id,merchant_id,payout_date,card_type,amount
contract1,merchantA,2022-01-07,Visa,750
contract2,merchantC,2022-01-09,Visa,1500
```

=> update_receivables(registered_receivables, input_contracts)

Output 2:
```
id,card_type,payout_date,amount
contract1,Visa,2022-01-07,750
contract2,Visa,2022-01-09,1500
merchantB,MasterCard,2022-01-08,1250
```
*/

Bracket Exapnsion
part 1: expand single brace: prefix {a,c,d}, suffix -> prefixasuffix, prefixcsuffix, prefixdsuffix
Example 1:
Input = "/2022/{jan,feb,march}/report"
List<String> Output = ["/2022/jan/report"
   "/2022/feb/report"
   "/2022/march/report"]

part 2: expand single brace with invalid input cases
If there are less than 2 tokens enclosed within curly braces or incorrect expression
(eg. opening and closing braces not present, only opening brace present,
closing brace present before opening brace etc) return the output same as input
these patterns do not have enough tokens, so they are not expanded:
Example 1:
Input: pre{mid}suf
Output: pre{mid}suf
Example 2:
Input: pre{}suf
Output: pre{}suf

Part 3: Liqiao 1087, I don’t have time, but I gave you some ideas.


Debug
Debug: mako, requests

The second part is finding bugs. To be honest, this interviewer kind of rubbed me the wrong way. First you have to find the bug. At that time, he didn't give me 30 seconds to think. If I paused quietly for 5 seconds, he would interrupt and tell me what to do next. Sometimes I would just say the next point I was going to check and he would jump in and say exactly what I was about to say! Not sure if it's his character, but I hope it doesn't make me look bad. Finally, he briefly reminded me where the bug was, and I fixed it immediately. Then he added a small problem, which I quickly solved.

Debug: Give 40 minutes to debug the wrong test case, I finished it in the 39th minute. It is a library parsed by Json, and the result of getPath is incorrect;

Integration
bikemap
The third part is integration. In fact, it is to write some POST request code, targeting the existing API, and there are many parts. I finished four parts and then ran out of time. Not sure if they expect you to do more, but I'm most confident about this round. This interviewer didn't interfere much, which was best for me because I need silence to think.

Integration: Call an API and parse the results; the second question is to construct a specific payload and then download a map of the image; the third constructed payload needs to parse a file first, and the construction logic is more complicated;


SD
Fifth round SD: Ledger service
In this round of system design, Stripe is focusing on differentiation. Others may focus on the macro architecture, but Stripe is obsessed with the details of API design. Don't rush to draw the architecture diagram at the beginning. First, talk thoroughly with the interviewer about the core functions, performance requirements, and usage scenarios of the service. For example, is this Ledger service for internal use or for external use? What is the throughput required? How to ensure data consistency?
After discussing the requirements clearly, design the service layer and database accordingly. API design should not be vague. Parameter types, return value formats, and error code definitions must all have details. Database design should not just talk about what database to use, but also how to design the table structure and how to build the index. Remember, stay in communication with the interviewer throughout the entire process, and confirm the direction while designing. Don’t just finish the work and realize that you have gone astray.
sd:metric counter

System design: a library that supports metric collection. Because I use a similar library in my work, I can answer it easily.