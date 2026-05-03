#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

/*
 * ============================================
 *              BOOK CLASS
 * ============================================
 * Represents a single book entity in the library.
 * Each book has a unique ID used as the key in
 * the BST/AVL Tree for efficient searching.
 */
class Book {
public:
    int id;
    std::string name;
    std::string author;
    std::string genre;
    bool isIssued;

    Book();
    Book(int id, const std::string& name, const std::string& author,
         const std::string& genre = "General");

    void display() const;
    std::string toFileString() const;
    static Book fromFileString(const std::string& line);

    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

#endif
