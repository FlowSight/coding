# 🎓 **Training Session: Building Intelligent Agents with Microsoft Copilot Studio**

### 🎯 **Training Objectives**

By the end of this session, participants will be able to:

*   Understand the Copilot Studio interface and key components.
*   Create generative, conversational agents from scratch.
*   Build topics with trigger phrases and conversation nodes.
*   Use generative answers with knowledge sources.
*   Create and test a real agent using the **Expense Claim Assistant** scenario.
*   Create an autonomous agent **HR Employee Onboarding** scenario.


# 🧭 **Module 1 – Introduction to Copilot Studio (10 mins)**

### What is Copilot Studio?

# **Introduction to Microsoft Copilot Studio**

Today’s organizations are under increasing pressure to deliver faster, more accurate, and more scalable customer service. Customers expect instant answers and self‑service options, while support teams seek ways to reduce repetitive workloads and focus on higher‑value tasks. **Microsoft Copilot Studio** sits at the intersection of these needs, empowering businesses to build intelligent conversational agents that provide quick, reliable, and personalized support.

Copilot Studio enables organizations to create a library of the most commonly asked questions and deliver them through intuitive, conversational experiences. These agents allow customers to retrieve information through natural, simple queries—mirroring how they search online—while giving businesses an efficient, cost‑effective support channel. The platform is designed for makers of all skill levels: even non‑technical users can build, update, and expand agents rapidly without requiring data science or engineering expertise.

## **What Are Agents?**

An **agent** is an AI system that simulates human conversation through a chat interface. Agents listen for **keywords, phrases, and intent** that match a library of known customer issues—called **topics**—and respond with relevant information. As the conversation progresses, the agent continuously evaluates whether the customer’s question has been resolved and adjusts the flow to guide the user toward the correct answer.

## **Benefits of Using Agents**

### **1. Reduce Assisted Support**

Agents can handle simple or repetitive inquiries autonomously, referencing:

*   Topics
*   FAQ pages
*   Knowledge base articles  
    This decreases the volume of human‑assisted support requests.

### **2. Integrate Seamlessly with Business Systems**

Through integrations with CRM systems and other enterprise platforms, agents can:

*   Personalize conversations
*   Pull customer‑specific data
*   Transfer conversations (with context) to a human agent when necessary

### **3. Automate Tasks and Workflows**

Agents can trigger automated actions such as:

*   Creating cases
*   Scheduling meetings
*   Sending emails or surveys
*   Executing follow‑up workflows  
    Together with **Power Automate**, custom workflows can run securely—always with user permission.

### **4. Provide Generative, Context‑Aware Answers**

Generative AI enhances agent responses with natural, conversational answers grounded in approved data sources, such as:

*   Public websites
*   Internal SharePoint sites
*   Documents (PDF, Word)
*   Azure OpenAI
*   Enterprise data via Microsoft Graph connectors

## **Overview: Creating Agents with Copilot Studio**

Microsoft Copilot Studio delivers a **guided, no‑code interface** that allows makers to build AI agents rapidly, without specialized technical knowledge. It removes barriers between subject matter experts and development teams by allowing experts to directly design, test, and update conversational logic.

Using Copilot Studio helps organizations:

### **Empower Teams**

Anyone—from SMEs to support specialists—can build and maintain agents without writing code.

### **Reduce Costs**

Automating high‑volume inquiries frees human agents to handle complex, high‑value cases.

### **Improve Customer Satisfaction**

Customers gain access to quick, all‑day, self‑help options with personalized, multi‑turn conversation flows.

## **Easy Deployment and Real Business Impact**

One of Copilot Studio’s greatest strengths is its **simplicity of deployment**:

*   Sign up
*   Create an agent
*   Embed it into your organization’s website, Teams, or other channels


# 🖥️ **Module 2 – Understanding the Copilot Studio Interface (20 mins)**

Walk through each major area of the UI:

### **1. Create**

Start a new agent from scratch or from templates.

### **2. Agents**

View and manage all existing agents.

### **3. Library**

Access connectors, component collections, and reusable assets.

### **4. Overview**

Home screen for the selected agent — quick access to configuration.

### **5. Knowledge**

Add websites, documents, SharePoint, Dataverse, or Graph connectors as grounding sources.

### **6. Topics**

Build & structure conversations using triggers + conversation nodes.

### **7. Actions**

Create or import:

*   Conversational plugins
*   AI plugins

### **8. Activity**

Monitor GPT calls, AI responses, system logs.

### **9. Analytics**

Usage insights: sessions, escalations, resolutions, drop-offs.

### **10. Channels**

Publish agent to Teams, Web, Mobile, Custom channel.

### **11. Settings**

Authentication, channel settings, skills, environment configurations.

### **12. Test your agent panel**

Side panel to test conversational flows end-to-end.

# 🧩 **Module 3 – Working with Topics (25 mins)**

### What are Topics?

Topics represent the *intents* of a user — common questions or tasks.

Examples:

*   “Reset password”
*   “Check order status”
*   “Return item instructions”

### **Topic Structure**

1.  **Trigger Phrases**
    *   Keywords, utterances, questions
    *   Example: *“What are your store hours?”*

2.  **Conversation Nodes**
    *   Dialogue steps that define agent behavior
    *   Display messages, ask questions, run actions, call plugins

### **Ways to Create Topics**

#### **From Blank**

*   Start with no predefined structure
*   Manually enter triggers, nodes, logic

#### **Create from Description**

*   Provide a short description
*   Copilot auto-generates the topic, flow, and triggers

### **Best Practices**

*   Make trigger phrases **unique** per topic
*   Add **5–10 varied** triggers for better intent detection
*   Frequently test topic recognition in the Test panel

***

# 🛠️ **Module 4 – Conversation Nodes (10 mins)**

### Types of Nodes

*   **Message** – Bot responds with text
*   **Ask a Question** – Captures user input
*   **Call an Action** – Trigger a plugin or API
*   **Condition** – Branch logic
*   **Generative Answers Node** – Use AI to summarize/search based on knowledge sources

### Example

To get store hours:

*   Ask for location → Confirm input → Display relevant hours.

***

# 🤖 **Module 5 – Generative Answers with Knowledge Sources (20 mins)**

### Why add knowledge sources?

Topics can’t cover every possible user question.  
Generative Answers allow AI to respond using **your organization’s content**, not generic GPT.

### Supported Knowledge Types

*   Websites
*   PDFs, Text files
*   SharePoint libraries
*   Dataverse tables
*   Enterprise data through Graph connectors

### How Generative Answers Work

*   Agent-level sources = fallback
*   Generative Answers node = overrides fallback for specific topics
*   AI searches and summarizes the content you select

***

# 🧪 **Module 6 – Lab: Build the *Expense Claim Assistant* Agent (30–40 mins)**

Participants will build a functioning agent with:

### ✔ Agent Name

**Expense Claim Assistant**

### ✔ Description

"Help employees submit, track, and manage their expense claims efficiently."

### ✔ Add Purpose and Guidelines

*   Friendly + professional
*   Must follow company expense policy
*   No tax advice
*   Don’t process incomplete claims
*   Provide clear step-by-step instructions

***

## **Lab Step 1 – Create the Agent**

1.  Go to **Create → New Agent**
2.  Enter the name & description
3.  Confirm creation

***

## **Lab Step 2 – Create Topic: *Ask about expenses contact***

### Trigger phrases to include:

*   who do I contact about expenses
*   expense department contact
*   how can I reach the expenses team
*   expense inquiry contact
*   contact for expense questions

### Conversation Flow:

**Bot message:**  
“Please reach out to our finance team at **<finance@contoso.com>** for all expense-related inquiries.”

Save the topic.

***

## **Lab Step 3 – Add Knowledge Source**

1.  Go to **Knowledge**
2.  Upload or link the company expense guideline source (PDF, SharePoint, website, etc.)
3.  Enable it for grounding generative answers.

***

## **Lab Step 4 – Test the Agent**

In Test Pane, enter:

*   *What’s the expense limit for a hotel stay?*
*   *What about flights?*
*   *What guidelines are there for entertainment expenses?*
*   *What are the expense limits for meals?*

Verify responses are grounded using the knowledge source.

## **Lab Step 5 – Configure Welcome Message**

Set:  
**“Ask me about Expense claims”**

### Add conversation starters:

*   Hello
*   Who should I contact with expense enquiries?
*   What are the expense limits for flights?


# **💼 Training Lab: Build an Autonomous HR Onboarding Agent in Microsoft Copilot Studio**

## **⏱ Duration:** 45–60 minutes

## **🎯 Skill Level:** Intermediate

## **📘 Objective:**

By the end of this lab, participants will build an **autonomous HR onboarding agent** that uses knowledge grounding, actions, triggers, and automated email workflows to streamline the employee onboarding process.

# **1. Introduction**

Autonomous agents in Microsoft Copilot Studio enable organizations to transform their business processes by automating tasks, coordinating workflows, and providing intelligent conversational assistance. In this lab, you’ll create an HR onboarding agent that:

*   Answers onboarding-related questions
*   Submits onboarding requests
*   Sends approval emails
*   Reacts to email responses
*   Coordinates with IT/procurement
*   Notifies employees with final instructions

This lab simulates an end‑to‑end **HR onboarding process** powered by an autonomous agent.

***

# **2. Real‑World Use Cases (Context Overview)**

Before building the agent, review typical enterprise scenarios where autonomous agents add value:

| **Department**   | **How Autonomous Agents Help**          |
| ---------------- | --------------------------------------- |
| HR Onboarding    | Automate employee hiring workflows      |
| IT Service       | Manage tickets, automate IT tasks       |
| Customer Service | Resolve tickets, handle FAQs            |
| Back‑Office      | Optimize admin processes                |
| Sales            | Handle lead intake, automate follow‑ups |

***

# **3. Components Used in This Lab**

| **Component** | **Role in the Agent**                                    |
| ------------- | -------------------------------------------------------- |
| **Knowledge** | Uses documents, FAQs, Dataverse data to answer questions |
| **Topics**    | The conversational logic — intents, triggers, dialogue   |
| **Actions**   | Allows agent to send emails, call APIs, run workflows    |
| **Triggers**  | Event‑based automation entry points                      |
| **Activity**  | Tracks user interactions for monitoring                  |
| **Analytics** | Provides usage and performance metrics                   |
| **Channels**  | Deploys the agent (Teams, Web, etc.)                     |


# **4. Scenario Overview: HR Employee Onboarding**

Your HR agent must automate the following workflow:

1.  Respond to general onboarding questions.
2.  Receive a new employee onboarding request.
3.  Send approval email to hiring manager.
4.  Wait for hiring manager’s response.
5.  If approved → email IT/procurement to set up laptop + accounts.
6.  Wait for IT/procurement confirmation.
7.  Notify the employee with onboarding instructions.


# **5. Prerequisites**

### **Dataverse Table Setup**

Create a Dataverse table using the **Employee details.csv** file.

Required columns:

*   **Name**
*   **Email ID**

***

# **6. Create the Agent**

1.  Open **Copilot Studio**
2.  Select **Create New Agent**
3.  Choose **Skip to configure**
4.  Fill the fields:

| Field            | Value                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Name**         | Employee Onboarding Agent                                                                                                                                                                                                                                                                                                                                                                                                                |
| **Description**  | An agent developed to simplify the employee onboarding process.                                                                                                                                                                                                                                                                                                                                                                          |
| **Instructions** | You are an agent responsible for employee onboarding. After you receive the onboarding request from HR, validate it and send the employee details to the hiring manager for approval. When the hiring manager approves it, forward the information to the IT and procurement teams so they can complete their respective tasks. After they finish their tasks, send the onboarding confirmation along with instructions to the employee. |

Select **Create** to continue.


# **7. Add Knowledge (Dataverse as Knowledge Source)**

1.  Go to **Knowledge**
2.  Select **Add knowledge**
3.  Choose **Dataverse**
4.  In Step 1 of the wizard:
    *   In the **Search bar**, type **Employee Details**
    *   Select your table(s)
    *   Select **Next**
5.  Complete the wizard and save

Your agent now uses the Dataverse table as grounded knowledge.

# **8. Create & Configure Actions**

You need 3 automated actions:

### **8.1 Add First Action: Email Hiring Manager**

1.  Select **+ Add action**
2.  Search for **Send an email (V2)**
3.  Select the connector
4.  Enter:
    *   **Name:** Send an email to the hiring manager
    *   **Description:** Sends an email requesting approval for employee onboarding.
5.  Select **Add action**

### **8.2 Add Remaining Actions**

Repeat the same steps to create:

*   **Send an email to the IT team for approval**
*   **Send final onboarding email to employee**

All actions now appear in the **Actions** list.


# **9. Create & Configure Triggers**

Triggers execute flows automatically based on events.


## **9.1 Trigger 1 — When a new employee is added**

Start the onboarding workflow.

1.  In Overview, select **Add trigger**
2.  Choose **When a row is added, modified, or deleted**
3.  Configure:
    *   **Name:** When a new employee is added
    *   **Change type:** Added
    *   **Table name:** Employee Details
    *   **Scope:** Select appropriate scope
4.  Select **Create trigger**


## **9.2 Trigger 2 — When hiring manager approves onboarding**

Used to detect approval email.

1.  Add new trigger: **When an email arrives**
2.  In **Subject filter**, enter:  
    **Onboarding request for the Employee**
3.  Select **Save draft**


## **9.3 Trigger 3 — When IT/procurement confirms access setup**

1.  Add new trigger: **When an email arrives**
2.  In **Subject filter**, enter:  
    **Account creation request for the Employee**
3.  Select **Save draft**

# **10. Validate the End‑to‑End Workflow**

### Test the agent by simulating:

✔ HR adds new employee → Dataverse trigger fires  
✔ Hiring manager receives approval email  
✔ Agent reads approval email  
✔ IT team receives provisioning request  
✔ Agent waits for IT confirmation  
✔ Agent emails employee with onboarding steps

# **11. Publish the Agent**

1.  Go to **Channels**
2.  Enable deployment to:
    *   Microsoft Teams
    *   Internal website
    *   External portal (if allowed)

# **12. Lab Completion**

Participants have now built an **Autonomous HR Onboarding Agent** that uses:

*   Dataverse knowledge
*   Email‑based automated actions
*   Event triggers
*   Autonomous orchestration
*   Multi-step enterprise workflow automation

As an agent you are responsible for employee onboarding when a new employee is added to the Employee Details Table, you will send the employee's information to the hiring manager for approval. After receiving approval from the hiring manager, you will forward the information to the IT and procurement team to complete their tasks. After receiving confirmation email from IT and procurement team send the onboarding confirmation along with the onboarding instructions to the employee.

### When a new employee is added
1. Upon receiving then trigger "When a new employee is added", retrieve the data from the row and verify the email column is not empty. If the email is valid, Use the Send an email to the hiring manager action to send an email to the hiring manager with email ID: "anshulsaxena@microsoft.com" immediately without any delay. Include the following details in the email body: Employee's Name, Employee's Email ID and add email subject "Onboarding request for the Employee", Employee's Name formatted in HTML, for proper styling and presentation.

### When Approval is received from Hiring Manager
1. Wait for Approval: Do not trigger next action until you receive "When a approval email arrives" trigger, if the body of the mail contains the word "Approved", use the Send an email to the IT team for approval action to send an email to the IT team with email ID: anshulsaxena@microsoft.com. Get the details of the employee from your knowledge "Employee Details" use email from body of the employee, Include the following details in the email body: Employee's Name and Employee's Email and add email subject "Account creation request for the Employee", Name of the employee is formatted in HTML for proper styling and presentation.

### When Confirmation is received from IT Item
1. Wait for Confirmation: Do not trigger the next action until you receive the "When a confirmation email arrives from IT Team" trigger, verify that the body of email contains terms such as "Confirmed", "Successful", "Account Created" or similar phrases, and that the subject includes "Account creation request for the Employee", then useSend a final email to the employee with onboarding details action to send an email to the employee with email ID equal to email column from employee details fetched from your knowledge "Employee Details" and email body will be a warm, professional welcome message celebrating the employee's start at the company, formatted in HTML for proper styling.