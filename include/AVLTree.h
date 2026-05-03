#ifndef AVLTREE_H
#define AVLTREE_H

#include "Book.h"
#include <vector>
#include <string>
#include <algorithm>

/*
 * ============================================
 *         AVL TREE (Self-Balancing BST)
 * ============================================
 * 
 * DSA USAGE: AVL Tree is used for BOOK STORAGE & SEARCH
 * 
 * WHY AVL over simple BST?
 *   - Simple BST can degrade to O(n) if inserted in order
 *   - AVL guarantees O(log n) for insert, search, delete
 *   - Books are keyed by ID for fast lookup
 *   - In-order traversal gives sorted output (by ID)
 *
 * OPERATIONS:
 *   insert()       → Add book, auto-balance via rotations
 *   search()       → O(log n) search by book ID
 *   searchByName() → O(n) substring search across all nodes
 *   getAllBooks()   → In-order traversal → sorted book list
 *   remove()       → Delete node + rebalance
 *
 * ROTATIONS:
 *   LL Case → Right Rotate
 *   RR Case → Left Rotate
 *   LR Case → Left Rotate child, then Right Rotate
 *   RL Case → Right Rotate child, then Left Rotate
 */

struct AVLNode {
    Book data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Book b) : data(b), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    int nodeCount;

    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    void updateHeight(AVLNode* node);

    // --- AVL Rotations (core balancing logic) ---
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    // --- Recursive helpers ---
    AVLNode* insertNode(AVLNode* node, Book book);
    AVLNode* searchNode(AVLNode* node, int id);
    AVLNode* deleteNode(AVLNode* node, int id);
    AVLNode* minValueNode(AVLNode* node);
    void inOrderHelper(AVLNode* node, std::vector<Book>& result);
    void searchByNameHelper(AVLNode* node, const std::string& query,
                            std::vector<Book>& results);
    void destroyTree(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(Book book);
    Book* search(int id);
    std::vector<Book> searchByName(const std::string& query);
    std::vector<Book> getAllBooks();  // in-order traversal
    bool remove(int id);
    bool update(int id, std::string name, std::string author, std::string genre);
    int getCount() const;
};

#endif
