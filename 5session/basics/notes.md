Cookies are small pieces of data stored by a web browser at the request of a server. They are used to maintain stateful information across HTTP requests (which are otherwise stateless), such as session management, user preferences, tracking, and authentication.

---

## 🔹 Cookie Attributes (Explained)

| Attribute                  | Description                                                                             |
| -------------------------- | --------------------------------------------------------------------------------------- |
| **Name=Value**             | Core content of the cookie (key-value pair).                                            |
| **Expires** or **Max-Age** | Controls the lifespan of the cookie. `Expires` is a date-time; `Max-Age` is in seconds. |
| **Domain**                 | Specifies the domain for which the cookie is valid.                                     |
| **Path**                   | Restricts the cookie to a specific path on the domain.                                  |
| **Secure**                 | If present, the cookie will only be sent over HTTPS.                                    |
| **HttpOnly**               | Prevents access to the cookie via JavaScript (`document.cookie`), reducing XSS risk.    |
| **SameSite**               | Controls cross-site request behavior:                                                   |

* `Strict`: Only same-site requests.
* `Lax`: Cross-site allowed for top-level navigation (like clicking a link).
* `None`: Fully cross-site; **must** be `Secure`. |

---

### 🔹 Example: HTTP Set-Cookie Header

```http
Set-Cookie: sessionId=abc123; Secure; HttpOnly; Path=/; Max-Age=3600; SameSite=Strict
```

---

## 🔹 Setting Cookies in C++ (using raw HTTP)

While C++ doesn’t provide a built-in HTTP server or cookie API like some higher-level languages, you can simulate one using sockets or libraries like **Crow**, **cpp-httplib**, or **Boost.Beast**.

### ✅ Simple C++ Example using Crow (a lightweight C++ web framework)

#### 1. **Install Crow** (via vcpkg or manually)

#### 2. **Example Code: Set a Cookie**

```cpp
#include "crow_all.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/set-cookie")
    ([](const crow::request& req) {
        crow::response res("Cookie is set");
        
        // Setting the Set-Cookie header
        res.add_header("Set-Cookie", "sessionId=abc123; Path=/; Max-Age=3600; HttpOnly; Secure; SameSite=Strict");

        return res;
    });

    app.port(18080).multithreaded().run();
}
```

#### ➕ You can now access: `http://localhost:18080/set-cookie`

* It returns a header like:

  ```
  Set-Cookie: sessionId=abc123; Path=/; Max-Age=3600; HttpOnly; Secure; SameSite=Strict
  ```

---

## 🔹 Notes on Security Best Practices

| Goal                    | Use These Attributes       |
| ----------------------- | -------------------------- |
| Prevent JS access (XSS) | `HttpOnly`                 |
| Prevent MITM attacks    | `Secure`                   |
| Prevent CSRF            | `SameSite=Strict` or `Lax` |
| Set session lifetime    | `Max-Age` or `Expires`     |

---

### 🔹 Testing with `curl`

```bash
curl -i http://localhost:18080/set-cookie
```


