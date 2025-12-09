The Basics
60-minute CoderPad session with an AI-assist chat window (GPT-4o mini, Claude 3.5 Haiku, or Llama 4 Maverick; you can switch models). Somewhat similar interface to github copilot's chat window, but simplified.

One thematic question with multiple checkpoints or stages (so it can be a multi-part question), not two separate LeetCode problems

You get a mini multi-file codebase (for Python: multiple .py files plus requirements.txt)

You can run and debug code in real time. So no dry-running needed I suppsoe

Started appearing early October 2025 for SWE and ML; likely rolling out to Production Engineers soon

What This Round Actually Tests
What do we look for?
The AI-Enabled Coding Interview will assess your performance on the following four focus areas: Problem Solving, Code Development and Understanding, Verification and Debugging, and Technical Communication.

• Problem Solving: Are you able to clarify and refine problem statements? Can you generate solutions to open-ended and quantitative problems?
• Code Development and Understanding: Are you able to navigate a codebase to develop and build on working code structures and to evaluate the quality of produced code? Can you analyze and improve code quality and maintainability? Does code work as intended after it is executed?
• Verification and Debugging: Can you find and mitigate errors to ensure code runs/functions as intended? Are you able to verify solutions meet specified requirements, leveraging test/edge cases and handling errors and exceptions? How well do your unit tests run?
• Technical Communication: How well can you communicate reasoning, discuss technical ideas, ask thoughtful questions, and incorporate feedback?

What You Need to Know About the AI
It is not a frontier reasoning model. Expect hallucinations, suboptimal suggestions, and missed edge cases

The AI can see all code in your editor (no copy-paste needed)

This is not a prompting test. You are evaluated on problem-solving and verification, not AI expertise

Some candidates barely use it and excel; others use it heavily for boilerplate and also excel

The AI is great for: boilerplate, parsing, scaffolding, heavy typing, and help with debugging and navigating the codebase.

AI struggles with: 100% accuracy, algorithmic optimality, edge cases, and deep reasoning

Things To Avoid Doing
Letting AI drive and do all the work: for example, pasting large outputs without reviewing them line by line

Skipping tests: eyeballing code instead of actually running it

Giant code dumps: requesting 100+ lines at once that you cannot verify

Long silences: going quiet without indicating to the interviewer that you are taking time to think or to do x, y, z. Keep the interviewer in the loop

Ignoring regressions: only re-running the last failing test instead of the full suite

Nonstop narration: talking through every keystroke

How to Prepare
Ask your recruiter for the practice CoderPad (it has the AI-assist tab and model switcher)

Practice three scenarios:

Building from scratch

Extending unfamiliar multi-file code

Debugging broken code under pressure

///////

Get good at rigorously laying out edge cases: empty input, large values, duplicates, invalid data

Get familiar with the AI-models beforehand: Know which one you will use for different tasks like (writing tests, debugging etc).

One tip that should help with time management in this round is to think about pipelining your workflow with the AI. Basically, try to work in parallel with the model instead of waiting around for each response, as much as you can

For example if you have 4 functions to implement, you can ask the AI to implement the first two functions. While it's generating, use that time to explain your approach out loud to the interviewer instead of just watching it generate. Once the AI finishes, ask it for the next 2 functions, and in parallel review the generated code, which you've probably pasted in the editor at this point.

Another example could be to tell the AI to generate the skeleton/interface for your planned approach, and while it's doing this you can use this time to explain the runtime and space complexity to the interviewer.

The goal is to as much as you can minimise idle time, so try to be doing something valuable while the AI is doing its thing.

there is cost for
    1.  entering the prompts
    2.  the AI can hallucinate.

Rule of thumb : dont use ai for something which u can do much faster.