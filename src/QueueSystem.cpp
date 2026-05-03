#include "QueueSystem.h"
#include <ctime>
#include <iostream>
#include <stdexcept>

/*
 * QUEUE SYSTEM IMPLEMENTATION
 * ===========================
 * FIFO (First-In-First-Out) queue for managing book issue requests.
 *
 * Original C++ code used: queue<Book> q;
 *   q.push(books[id])   → enqueue
 *   q.front() + q.pop() → dequeue
 *
 * This version adds timestamps and user names for tracking.
 */

static std::string getTimestamp() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

// ENQUEUE: Add issue request to the BACK of the queue (FIFO)
void QueueSystem::enqueue(const Book& book, const std::string& userName) {
    IssueRequest req(book, userName, getTimestamp());
    queue.push_back(req);  // Add to back — O(1)
}

// DEQUEUE: Remove and return request from the FRONT (FIFO)
IssueRequest QueueSystem::dequeue() {
    if (queue.empty()) {
        throw std::runtime_error("Queue is empty! No pending issue requests.");
    }
    IssueRequest front = queue.front();    // Get front element
    queue.erase(queue.begin());            // Remove from front — O(n) shift
    return front;
}

// PEEK: View the front request without removing it
IssueRequest QueueSystem::peek() const {
    if (queue.empty()) {
        throw std::runtime_error("Queue is empty!");
    }
    return queue.front();
}

bool QueueSystem::isEmpty() const {
    return queue.empty();
}

int QueueSystem::size() const {
    return static_cast<int>(queue.size());
}

// Get all pending requests (front to back order)
std::vector<IssueRequest> QueueSystem::getAll() const {
    return queue;
}

bool QueueSystem::isBookQueued(int bookId) const {
    for (const auto& req : queue) {
        if (req.book.id == bookId) return true;
    }
    return false;
}

void QueueSystem::clear() {
    queue.clear();
}
