#ifndef STACKSYSTEM_H
#define STACKSYSTEM_H

#include "Book.h"
#include <vector>
#include <string>

/*
 * ============================================
 *            STACK SYSTEM (LIFO)
 * ============================================
 *
 * DSA USAGE: Stack is used for RETURN HISTORY
 *
 * WHY Stack?
 *   - Return history naturally follows LAST-IN-FIRST-OUT
 *   - Most recent return is shown first (like browser history)
 *   - Undo-style semantics — last action is most relevant
 *
 * OPERATIONS:
 *   push()   → Record a book return (push to top)
 *   pop()    → Remove most recent return record
 *   top()    → View most recent return without removing
 *   getAll() → Traverse stack top-to-bottom (LIFO order)
 *
 * IMPLEMENTATION:
 *   Uses std::vector with back as top
 *   push = push_back, pop = pop_back, top = back
 */

struct ReturnRecord {
    Book book;
    std::string timestamp;

    ReturnRecord() {}
    ReturnRecord(Book b, const std::string& time)
        : book(b), timestamp(time) {}
};

class StackSystem {
private:
    std::vector<ReturnRecord> stack;

public:
    void push(const Book& book);
    ReturnRecord pop();
    ReturnRecord top() const;
    bool isEmpty() const;
    int size() const;
    std::vector<ReturnRecord> getAll() const;  // returns in LIFO order
    void clear();
};

#endif
