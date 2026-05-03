/*
 * ================================================================
 *   SMART LIBRARY MANAGEMENT & BOOK RECOMMENDATION SYSTEM
 * ================================================================
 *
 *   Data Structures Used:
 *
 *   1. AVL TREE (Self-Balancing BST)
 *      - Where: Book storage, search by ID, sorted display
 *      - Why: O(log n) insert, search, delete guaranteed
 *      - Files: AVLTree.h, AVLTree.cpp
 *
 *   2. QUEUE (FIFO - First In First Out)
 *      - Where: Book issue request management
 *      - Why: Fair ordering — first request gets served first
 *      - Files: QueueSystem.h, QueueSystem.cpp
 *
 *   3. STACK (LIFO - Last In First Out)
 *      - Where: Book return history tracking
 *      - Why: Most recent return shown first (like undo history)
 *      - Files: StackSystem.h, StackSystem.cpp
 *
 *   4. GRAPH (Adjacency List)
 *      - Where: Book recommendation system
 *      - Why: Models "related books" relationships efficiently
 *      - Files: GraphRecommendation.h, GraphRecommendation.cpp
 *
 *   Additional:
 *   - File handling for persistence (FileHandler)
 *   - Hash Map (unordered_map) for O(1) book lookup
 *   - String matching for search by name
 *
 *   Compile: g++ -std=c++17 -I include src/*.cpp -o smart_library
 *   Run:     ./smart_library (Linux/Mac) or smart_library.exe (Windows)
 *
 * ================================================================
 */

#include "LibrarySystem.h"

int main() {
    LibrarySystem library;
    library.run();
    return 0;
}
