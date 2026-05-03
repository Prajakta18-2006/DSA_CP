#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include "Book.h"
#include "AVLTree.h"
#include "QueueSystem.h"
#include "StackSystem.h"
#include "GraphRecommendation.h"
#include "FileHandler.h"
#include <unordered_map>

/*
 * ============================================
 *         LIBRARY SYSTEM (Controller)
 * ============================================
 * Main controller class that ties together all
 * data structures into a cohesive library system.
 *
 * Components:
 *   AVLTree            → Book storage & search
 *   QueueSystem        → Issue request management
 *   StackSystem        → Return history tracking
 *   GraphRecommendation → Book recommendations
 *   FileHandler        → Data persistence
 *   unordered_map      → O(1) book lookup by ID
 */

class LibrarySystem {
private:
    AVLTree bookTree;                          // AVL Tree for sorted storage
    QueueSystem issueQueue;                    // Queue for issue requests
    StackSystem returnStack;                   // Stack for return history
    GraphRecommendation recGraph;              // Graph for recommendations
    std::unordered_map<int, Book> bookMap;     // Hash map for O(1) lookup

    const std::string DATA_DIR = "data";
    const std::string BOOKS_FILE = "data/books.txt";
    const std::string TRANSACTIONS_FILE = "data/transactions.txt";

    int nextBookId;

    // --- Menu Actions ---
    void addBook();
    void searchBookById();
    void searchBookByName();
    void displayAllBooks();
    void issueBook();
    void processIssue();
    void returnBook();
    void showReturnHistory();
    void addRecommendation();
    void getRecommendations();
    void viewIssueQueue();
    void viewTransactionLog();
    void showStats();

    // --- Helpers ---
    void setupRecommendations();
    void preloadBooks();
    void loadFromFile();
    void saveToFile();
    void displayMenu();
    void displayHeader();
    void clearScreen();
    std::string getCurrentTimestamp();

public:
    LibrarySystem();
    ~LibrarySystem();
    void run();

    // --- Web API Methods ---
    std::vector<Book> getAllBooksApi();
    Book* getBookByIdApi(int id);
    std::vector<Book> searchBooksByNameApi(std::string name);
    bool addBookApi(int id, std::string name, std::string author, std::string genre);
    bool deleteBookApi(int id);
    bool updateBookApi(int id, std::string name, std::string author, std::string genre);
    bool issueBookApi(int id, std::string user);
    IssueRequest processIssueApi();
    std::vector<IssueRequest> getIssueQueueApi();
    bool returnBookApi(int id);
    std::vector<ReturnRecord> getReturnHistoryApi();
    void addRecommendationApi(int a, int b);
    std::vector<int> getRecommendationsApi(int id);
    Book* getBookFromMap(int id);
};

#endif
