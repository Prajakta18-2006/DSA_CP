#define _WIN32_WINNT 0x0601
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include "LibrarySystem.h"
#include "nlohmann/json.hpp"

#pragma comment(lib, "ws2_32")

using json = nlohmann::json;

LibrarySystem library;

std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

json bookToJson(const Book& b) {
    return {{"id", b.id}, {"name", b.name}, {"author", b.author}, {"genre", b.genre}, {"isIssued", b.isIssued}};
}

void sendResponse(SOCKET clientSocket, int status, const std::string& contentType, const std::string& content) {
    std::stringstream ss;
    ss << "HTTP/1.1 " << status << " OK\r\n";
    ss << "Content-Type: " << contentType << "\r\n";
    ss << "Content-Length: " << content.length() << "\r\n";
    ss << "Access-Control-Allow-Origin: *\r\n";
    ss << "Connection: close\r\n\r\n";
    ss << content;
    std::string response = ss.str();
    send(clientSocket, response.c_str(), response.length(), 0);
}

void handleClient(SOCKET clientSocket) {
    char buffer[4096] = {0};
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        closesocket(clientSocket);
        return;
    }

    std::string request(buffer);
    std::stringstream ss(request);
    std::string method, uri, version;
    ss >> method >> uri >> version;

    std::cout << method << " " << uri << std::endl;

    if (method == "GET") {
        if (uri == "/") sendResponse(clientSocket, 200, "text/html", readFile("templates/index.html"));
        else if (uri == "/style.css") sendResponse(clientSocket, 200, "text/css", readFile("public/style.css"));
        else if (uri == "/script.js") sendResponse(clientSocket, 200, "application/javascript", readFile("public/script.js"));
        else if (uri == "/api/books") {
            auto books = library.getAllBooksApi();
            json j = json::array();
            for (const auto& b : books) j.push_back(bookToJson(b));
            sendResponse(clientSocket, 200, "application/json", j.dump());
        }
        else if (uri.find("/api/books/search") == 0) {
            size_t pos = uri.find("name=");
            std::string name = (pos != std::string::npos) ? uri.substr(pos + 5) : "";
            auto results = library.searchBooksByNameApi(name);
            json j = json::array();
            for (const auto& b : results) j.push_back(bookToJson(b));
            sendResponse(clientSocket, 200, "application/json", j.dump());
        }
        else if (uri == "/api/issue") {
            auto queue = library.getIssueQueueApi();
            json j = json::array();
            for (const auto& r : queue) j.push_back({{"bookId",r.book.id},{"bookName",r.book.name},{"user",r.userName}});
            sendResponse(clientSocket, 200, "application/json", j.dump());
        }
        else if (uri == "/api/return/history") {
            auto history = library.getReturnHistoryApi();
            json j = json::array();
            for (const auto& r : history) j.push_back({{"bookId",r.book.id},{"bookName",r.book.name},{"timestamp",r.timestamp}});
            sendResponse(clientSocket, 200, "application/json", j.dump());
        }
        else if (uri.find("/api/recommend/") == 0) {
            std::string idStr = uri.substr(15);
            size_t end = idStr.find_first_not_of("0123456789");
            int id = std::stoi(idStr.substr(0, end));
            auto recIds = library.getRecommendationsApi(id);
            json j = json::array();
            for (int rid : recIds) {
                Book* b = library.getBookFromMap(rid);
                if (b) j.push_back(bookToJson(*b));
            }
            sendResponse(clientSocket, 200, "application/json", j.dump());
        }
        else {
            sendResponse(clientSocket, 404, "text/plain", "Not Found");
        }
    } 
    else if (method == "POST") {
        size_t bodyPos = request.find("\r\n\r\n");
        std::string body = (bodyPos != std::string::npos) ? request.substr(bodyPos + 4) : "";
        
        if (uri == "/api/books/add") {
            try {
                json x = json::parse(body);
                if (library.addBookApi(x.value("id", 0), x.value("name", ""), x.value("author", ""), x.value("genre", "")))
                    sendResponse(clientSocket, 201, "application/json", "{\"message\":\"Added\"}");
                else sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Exists\"}");
            } catch (...) { sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Invalid JSON\"}"); }
        }
        else if (uri == "/api/books/update") {
            try {
                json x = json::parse(body);
                if (library.updateBookApi(x.value("id", 0), x.value("name", ""), x.value("author", ""), x.value("genre", "")))
                    sendResponse(clientSocket, 200, "application/json", "{\"message\":\"Updated\"}");
                else sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Not found\"}");
            } catch (...) { sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Invalid JSON\"}"); }
        }
        else if (uri == "/api/books/delete") {
            try {
                json x = json::parse(body);
                if (library.deleteBookApi(x.value("id", 0)))
                    sendResponse(clientSocket, 200, "application/json", "{\"message\":\"Deleted\"}");
                else sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Not found\"}");
            } catch (...) { sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Invalid JSON\"}"); }
        }
        else if (uri.find("/api/issue/") == 0 && uri != "/api/issue/process") {
            int id = std::stoi(uri.substr(11));
            std::string user = "Guest";
            try { user = json::parse(body).value("user", "Guest"); } catch (...) {}
            if (library.issueBookApi(id, user)) sendResponse(clientSocket, 200, "application/json", "{\"message\":\"Queued\"}");
            else sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Book already issued or pending in queue\"}");
        }
        else if (uri == "/api/issue/process") {
            try {
                auto req = library.processIssueApi();
                json j = {{"message","Processed"},{"bookName",req.book.name},{"user",req.userName}};
                sendResponse(clientSocket, 200, "application/json", j.dump());
            } catch (...) { sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Empty\"}"); }
        }
        else if (uri == "/api/recommend/add") {
            try {
                json x = json::parse(body);
                library.addRecommendationApi(x["bookA"], x["bookB"]);
                sendResponse(clientSocket, 200, "application/json", "{\"message\":\"Recommendation added\"}");
            } catch (...) { sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Invalid JSON\"}"); }
        }
        else if (uri.find("/api/return/") == 0) {
            int id = std::stoi(uri.substr(12));
            if (library.returnBookApi(id)) sendResponse(clientSocket, 200, "application/json", "{\"message\":\"Returned\"}");
            else sendResponse(clientSocket, 400, "application/json", "{\"error\":\"Not issued\"}");
        }
        else {
            sendResponse(clientSocket, 404, "text/plain", "Not Found");
        }
    }

    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return 1;

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);

    std::cout << "Library Web Server starting on http://localhost:8080" << std::endl;
    library.getRecommendationsApi(1); // Warm up
    
    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket != INVALID_SOCKET) {
            handleClient(clientSocket);
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
