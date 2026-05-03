#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Book.h"
#include <vector>
#include <string>

/*
 * ============================================
 *            FILE HANDLER
 * ============================================
 * Handles persistence — saving/loading books
 * and transaction logs to/from text files.
 *
 * File Format (books.txt):
 *   id|name|author|genre|isIssued
 *
 * File Format (transactions.txt):
 *   timestamp|action|bookId|bookName
 */

class FileHandler {
public:
    static void saveBooks(const std::vector<Book>& books, const std::string& filename);
    static std::vector<Book> loadBooks(const std::string& filename);
    static void logTransaction(const std::string& action, const Book& book,
                               const std::string& filename);
    static std::vector<std::string> getTransactionLog(const std::string& filename);
    static bool fileExists(const std::string& filename);
    static void ensureDirectory(const std::string& dirPath);
};

#endif
