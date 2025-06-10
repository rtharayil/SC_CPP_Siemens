# 🧾 3-Minute Case Study Presentation Format

Total time: 3 minutes (180 seconds)
Ideal for fast-paced classroom presentations or lightning talks.

1. 🧠 What Happened? (45 seconds)
Name of the case (e.g., Jeep Hack, Heartbleed, Toyota Unintended Acceleration)

System or device involved (car, drone, medical device, etc.)

Summary of the failure

What was the vulnerability?

Who discovered it and how?

2. 🔥 Impact of the Vulnerability (30 seconds)
Real-world consequences:

Safety impact (injuries, deaths)

Financial loss, recalls, legal consequences

How many devices/people were affected?

3. 🛠️ Technical Breakdown (45 seconds)
Vulnerability type (e.g., buffer overflow, command injection, logic flaw)

Which OWASP IoT Top 10 category it maps to (brief explanation)

What secure coding principle was violated (e.g., missing bounds check, no input validation)

4. ✅ How It Could Have Been Prevented (45 seconds)
Secure coding practices that would have prevented it

Mention relevant standard/tools:

CERT C, MISRA, static analysis tools

Input validation, memory safety, use-after-free prevention

Example: “This could’ve been avoided with proper bounds checking and use of safer functions like strncpy instead of strcpy.”