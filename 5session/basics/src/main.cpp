#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    svr.Get("/set-cookies", [](const httplib::Request& req, httplib::Response& res) {
        // 🍪 Insert multiple cookies with varied attributes
        res.headers.insert({"Set-Cookie", "sessionId=abc123; Path=/;"});
        res.headers.insert({"Set-Cookie", "authToken=secretxyz; Path=/; HttpOnly"});
        res.headers.insert({"Set-Cookie", "secureId=secureVal; Path=/; Secure; SameSite=None"});
        res.headers.insert({"Set-Cookie", "strictMode=on; Path=/; SameSite=Strict"});
        res.headers.insert({"Set-Cookie", "temporary=oneHour; Max-Age=3600; Path=/"});
        

        res.set_content("🍪 Multiple cookies set with custom attributes!", "text/plain");
    });

    svr.Get("/check-cookies", [](const httplib::Request& req, httplib::Response& res) {
        std::string cookie_data = req.get_header_value("Cookie");
        res.set_content("👀 Received Cookies: " + cookie_data, "text/plain");
    });

    std::cout << "🚀 Cookie server running at \n";
    svr.listen("0.0.0.0", 8080);
}
