

## 🔁 What Are Tracking Cookies?

A **tracking cookie** is a cookie that allows a **third party** (like an ad network or analytics provider) to monitor your activity **across multiple websites**.

These are typically set by **embedding third-party resources** (scripts/images/iframes) from a **different domain** (e.g., `tracker.com`) on many sites.

---

## 🎯 Goal: Re-identify the same user on multiple websites

---

## 🧭 Step-by-Step Flow

### 🎥 Scenario:

You visit three different websites:

* `news.com`
* `shopping.com`
* `sports.com`

All of them include a third-party ad/image from `tracker.com`.

### 🔄 Flow Diagram

```
Browser                news.com                tracker.com
   |                       |                         |
   | --> GET /            --> <html>... <img src="https://tracker.com/ad.png"> ... |
   |                       |                         |
   |                       | -------> GET /ad.png --->|
   |                       |                         |
   |                       | <--- Set-Cookie: user=abc123
   |                       |<------------------------|
   |                       |
--- Now visit shopping.com ---
   | --> GET /            --> <img src="https://tracker.com/ad.png">
   |                       |-------> GET /ad.png with Cookie: user=abc123
   |                       |                         |
   |                       | <-- 200 OK               |
   |                       |                         |
   --> Tracker knows it's the same user as before
```

---

## 🔍 Detailed Flow

### 1. **Visit `news.com`**

* Page includes:

  ```html
  <img src="https://tracker.com/track?id=news">
  ```
* Browser requests this image.
* **`tracker.com` sets a cookie**: `Set-Cookie: user=abc123; Domain=tracker.com`

### 2. **Visit `shopping.com`**

* Includes the same tracker:

  ```html
  <script src="https://tracker.com/track.js"></script>
  ```
* Browser sends cookie `user=abc123` to `tracker.com` again.
* **Tracker knows it's the same person visiting multiple sites.**

---



