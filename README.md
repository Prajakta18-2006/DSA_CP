# 📚 Smart Library Management & Recommendation System

A modern, high-performance **Full-Stack Web Application** built entirely with **C++** on the backend. This project showcases the implementation of advanced Data Structures and Algorithms (DSA) to solve real-world library management problems.

## 🚀 Features

-   **Real-time Book Management**: Add, Edit, Search, and Delete books using an AVL Tree for $O(\log n)$ performance.
-   **FIFO Issue System**: Manages book issuance through a Queue to ensure fair service.
-   **LIFO Return History**: Tracks return transactions using a Stack.
-   **Graph-based Recommendations**: Suggests related books using an Adjacency List Graph representation.
-   **Web Dashboard**: A sleek, responsive interface built with Vanilla JS and CSS.
-   **Persistent Storage**: Automatically saves all book data and transactions to local files.

## 🧠 Data Structures Used

| Feature | Data Structure | Rationale |
| :--- | :--- | :--- |
| **Book Storage** | **AVL Tree** | Ensures the tree remains balanced, providing guaranteed $O(\log n)$ search and insertion. |
| **Search (O(1))** | **Hash Map** | An `unordered_map` is used alongside the tree for instant lookup by Book ID. |
| **Issue System** | **Queue** | Implements First-In-First-Out (FIFO) logic for pending book requests. |
| **Return History** | **Stack** | Implements Last-In-First-Out (LIFO) logic to show the most recent returns first. |
| **Recommendations**| **Graph** | Uses an Adjacency List to model complex relationships between related books. |

## 🛠 Tech Stack

-   **Backend**: C++ (C++17)
-   **Networking**: Raw WinSock2 (Windows Sockets)
-   **JSON Parsing**: [nlohmann/json](https://github.com/nlohmann/json)
-   **Frontend**: HTML5, CSS3 (Vanilla), JavaScript (Vanilla)

## 📂 Project Structure

```text
├── include/              # Header files (.h)
├── src/                  # Implementation files (.cpp)
│   └── web_main.cpp      # Main entry point for the Web Server
├── templates/            # HTML templates
├── public/               # Static assets (CSS, JS)
├── data/                 # Persistent storage (books.txt, transactions.txt)
├── compile_web.bat       # Build script for Windows
└── README.md             # This file
```

## ⚙️ How to Run

### Prerequisites
- **MinGW-w64** (or any C++ compiler with WinSock support).
- Windows OS (uses `ws2_32.lib`).

### Steps to Run
1.  **Clone/Extract** the project to your local machine.
2.  **Compile**: Run the `compile_web.bat` script. This will generate `library_web_server.exe`.
    ```bash
    .\compile_web.bat
    ```
3.  **Run Server**: Execute the generated `.exe`.
    ```bash
    .\library_web_server.exe
    ```
4.  **Access App**: Open your web browser and navigate to:
    👉 **[http://localhost:8080](http://localhost:8080)**

## 🤝 For Team Members

- **Adding Logic**: Most of the core logic resides in `LibrarySystem.cpp`.
- **Modifying UI**: Update `templates/index.html` for structure and `public/script.js` for interactivity.
- **Data Preservation**: The system automatically creates a `data/` folder. Do not delete `books.txt` unless you want to reset the library.
- **Port**: The server runs on port `8080` by default. You can change this in `src/web_main.cpp`.

---
Developed for **Data Structures & Algorithms (CP)** project.
