#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sys/stat.h>
#ifdef _WIN32
    #include <direct.h>
#endif

/*
 * FILE HANDLER IMPLEMENTATION
 * ===========================
 * Provides persistence for the library system.
 * Books are saved/loaded from a pipe-delimited text file.
 * Transactions are logged with timestamps.
 */

void FileHandler::saveBooks(const std::vector<Book>& books, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "  [ERROR] Could not open file for writing: " << filename << "\n";
        return;
    }

    for (const auto& book : books) {
        file << book.toFileString() << "\n";
    }
    file.close();
}

std::vector<Book> FileHandler::loadBooks(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream file(filename);

    if (!file.is_open()) {
        return books;  // Return empty — file doesn't exist yet
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                books.push_back(Book::fromFileString(line));
            } catch (...) {
                // Skip malformed lines
            }
        }
    }
    file.close();
    return books;
}

void FileHandler::logTransaction(const std::string& action, const Book& book,
                                  const std::string& filename) {
    std::ofstream file(filename, std::ios::app);  // Append mode
    if (!file.is_open()) {
        std::cerr << "  [ERROR] Could not open transaction log: " << filename << "\n";
        return;
    }

    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));

    file << buf << " | " << action << " | ID:" << book.id << " | " << book.name << "\n";
    file.close();
}

std::vector<std::string> FileHandler::getTransactionLog(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (!file.is_open()) return lines;

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    file.close();
    return lines;
}

bool FileHandler::fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void FileHandler::ensureDirectory(const std::string& dirPath) {
    #ifdef _WIN32
        _mkdir(dirPath.c_str());
    #else
        mkdir(dirPath.c_str(), 0777);
    #endif
}
