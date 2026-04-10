    Payment Webhook System
The Challenge
You need to design a webhook service for a payment platform. The goal is to notify merchants whenever a payment event happens. For example, when a customer pays, gets a refund, or disputes a charge, the platform must send this information to the merchant's server immediately.

Think about the workflow: An online store connects to a payment platform to handle money. The store needs to know right away when a payment succeeds so they can ship the product. They also need to know about refunds to update their stock. A webhook system does this by sending HTTP POST requests to a specific URL that the merchant sets up.

What the System Needs
Your system must handle three main things:

Merchant Registration: Allow merchants to save a webhook URL and choose which types of events they want to receive.
Sending Events: When a payment event happens, send an HTTP POST request with the data to all registered webhooks.
Reliability: Ensure the message gets delivered, even if the merchant's server is down for a short time.
Code Example
// Save a new webhook endpoint
WebhookRegistration registerWebhook(
    String merchantId,
    String callbackUrl,
    List<String> eventTypes  // Example: ["payment.success", "refund.created"]
)
When an event happens, the system sends an HTTP POST request to the merchant's URL:

{
    "id": "evt_1234567890",
    "type": "payment.success",
    "created_at": "2024-12-15T10:30:00Z",
    "data": {
        "payment_id": "pay_abc123",
        "amount": 5000,
        "currency": "usd",
        "customer_id": "cus_xyz789"
    }
}
The merchant must reply with an HTTP 200 code to confirm they got the message.

Things to Think About
Delivery Guarantees: How do you make sure every message is delivered at least once? How should merchants handle it if they get the same message twice?
Retry Strategy: What do you do if the merchant's server is down? How many times do you try again, and for how long?
Latency: Some merchant servers might take 10-15 seconds to reply. How do you handle this without slowing down your system?
Security: How can the merchant prove that the request really came from your platform?
Scale: The system might create millions of events every day. How do you handle this huge amount of traffic?
Topics for Discussion
In the interview, the interviewer may ask deeper questions about these specific technical areas:

Idempotency: How do merchants safely process the same webhook twice without errors? What unique ID should they use?
Signature Verification: How do you sign the requests? Should you use Symmetric (HMAC) or Asymmetric (RSA) keys so merchants can check the signature?
Circuit Breaking: When do you stop trying to send data to a broken URL? How do you tell the merchant there is a problem?
Event Ordering: Is it possible for events to arrive in the wrong order? How should the merchant handle that?
Endpoint Validation: How do you verify that the merchant actually owns the URL they entered before you send them sensitive payment data?
SSRF Prevention: How do you stop attackers from using your webhook system to hit your internal servers?
Observability: How do merchants see logs or debug why a delivery failed?
Backpressure: If one merchant has millions of stuck events, how do you make sure it doesn't slow down delivery for other merchants?
Helpful Links
This is a very common system design problem. Here are some resources to help you understand the architecture:

Designing Payment Webhook - Tianpan.co - Explains the architecture, security, and retry logic.
Webhook System Design - System Design School - A step-by-step guide to the components and how to handle failures.
Webhook System Design - YouTube - A video that draws out the system design visually.
Real World Context
This question was asked during a remote interview for a Software Engineer role at Stripe. The interview focuses on building a system that is very reliable. They care a lot about how you handle the asynchronous nature of webhooks and how you ensure merchants never miss a payment notification.

You should be ready to talk about the whole lifecycle: from the merchant signing up and verifying their URL, to creating the event, putting it in a queue, and sending it out. Because reliability is a priority, expect detailed questions about retry logic, idempotency, and how to deal with merchant servers that are slow or broken.