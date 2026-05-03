#include "AVLTree.h"

/*
 * AVL TREE IMPLEMENTATION
 * =======================
 * This is an upgrade from the original simple BST.
 * Every insert/delete automatically rebalances the tree
 * using rotations to maintain O(log n) height.
 *
 * Balance Factor = height(left) - height(right)
 * If |balance| > 1, we rotate to fix it.
 */

// -------- Private Helpers --------

int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

/*
 * RIGHT ROTATION (LL Case)
 *
 *       y              x
 *      / \            / \
 *     x   T3  =>   T1   y
 *    / \                / \
 *  T1   T2            T2   T3
 */
AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;  // new root of subtree
}

/*
 * LEFT ROTATION (RR Case)
 *
 *     x                y
 *    / \              / \
 *  T1   y    =>     x   T3
 *      / \         / \
 *    T2   T3     T1   T2
 */
AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;  // new root of subtree
}

/*
 * INSERT with AVL balancing
 * After standard BST insert, check balance factor
 * and apply the appropriate rotation case:
 *   LL → rightRotate
 *   RR → leftRotate
 *   LR → leftRotate(left child) then rightRotate
 *   RL → rightRotate(right child) then leftRotate
 */
AVLNode* AVLTree::insertNode(AVLNode* node, Book book) {
    // Standard BST insert
    if (!node) {
        nodeCount++;
        return new AVLNode(book);
    }

    if (book.id < node->data.id)
        node->left = insertNode(node->left, book);
    else if (book.id > node->data.id)
        node->right = insertNode(node->right, book);
    else
        return node;  // duplicate ID, skip

    // Update height of ancestor
    updateHeight(node);

    // Get balance factor
    int balance = getBalance(node);

    // LL Case: Left-heavy & new node in left subtree's left
    if (balance > 1 && book.id < node->left->data.id)
        return rightRotate(node);

    // RR Case: Right-heavy & new node in right subtree's right
    if (balance < -1 && book.id > node->right->data.id)
        return leftRotate(node);

    // LR Case: Left-heavy & new node in left subtree's right
    if (balance > 1 && book.id > node->left->data.id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case: Right-heavy & new node in right subtree's left
    if (balance < -1 && book.id < node->right->data.id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;  // no rotation needed
}

// Standard BST search — O(log n) guaranteed by AVL balancing
AVLNode* AVLTree::searchNode(AVLNode* node, int id) {
    if (!node || node->data.id == id)
        return node;

    if (id < node->data.id)
        return searchNode(node->left, id);
    else
        return searchNode(node->right, id);
}

// Find the node with minimum value (leftmost node)
AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// DELETE with AVL rebalancing
AVLNode* AVLTree::deleteNode(AVLNode* node, int id) {
    if (!node) return nullptr;

    if (id < node->data.id)
        node->left = deleteNode(node->left, id);
    else if (id > node->data.id)
        node->right = deleteNode(node->right, id);
    else {
        // Node found — handle 3 cases
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                delete node;
                node = nullptr;
            } else {
                *node = *temp;
                delete temp;
            }
            nodeCount--;
        } else {
            AVLNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data.id);
        }
    }

    if (!node) return nullptr;

    updateHeight(node);
    int balance = getBalance(node);

    // Rebalance after deletion
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/*
 * IN-ORDER TRAVERSAL → gives books sorted by ID
 * Left → Root → Right
 * This is the same as showAll() from the original C++ code
 */
void AVLTree::inOrderHelper(AVLNode* node, std::vector<Book>& result) {
    if (!node) return;
    inOrderHelper(node->left, result);
    result.push_back(node->data);
    inOrderHelper(node->right, result);
}

// Case-insensitive substring search across all book names
void AVLTree::searchByNameHelper(AVLNode* node, const std::string& query,
                                  std::vector<Book>& results) {
    if (!node) return;

    searchByNameHelper(node->left, query, results);

    // Case-insensitive substring match
    std::string bookName = node->data.name;
    std::string searchQuery = query;
    std::transform(bookName.begin(), bookName.end(), bookName.begin(), ::tolower);
    std::transform(searchQuery.begin(), searchQuery.end(), searchQuery.begin(), ::tolower);

    if (bookName.find(searchQuery) != std::string::npos) {
        results.push_back(node->data);
    }

    searchByNameHelper(node->right, query, results);
}

void AVLTree::destroyTree(AVLNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// -------- Public Methods --------

AVLTree::AVLTree() : root(nullptr), nodeCount(0) {}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::insert(Book book) {
    root = insertNode(root, book);
}

Book* AVLTree::search(int id) {
    AVLNode* result = searchNode(root, id);
    return result ? &(result->data) : nullptr;
}

std::vector<Book> AVLTree::searchByName(const std::string& query) {
    std::vector<Book> results;
    searchByNameHelper(root, query, results);
    return results;
}

std::vector<Book> AVLTree::getAllBooks() {
    std::vector<Book> result;
    inOrderHelper(root, result);
    return result;
}

bool AVLTree::remove(int id) {
    if (!search(id)) return false;
    root = deleteNode(root, id);
    return true;
}

bool AVLTree::update(int id, std::string name, std::string author, std::string genre) {
    AVLNode* node = searchNode(root, id);
    if (!node) return false;
    
    node->data.name = name;
    node->data.author = author;
    node->data.genre = genre;
    return true;
}

int AVLTree::getCount() const {
    return nodeCount;
}
