#include "LibrarySystem.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// -------- Helpers --------

string LibrarySystem::getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

void LibrarySystem::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void LibrarySystem::displayHeader() {
    cout << "\n";
    cout << "  +============================================================+\n";
    cout << "  |                                                            |\n";
    cout << "  |     SMART LIBRARY MANAGEMENT & RECOMMENDATION SYSTEM       |\n";
    cout << "  |                                                            |\n";
    cout << "  |     DSA: AVL Tree | Queue | Stack | Graph                  |\n";
    cout << "  |                                                            |\n";
    cout << "  +============================================================+\n";
}

void LibrarySystem::displayMenu() {
    cout << "\n  +------------------------------------------------------------+\n";
    cout << "  |                      MAIN MENU                             |\n";
    cout << "  +------------------------------------------------------------+\n";
    cout << "  |                                                            |\n";
    cout << "  |   [1]  Add New Book              (AVL Tree Insert)         |\n";
    cout << "  |   [2]  Search Book by ID         (AVL Tree Search)         |\n";
    cout << "  |   [3]  Search Book by Name       (String Matching)         |\n";
    cout << "  |   [4]  Display All Books         (In-Order Traversal)      |\n";
    cout << "  |   [5]  Issue Book                (Queue Enqueue)           |\n";
    cout << "  |   [6]  Process Issue Request     (Queue Dequeue)           |\n";
    cout << "  |   [7]  View Issue Queue          (Queue Display)           |\n";
    cout << "  |   [8]  Return Book               (Stack Push)              |\n";
    cout << "  |   [9]  View Return History       (Stack Traversal)         |\n";
    cout << "  |   [10] Add Recommendation        (Graph Add Edge)          |\n";
    cout << "  |   [11] Get Recommendations       (Graph Adjacency List)    |\n";
    cout << "  |   [12] View Transaction Log      (File Reading)            |\n";
    cout << "  |   [13] Library Statistics                                  |\n";
    cout << "  |   [0]  Save & Exit                                         |\n";
    cout << "  |                                                            |\n";
    cout << "  +------------------------------------------------------------+\n";
    cout << "  Enter choice: ";
}

// -------- Preload 50 Books (same as original C++ code) --------

void LibrarySystem::setupRecommendations() {
    // --- Recommendation Graph Edges (related books) ---
    // CS Core cluster
    recGraph.addEdge(1, 2);   // Data Structures <-> Algorithms
    recGraph.addEdge(1, 4);   // Data Structures <-> C++ Basics
    recGraph.addEdge(2, 14);  // Algorithms <-> Discrete Mathematics

    // Programming cluster
    recGraph.addEdge(3, 4);   // C Programming <-> C++ Basics
    recGraph.addEdge(4, 5);   // C++ Basics <-> Java
    recGraph.addEdge(5, 6);   // Java <-> Python
    recGraph.addEdge(6, 11);  // Python <-> Machine Learning

    // AI/ML cluster
    recGraph.addEdge(11, 12); // ML <-> AI
    recGraph.addEdge(12, 13); // AI <-> Deep Learning
    recGraph.addEdge(11, 30); // ML <-> Data Mining

    // Web Dev cluster
    recGraph.addEdge(21, 22); // Web Dev <-> HTML CSS
    recGraph.addEdge(22, 23); // HTML CSS <-> JavaScript
    recGraph.addEdge(23, 24); // JavaScript <-> React
    recGraph.addEdge(24, 25); // React <-> NodeJS

    // Systems cluster
    recGraph.addEdge(7, 8);   // OS <-> Networks
    recGraph.addEdge(8, 49);  // Networks <-> Networking Basics
    recGraph.addEdge(19, 50); // Cyber Security <-> Ethical Hacking
    recGraph.addEdge(10, 41); // Software Eng <-> Project Management
    recGraph.addEdge(42, 43); // Agile <-> DevOps

    cout << "  [OK] Loaded " << recGraph.totalNodes() << " nodes in recommendation graph\n";
}

void LibrarySystem::preloadBooks() {
    vector<string> names = {
        "Data Structures", "Algorithms", "C Programming", "C++ Basics", "Java Programming",
        "Python Programming", "Operating System", "Computer Networks", "DBMS Concepts", "Software Engineering",
        "Machine Learning", "Artificial Intelligence", "Deep Learning", "Discrete Mathematics", "Digital Logic",
        "Compiler Design", "Theory of Computation", "Cloud Computing", "Cyber Security", "Big Data",
        "Web Development", "HTML CSS", "JavaScript", "React Basics", "NodeJS",
        "Android Development", "iOS Development", "Game Development", "Computer Graphics", "Data Mining",
        "Linear Algebra", "Statistics", "Probability", "Numerical Methods", "Physics",
        "Chemistry", "Mathematics", "English Grammar", "Communication Skills", "Soft Skills",
        "Project Management", "Agile Development", "DevOps", "Blockchain", "IoT",
        "Embedded Systems", "Microprocessors", "Robotics", "Networking Basics", "Ethical Hacking"
    };

    vector<string> authors = {
        "Thomas Cormen", "Robert Sedgewick", "Dennis Ritchie", "Bjarne Stroustrup", "Herbert Schildt",
        "Guido van Rossum", "Abraham Silberschatz", "Andrew Tanenbaum", "Raghu Ramakrishnan", "Ian Sommerville",
        "Tom Mitchell", "Stuart Russell", "Ian Goodfellow", "Kenneth Rosen", "Morris Mano",
        "Alfred Aho", "Michael Sipser", "Rajkumar Buyya", "William Stallings", "Tom White",
        "Jon Duckett", "Elisabeth Robson", "David Flanagan", "Alex Banks", "Shelley Powers",
        "Bill Phillips", "Matt Neuburg", "Jason Gregory", "John Hughes", "Jiawei Han",
        "Gilbert Strang", "Larry Wasserman", "Sheldon Ross", "Steven Chapra", "H.C. Verma",
        "P.W. Atkins", "R.D. Sharma", "Wren & Martin", "Dale Carnegie", "Shiv Khera",
        "Harold Kerzner", "Robert Martin", "Gene Kim", "Andreas Antonopoulos", "Adrian McEwen",
        "Raj Kamal", "B. Ram", "John Craig", "James Kurose", "Jon Erickson"
    };

    vector<string> genres = {
        "CS Core", "CS Core", "Programming", "Programming", "Programming",
        "Programming", "CS Core", "CS Core", "CS Core", "CS Core",
        "AI/ML", "AI/ML", "AI/ML", "Mathematics", "Electronics",
        "CS Core", "CS Core", "Cloud", "Security", "Data Science",
        "Web Dev", "Web Dev", "Web Dev", "Web Dev", "Web Dev",
        "Mobile Dev", "Mobile Dev", "Game Dev", "Graphics", "Data Science",
        "Mathematics", "Mathematics", "Mathematics", "Mathematics", "Science",
        "Science", "Mathematics", "Language", "Soft Skills", "Soft Skills",
        "Management", "Management", "DevOps", "Blockchain", "IoT",
        "Electronics", "Electronics", "Robotics", "Networking", "Security"
    };

    for (int i = 0; i < 50; i++) {
        Book b(i + 1, names[i], authors[i], genres[i]);
        bookTree.insert(b);        // Insert into AVL Tree
        bookMap[b.id] = b;         // Also store in hash map for O(1) lookup
    }

    nextBookId = 51;
    cout << "  [OK] Preloaded 50 books into AVL Tree\n";
}

void LibrarySystem::loadFromFile() {
    vector<Book> books = FileHandler::loadBooks(BOOKS_FILE);
    if (!books.empty()) {
        for (auto& b : books) {
            bookTree.insert(b);
            bookMap[b.id] = b;
            if (b.id >= nextBookId) nextBookId = b.id + 1;
        }
        cout << "  [OK] Loaded " << books.size() << " books from file\n";
    } else {
        preloadBooks();
    }
}

void LibrarySystem::saveToFile() {
    FileHandler::ensureDirectory(DATA_DIR);
    vector<Book> allBooks = bookTree.getAllBooks();
    FileHandler::saveBooks(allBooks, BOOKS_FILE);
    cout << "  [OK] Saved " << allBooks.size() << " books to " << BOOKS_FILE << "\n";
}

// -------- Menu Actions --------

/*
 * ADD BOOK — Uses AVL Tree Insert
 * The book is inserted into the self-balancing AVL tree.
 * After insertion, the tree automatically rebalances via rotations.
 */
void LibrarySystem::addBook() {
    cout << "\n  +----- ADD NEW BOOK (AVL Tree Insert) -----+\n\n";

    int id;
    string name, author, genre;

    cout << "  Enter Book ID (or 0 for auto): ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (id == 0) id = nextBookId;

    if (bookMap.count(id)) {
        cout << "\n  [ERROR] Book with ID " << id << " already exists!\n";
        return;
    }

    cout << "  Enter Book Name: ";
    getline(cin, name);

    cout << "  Enter Author: ";
    getline(cin, author);

    cout << "  Enter Genre: ";
    getline(cin, genre);
    if (genre.empty()) genre = "General";

    Book b(id, name, author, genre);
    bookTree.insert(b);         // AVL Tree insert with auto-balancing
    bookMap[b.id] = b;

    if (id >= nextBookId) nextBookId = id + 1;

    FileHandler::ensureDirectory(DATA_DIR);
    FileHandler::logTransaction("ADDED", b, TRANSACTIONS_FILE);

    cout << "\n  [SUCCESS] Book added successfully! (AVL Tree rebalanced)\n";
    b.display();
}

/*
 * SEARCH BY ID — Uses AVL Tree Search
 * Traverses the tree: go left if id < node, right if id > node
 * Guaranteed O(log n) due to AVL balancing
 */
void LibrarySystem::searchBookById() {
    cout << "\n  +----- SEARCH BOOK BY ID (AVL Tree Search) -----+\n\n";

    int id;
    cout << "  Enter Book ID: ";
    cin >> id;

    Book* found = bookTree.search(id);  // AVL tree search — O(log n)

    if (found) {
        cout << "\n  [FOUND] Book located in AVL Tree:\n";
        cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
        cout << "  | ID   | Name                           | Author             | Genre            | Status     |\n";
        cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
        found->display();
        cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
    } else {
        cout << "\n  [NOT FOUND] No book with ID " << id << " in the AVL Tree.\n";
    }
}

/*
 * SEARCH BY NAME — String matching across all AVL nodes
 * Traverses entire tree (in-order) checking for substring match
 * Case-insensitive comparison
 */
void LibrarySystem::searchBookByName() {
    cout << "\n  +----- SEARCH BOOK BY NAME (String Matching) -----+\n\n";

    string query;
    cout << "  Enter search term: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, query);

    vector<Book> results = bookTree.searchByName(query);

    if (results.empty()) {
        cout << "\n  [NOT FOUND] No books matching \"" << query << "\"\n";
    } else {
        cout << "\n  [FOUND] " << results.size() << " book(s) matching \"" << query << "\":\n";
        cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
        cout << "  | ID   | Name                           | Author             | Genre            | Status     |\n";
        cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
        for (auto& b : results) b.display();
        cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
    }
}

/*
 * DISPLAY ALL BOOKS — Uses AVL Tree In-Order Traversal
 * In-order (Left → Root → Right) gives books sorted by ID
 * This is the same logic as showAll() from the original C++ code
 */
void LibrarySystem::displayAllBooks() {
    cout << "\n  +----- ALL BOOKS (AVL Tree In-Order Traversal) -----+\n\n";

    vector<Book> books = bookTree.getAllBooks();  // In-order traversal

    if (books.empty()) {
        cout << "  [EMPTY] No books in the library.\n";
        return;
    }

    cout << "  Total Books: " << books.size() << "\n\n";
    cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
    cout << "  | ID   | Name                           | Author             | Genre            | Status     |\n";
    cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
    for (auto& b : books) {
        cout << b << "\n";
    }
    cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
}

/*
 * ISSUE BOOK — Uses Queue Enqueue (FIFO)
 * Adds an issue request to the BACK of the queue.
 * Mirrors: q.push(books[id]) from original code
 */
void LibrarySystem::issueBook() {
    cout << "\n  +----- ISSUE BOOK (Queue Enqueue - FIFO) -----+\n\n";

    int id;
    string userName;

    cout << "  Enter Book ID to issue: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!bookMap.count(id)) {
        cout << "\n  [ERROR] Book ID " << id << " not found!\n";
        return;
    }

    if (bookMap[id].isIssued) {
        cout << "\n  [ERROR] Book \"" << bookMap[id].name << "\" is already issued!\n";
        return;
    }

    cout << "  Enter your name: ";
    getline(cin, userName);

    issueQueue.enqueue(bookMap[id], userName);  // Queue enqueue — FIFO

    cout << "\n  [SUCCESS] Issue request added to queue!\n";
    cout << "  Book: " << bookMap[id].name << "\n";
    cout << "  Requested by: " << userName << "\n";
    cout << "  Queue position: " << issueQueue.size() << "\n";

    FileHandler::ensureDirectory(DATA_DIR);
    FileHandler::logTransaction("ISSUE_REQUESTED", bookMap[id], TRANSACTIONS_FILE);
}

/*
 * PROCESS ISSUE — Uses Queue Dequeue (FIFO)
 * Removes the FIRST request from the queue (first come, first served)
 * Mirrors: q.front() + q.pop() from original code
 */
void LibrarySystem::processIssue() {
    cout << "\n  +----- PROCESS ISSUE (Queue Dequeue - FIFO) -----+\n\n";

    if (issueQueue.isEmpty()) {
        cout << "  [EMPTY] No pending issue requests in the queue.\n";
        return;
    }

    try {
        IssueRequest req = issueQueue.dequeue();  // Queue dequeue — front removal

        // Mark book as issued
        Book* treeBook = bookTree.search(req.book.id);
        if (treeBook) treeBook->isIssued = true;
        if (bookMap.count(req.book.id)) bookMap[req.book.id].isIssued = true;

        cout << "  [ISSUED] Book processed successfully!\n";
        cout << "  Book: " << req.book.name << " (ID: " << req.book.id << ")\n";
        cout << "  Issued to: " << req.userName << "\n";
        cout << "  Requested at: " << req.timestamp << "\n";
        cout << "  Remaining in queue: " << issueQueue.size() << "\n";

        FileHandler::ensureDirectory(DATA_DIR);
        FileHandler::logTransaction("ISSUED to " + req.userName, req.book, TRANSACTIONS_FILE);
    } catch (const exception& e) {
        cout << "  [ERROR] " << e.what() << "\n";
    }
}

// View the current issue queue
void LibrarySystem::viewIssueQueue() {
    cout << "\n  +----- ISSUE QUEUE (FIFO Order) -----+\n\n";

    if (issueQueue.isEmpty()) {
        cout << "  [EMPTY] No pending issue requests.\n";
        return;
    }

    vector<IssueRequest> all = issueQueue.getAll();
    cout << "  Pending requests: " << all.size() << "\n\n";
    cout << "  +-----+------+--------------------------------+--------------------+---------------------+\n";
    cout << "  | Pos | ID   | Book Name                      | Requested By       | Time                |\n";
    cout << "  +-----+------+--------------------------------+--------------------+---------------------+\n";

    for (size_t i = 0; i < all.size(); i++) {
        cout << "  | " << left << setw(4) << (i + 1)
             << "| " << setw(5) << all[i].book.id
             << "| " << setw(31) << all[i].book.name
             << "| " << setw(19) << all[i].userName
             << "| " << setw(20) << all[i].timestamp << "|\n";
    }
    cout << "  +-----+------+--------------------------------+--------------------+---------------------+\n";
}

/*
 * RETURN BOOK — Uses Stack Push (LIFO)
 * Pushes the returned book onto the stack.
 * Most recent return is always on top.
 * Mirrors: st.push(books[id]) from original code
 */
void LibrarySystem::returnBook() {
    cout << "\n  +----- RETURN BOOK (Stack Push - LIFO) -----+\n\n";

    int id;
    cout << "  Enter Book ID to return: ";
    cin >> id;

    if (!bookMap.count(id)) {
        cout << "\n  [ERROR] Book ID " << id << " not found!\n";
        return;
    }

    if (!bookMap[id].isIssued) {
        cout << "\n  [ERROR] Book \"" << bookMap[id].name << "\" is not currently issued!\n";
        return;
    }

    // Mark book as available
    Book* treeBook = bookTree.search(id);
    if (treeBook) treeBook->isIssued = false;
    bookMap[id].isIssued = false;

    returnStack.push(bookMap[id]);  // Stack push — LIFO

    cout << "\n  [SUCCESS] Book returned successfully!\n";
    cout << "  Book: " << bookMap[id].name << " (ID: " << id << ")\n";
    cout << "  Return history size: " << returnStack.size() << "\n";

    FileHandler::ensureDirectory(DATA_DIR);
    FileHandler::logTransaction("RETURNED", bookMap[id], TRANSACTIONS_FILE);
}

/*
 * RETURN HISTORY — Uses Stack Traversal (LIFO order)
 * Shows most recent returns first (top of stack).
 * Mirrors showReturn() from original code:
 *   stack<Book> temp = st;
 *   while (!temp.empty()) { cout << temp.top(); temp.pop(); }
 */
void LibrarySystem::showReturnHistory() {
    cout << "\n  +----- RETURN HISTORY (Stack - LIFO Order) -----+\n\n";

    if (returnStack.isEmpty()) {
        cout << "  [EMPTY] No return records.\n";
        return;
    }

    vector<ReturnRecord> all = returnStack.getAll();  // Returns in LIFO order
    cout << "  Total returns: " << all.size() << " (most recent first)\n\n";
    cout << "  +-----+------+--------------------------------+---------------------+\n";
    cout << "  | #   | ID   | Book Name                      | Returned At         |\n";
    cout << "  +-----+------+--------------------------------+---------------------+\n";

    for (size_t i = 0; i < all.size(); i++) {
        cout << "  | " << left << setw(4) << (i + 1)
             << "| " << setw(5) << all[i].book.id
             << "| " << setw(31) << all[i].book.name
             << "| " << setw(20) << all[i].timestamp << "|\n";
    }
    cout << "  +-----+------+--------------------------------+---------------------+\n";
}

/*
 * ADD RECOMMENDATION — Uses Graph Add Edge
 * Connects two books in the adjacency list (bidirectional).
 * Mirrors: addEdge(a, b) from original code
 */
void LibrarySystem::addRecommendation() {
    cout << "\n  +----- ADD RECOMMENDATION (Graph Edge) -----+\n\n";

    int a, b;
    cout << "  Enter Book ID A: ";
    cin >> a;
    cout << "  Enter Book ID B: ";
    cin >> b;

    if (!bookMap.count(a) || !bookMap.count(b)) {
        cout << "\n  [ERROR] One or both book IDs not found!\n";
        return;
    }

    recGraph.addEdge(a, b);  // Graph add edge — bidirectional

    cout << "\n  [SUCCESS] Recommendation edge added!\n";
    cout << "  \"" << bookMap[a].name << "\" <--> \"" << bookMap[b].name << "\"\n";
}

/*
 * GET RECOMMENDATIONS — Uses Graph Adjacency List Lookup
 * Returns all neighbors of the given book node.
 * Mirrors: for (int x : g[id]) { cout << books[x].name; }
 */
void LibrarySystem::getRecommendations() {
    cout << "\n  +----- GET RECOMMENDATIONS (Graph Lookup) -----+\n\n";

    int id;
    cout << "  Enter Book ID: ";
    cin >> id;

    if (!bookMap.count(id)) {
        cout << "\n  [ERROR] Book ID " << id << " not found!\n";
        return;
    }

    cout << "\n  Recommendations for: \"" << bookMap[id].name << "\" (ID: " << id << ")\n\n";

    vector<int> recs = recGraph.getRecommendations(id);  // Graph adjacency lookup

    if (recs.empty()) {
        cout << "  [NONE] No recommendations available for this book.\n";
        return;
    }

    cout << "  +------+--------------------------------+--------------------+------------------+\n";
    cout << "  | ID   | Recommended Book               | Author             | Genre            |\n";
    cout << "  +------+--------------------------------+--------------------+------------------+\n";
    for (int recId : recs) {
        if (bookMap.count(recId)) {
            cout << "  | " << left << setw(5) << recId
                 << "| " << setw(31) << bookMap[recId].name
                 << "| " << setw(19) << bookMap[recId].author
                 << "| " << setw(17) << bookMap[recId].genre << "|\n";
        }
    }
    cout << "  +------+--------------------------------+--------------------+------------------+\n";
}

void LibrarySystem::viewTransactionLog() {
    cout << "\n  +----- TRANSACTION LOG -----+\n\n";

    vector<string> logs = FileHandler::getTransactionLog(TRANSACTIONS_FILE);

    if (logs.empty()) {
        cout << "  [EMPTY] No transactions recorded yet.\n";
        return;
    }

    cout << "  Total transactions: " << logs.size() << "\n\n";
    for (auto& line : logs) {
        cout << "  " << line << "\n";
    }
}

void LibrarySystem::showStats() {
    cout << "\n  +----- LIBRARY STATISTICS -----+\n\n";
    cout << "  Total Books (AVL Tree):      " << bookTree.getCount() << "\n";
    cout << "  Pending Issues (Queue):      " << issueQueue.size() << "\n";
    cout << "  Return Records (Stack):      " << returnStack.size() << "\n";
    cout << "  Recommendation Nodes (Graph): " << recGraph.totalNodes() << "\n";
    cout << "  Recommendation Edges (Graph): " << recGraph.totalEdges() << "\n";

    // Count issued books
    int issued = 0;
    for (auto& pair : bookMap) {
        if (pair.second.isIssued) issued++;
    }
    cout << "  Books Currently Issued:      " << issued << "\n";
    cout << "  Books Available:             " << (bookTree.getCount() - issued) << "\n";
}

// -------- Constructor / Destructor --------

LibrarySystem::LibrarySystem() : nextBookId(1) {
    FileHandler::ensureDirectory(DATA_DIR);
    displayHeader();
    cout << "\n  Initializing library...\n\n";
    loadFromFile();
    setupRecommendations();  // Always setup recommendations
    cout << "\n  System ready!\n";
}

LibrarySystem::~LibrarySystem() {
    saveToFile();
}

// -------- Main Run Loop --------

void LibrarySystem::run() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n  [ERROR] Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:  addBook();            break;
            case 2:  searchBookById();     break;
            case 3:  searchBookByName();   break;
            case 4:  displayAllBooks();    break;
            case 5:  issueBook();          break;
            case 6:  processIssue();       break;
            case 7:  viewIssueQueue();     break;
            case 8:  returnBook();         break;
            case 9:  showReturnHistory();  break;
            case 10: addRecommendation();  break;
            case 11: getRecommendations(); break;
            case 12: viewTransactionLog(); break;
            case 13: showStats();          break;
            case 0:
                cout << "\n  Saving data and exiting...\n";
                saveToFile();
                cout << "  Goodbye!\n\n";
                break;
            default:
                cout << "\n  [ERROR] Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

// --- Web API Methods Implementation ---

std::vector<Book> LibrarySystem::getAllBooksApi() {
    return bookTree.getAllBooks();
}

Book* LibrarySystem::getBookByIdApi(int id) {
    return bookTree.search(id);
}

std::vector<Book> LibrarySystem::searchBooksByNameApi(std::string name) {
    return bookTree.searchByName(name);
}

bool LibrarySystem::addBookApi(int id, std::string name, std::string author, std::string genre) {
    if (id <= 0) id = nextBookId++;
    if (bookMap.count(id)) return false;
    
    Book b(id, name, author, genre);
    bookTree.insert(b);
    bookMap[id] = b;
    if (id >= nextBookId) nextBookId = id + 1;
    saveToFile();
    return true;
}

bool LibrarySystem::deleteBookApi(int id) {
    if (!bookMap.count(id)) return false;
    bookTree.remove(id);
    bookMap.erase(id);
    saveToFile();
    return true;
}

bool LibrarySystem::updateBookApi(int id, std::string name, std::string author, std::string genre) {
    if (!bookMap.count(id)) return false;
    bookTree.update(id, name, author, genre);
    bookMap[id].name = name;
    bookMap[id].author = author;
    bookMap[id].genre = genre;
    saveToFile();
    return true;
}

bool LibrarySystem::issueBookApi(int id, std::string user) {
    if (!bookMap.count(id)) return false;
    
    // Check if book is already issued OR already pending in the queue
    if (bookMap[id].isIssued || issueQueue.isBookQueued(id)) {
        return false; 
    }

    issueQueue.enqueue(bookMap[id], user);
    FileHandler::logTransaction("API_ISSUE_REQUEST", bookMap[id], TRANSACTIONS_FILE);
    return true;
}

IssueRequest LibrarySystem::processIssueApi() {
    if (issueQueue.isEmpty()) throw std::runtime_error("Queue empty");

    IssueRequest req = issueQueue.dequeue();
    
    // Double check availability (safety check)
    if (bookMap[req.book.id].isIssued) {
        throw std::runtime_error("Book already issued!");
    }

    Book* treeBook = bookTree.search(req.book.id);
    if (treeBook) treeBook->isIssued = true;
    bookMap[req.book.id].isIssued = true;

    FileHandler::logTransaction("API_ISSUED to " + req.userName, req.book, TRANSACTIONS_FILE);
    return req;
}

std::vector<IssueRequest> LibrarySystem::getIssueQueueApi() {
    return issueQueue.getAll();
}

bool LibrarySystem::returnBookApi(int id) {
    if (!bookMap.count(id) || !bookMap[id].isIssued) return false;

    Book* treeBook = bookTree.search(id);
    if (treeBook) treeBook->isIssued = false;
    bookMap[id].isIssued = false;

    returnStack.push(bookMap[id]);
    FileHandler::logTransaction("API_RETURNED", bookMap[id], TRANSACTIONS_FILE);
    return true;
}

std::vector<ReturnRecord> LibrarySystem::getReturnHistoryApi() {
    return returnStack.getAll();
}

void LibrarySystem::addRecommendationApi(int a, int b) {
    if (bookMap.count(a) && bookMap.count(b)) {
        recGraph.addEdge(a, b);
    }
}

std::vector<int> LibrarySystem::getRecommendationsApi(int id) {
    return recGraph.getRecommendations(id);
}

Book* LibrarySystem::getBookFromMap(int id) {
    if (bookMap.count(id)) return &bookMap[id];
    return nullptr;
}

