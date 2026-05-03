#ifndef QUEUESYSTEM_H
#define QUEUESYSTEM_H

#include "Book.h"
#include <vector>
#include <string>

/*
 * ============================================
 *            QUEUE SYSTEM (FIFO)
 * ============================================
 *
 * DSA USAGE: Queue is used for the BOOK ISSUE SYSTEM
 *
 * WHY Queue?
 *   - Issue requests are served in FIRST-IN-FIRST-OUT order
 *   - The first person to request a book gets it first
 *   - Fair scheduling — no one gets skipped
 *
 * OPERATIONS:
 *   enqueue() → Add issue request to back of queue
 *   dequeue() → Process (remove) request from front
 *   peek()    → View next request without removing
 *   getAll()  → View entire pending queue
 *
 * IMPLEMENTATION:
 *   Uses std::vector with index 0 as front
 *   enqueue = push_back, dequeue = erase(begin)
 */

struct IssueRequest {
    Book book;
    std::string userName;
    std::string timestamp;

    IssueRequest() {}
    IssueRequest(Book b, const std::string& user, const std::string& time)
        : book(b), userName(user), timestamp(time) {}
};

class QueueSystem {
private:
    std::vector<IssueRequest> queue;

public:
    void enqueue(const Book& book, const std::string& userName);
    IssueRequest dequeue();
    IssueRequest peek() const;
    bool isEmpty() const;
    int size() const;
    std::vector<IssueRequest> getAll() const;
    bool isBookQueued(int bookId) const;
    void clear();
};

#endif
