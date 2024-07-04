#include <iostream>
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <openssl/sha.h>

using namespace httplib;
using json = nlohmann::json;

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

void handle_authorize_request(const Request& req, Response& res) {
    // 解析 JSON 请求
    json request_json;
    try {
        request_json = json::parse(req.body);
    } catch (const json::parse_error& e) {
        res.status = 400;
        res.set_content("Invalid JSON request", "text/plain");
        return;
    }

    // 检查请求中是否包含 token
    if (!request_json.contains("token")) {
        res.status = 400;
        res.set_content("Missing 'token' field", "text/plain");
        return;
    }

    std::string token = request_json["token"];

    // 处理请求
    json response_json;
    response_json["status"] = "authorized";
    response_json["token"] = token;

    // 生成 JSON 响应
    res.set_content(response_json.dump(), "application/json");
}

int main() {
    Server svr;

    svr.Post("/authorize", handle_authorize_request);

    std::cout << "Server listening on port 8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}