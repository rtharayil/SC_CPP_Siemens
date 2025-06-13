
## 🛡️ Cross-Site Request Forgery (CSRF) Attack

### 🔍 What is CSRF?

**Cross-Site Request Forgery (CSRF)** is a type of web security vulnerability that tricks a user’s browser into executing unwanted actions on a web application in which they are authenticated. It exploits the trust that a web application has in the browser of a logged-in user.

In simple terms, CSRF allows an attacker to perform actions **on behalf of an authenticated user without their consent**.

---

### ⚙️ How CSRF Works

A CSRF attack typically follows these steps:

1. **Victim logs into a legitimate website**, like `bank.com`, and is authenticated (a session cookie is stored in the browser).
2. The **attacker sends the victim a malicious link** (via email, social media, or embedded in an image).
3. When the **victim clicks the link**, their browser **sends a request to the legitimate site using the stored session cookie**.
4. The **web server processes the request**, thinking it was made by the authenticated user.

#### 🔗 Example Attack Scenario:

Victim is logged into: `https://bank.com`

Attacker sends this link:

```html
<img src="https://bank.com/transfer?to=attacker&amount=1000" />
```

When the victim loads this image (e.g., by visiting an attacker-controlled site), the browser sends the request with session cookies — **money gets transferred**.

---

### 🎯 Impact of CSRF

CSRF can lead to:

* Unauthorized fund transfers
* Changed email addresses/passwords
* Deleted accounts
* Privilege escalation (e.g., making a user an admin)

It’s especially dangerous for **state-changing operations** like POST, PUT, or DELETE requests.

---

### ✅ Conditions for CSRF to Succeed

* User is authenticated (session is active).
* Web application **does not validate the origin of the request**.
* Browser **automatically includes credentials** (cookies, HTTP auth headers).

---

### 🛡️ How to Prevent CSRF

#### 1. **Use CSRF Tokens**

* Generate a **random token** per session/form.
* Attach it to all state-changing requests (usually as a hidden form field or request header).
* Server verifies the token before processing the request.

#### 2. **SameSite Cookies**

* Set `SameSite=Strict` or `SameSite=Lax` on cookies.
* Prevents cookies from being sent in cross-origin requests.

```http
Set-Cookie: sessionid=abc123; SameSite=Strict; Secure; HttpOnly
```

#### 3. **Double Submit Cookie Pattern**

* Send a CSRF token in a cookie and as a request header; server compares both values.

#### 4. **Check Referer or Origin Header**

* Validate that requests come from allowed domains.

#### 5. **Avoid GET Requests for State Changes**

* Use POST/PUT for sensitive operations.

---

### 🧪 Example in Practice

#### Without Token (Vulnerable):

```html
<form action="https://bank.com/transfer" method="POST">
  <input name="to" value="attacker" />
  <input name="amount" value="1000" />
  <input type="submit" />
</form>
```

#### With Token (Safe):

```html
<form action="https://bank.com/transfer" method="POST">
  <input name="to" value="attacker" />
  <input name="amount" value="1000" />
  <input type="hidden" name="csrf_token" value="AbC123xYz" />
  <input type="submit" />
</form>
```

Server validates `csrf_token` before proceeding.

---

### 🔐 Summary

| Mitigation              | Description                                 |
| ----------------------- | ------------------------------------------- |
| CSRF Tokens             | Unique per form/session, verified by server |
| SameSite Cookies        | Prevents cookie in cross-site requests      |
| Origin Checks           | Validates `Origin` or `Referer` headers     |
| Avoid GET for Mutations | Prevents CSRF via image/script tags         |


