#include "StackSystem.h"
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <algorithm>

/*
 * STACK SYSTEM IMPLEMENTATION
 * ===========================
 * LIFO (Last-In-First-Out) stack for tracking book returns.
 *
 * Original C++ code used: stack<Book> st;
 *   st.push(books[id])  → push return record
 *   st.top() + st.pop() → view/remove most recent
 *
 * This version adds timestamps for each return action.
 */

static std::string getTimestamp() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

// PUSH: Add return record to the TOP of the stack (LIFO)
void StackSystem::push(const Book& book) {
    ReturnRecord record(book, getTimestamp());
    stack.push_back(record);  // Top is at back — O(1)
}

// POP: Remove and return the most recent return record (TOP)
ReturnRecord StackSystem::pop() {
    if (stack.empty()) {
        throw std::runtime_error("Stack is empty! No return records.");
    }
    ReturnRecord topRecord = stack.back();   // Get top (most recent)
    stack.pop_back();                        // Remove from top — O(1)
    return topRecord;
}

// TOP: View most recent return without removing
ReturnRecord StackSystem::top() const {
    if (stack.empty()) {
        throw std::runtime_error("Stack is empty!");
    }
    return stack.back();
}

bool StackSystem::isEmpty() const {
    return stack.empty();
}

int StackSystem::size() const {
    return static_cast<int>(stack.size());
}

/*
 * GET ALL: Returns records in LIFO order (most recent first)
 * This mirrors the showReturn() function from the original code:
 *   stack<Book> temp = st;
 *   while (!temp.empty()) { cout << temp.top(); temp.pop(); }
 */
std::vector<ReturnRecord> StackSystem::getAll() const {
    std::vector<ReturnRecord> result = stack;
    std::reverse(result.begin(), result.end());  // Reverse to show LIFO order
    return result;
}

void StackSystem::clear() {
    stack.clear();
}
