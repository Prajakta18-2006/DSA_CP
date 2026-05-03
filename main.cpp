#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

// -------- Book --------
struct Book {
    int id;
    string name;
    string author;
};

// -------- Storage --------
unordered_map<int, Book> books;

// -------- BST --------
struct Node {
    Book data;
    Node* left;
    Node* right;
};

Node* root = NULL;

Node* newNode(Book b) {
    Node* t = new Node();
    t->data = b;
    t->left = t->right = NULL;
    return t;
}

Node* insertBook(Node* root, Book b) {
    if (root == NULL) return newNode(b);

    if (b.id < root->data.id)
        root->left = insertBook(root->left, b);
    else
        root->right = insertBook(root->right, b);

    return root;
}

Node* findBook(Node* root, int id) {
    if (root == NULL || root->data.id == id)
        return root;

    if (id < root->data.id)
        return findBook(root->left, id);
    else
        return findBook(root->right, id);
}

void showAll(Node* root) {
    if (root == NULL) return;

    showAll(root->left);
    cout << root->data.id << " - " << root->data.name << endl;
    showAll(root->right);
}

// -------- Queue & Stack --------
queue<Book> q;
stack<Book> st;

// -------- Graph --------
unordered_map<int, vector<int>> g;

void addEdge(int a, int b) {
    g[a].push_back(b);
}

// -------- Load 50 Books --------
void loadBooks() {

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
        "Author A","Author B","Author C","Author D","Author E",
        "Author F","Author G","Author H","Author I","Author J",
        "Author K","Author L","Author M","Author N","Author O",
        "Author P","Author Q","Author R","Author S","Author T",
        "Author U","Author V","Author W","Author X","Author Y",
        "Author Z","Author AA","Author BB","Author CC","Author DD",
        "Author EE","Author FF","Author GG","Author HH","Author II",
        "Author JJ","Author KK","Author LL","Author MM","Author NN",
        "Author OO","Author PP","Author QQ","Author RR","Author SS",
        "Author TT","Author UU","Author VV","Author WW","Author XX"
    };

    for (int i = 0; i < 50; i++) {
        Book b;
        b.id = i + 1;
        b.name = names[i];
        b.author = authors[i];

        books[b.id] = b;
        root = insertBook(root, b);
    }

    // sample recommendations
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(5, 6);
    addEdge(10, 11);
    addEdge(20, 21);
}

// -------- Functions --------

void addBook() {
    Book b;
    cout << "Enter id: ";
    cin >> b.id;
    cin.ignore();

    cout << "Enter name: ";
    getline(cin, b.name);

    cout << "Enter author: ";
    getline(cin, b.author);

    books[b.id] = b;
    root = insertBook(root, b);

    cout << "added\n";
}

void searchBook() {
    int id;
    cout << "Enter id: ";
    cin >> id;

    Node* res = findBook(root, id);

    if (res != NULL)
        cout << "Found: " << res->data.name << endl;
    else
        cout << "Not found\n";
}

void displayBooks() {
    cout << "\nBooks list:\n";
    showAll(root);
}

void issueBook() {
    int id;
    cout << "Enter id: ";
    cin >> id;

    if (books.count(id)) {
        q.push(books[id]);
        cout << "added to queue\n";
    } else {
        cout << "no book\n";
    }
}

void processIssue() {
    if (!q.empty()) {
        Book b = q.front();
        q.pop();
        cout << "issued: " << b.name << endl;
    } else {
        cout << "queue empty\n";
    }
}

void returnBook() {
    int id;
    cout << "Enter id: ";
    cin >> id;

    if (books.count(id)) {
        st.push(books[id]);
        cout << "returned\n";
    } else {
        cout << "wrong id\n";
    }
}

void showReturn() {
    stack<Book> temp = st;

    cout << "History:\n";
    while (!temp.empty()) {
        cout << temp.top().name << endl;
        temp.pop();
    }
}

void recommend() {
    int id;
    cout << "Enter id: ";
    cin >> id;

    if (g.count(id)) {
        cout << "You may like:\n";
        for (int x : g[id]) {
            cout << books[x].name << endl;
        }
    } else {
        cout << "no suggestion\n";
    }
}

// -------- Main --------
int main() {
    loadBooks();   // preload 50 books

    int ch;

    do {
        cout << "\n1.Add\n2.Search\n3.Show\n4.Issue\n5.Process\n6.Return\n7.History\n8.Add Rec\n9.Recommend\n0.Exit\n";
        cin >> ch;

        switch (ch) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: displayBooks(); break;
            case 4: issueBook(); break;
            case 5: processIssue(); break;
            case 6: returnBook(); break;
            case 7: showReturn(); break;
            case 8: {
                int a, b;
                cout << "Enter A B: ";
                cin >> a >> b;
                addEdge(a, b);
                break;
            }
            case 9: recommend(); break;
        }

    } while (ch != 0);

    return 0;
}