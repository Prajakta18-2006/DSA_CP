#include "Book.h"

Book::Book() : id(0), name(""), author(""), genre("General"), isIssued(false) {}

Book::Book(int id, const std::string& name, const std::string& author,
           const std::string& genre)
    : id(id), name(name), author(author), genre(genre), isIssued(false) {}

void Book::display() const {
    std::cout << "  +------+--------------------------------+--------------------+------------------+------------+\n";
    std::cout << "  | " << std::left << std::setw(5) << id
              << "| " << std::setw(31) << name
              << "| " << std::setw(19) << author
              << "| " << std::setw(17) << genre
              << "| " << std::setw(11) << (isIssued ? "Issued" : "Available")
              << "|\n";
}

std::string Book::toFileString() const {
    return std::to_string(id) + "|" + name + "|" + author + "|" + genre + "|" +
           std::to_string(isIssued ? 1 : 0);
}

Book Book::fromFileString(const std::string& line) {
    std::istringstream ss(line);
    std::string token;
    Book b;

    if (std::getline(ss, token, '|')) b.id = std::stoi(token);
    std::getline(ss, b.name, '|');
    std::getline(ss, b.author, '|');
    std::getline(ss, b.genre, '|');
    if (std::getline(ss, token, '|')) b.isIssued = (std::stoi(token) == 1);

    return b;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "  | " << std::left << std::setw(5) << book.id
       << "| " << std::setw(31) << book.name
       << "| " << std::setw(19) << book.author
       << "| " << std::setw(17) << book.genre
       << "| " << std::setw(11) << (book.isIssued ? "Issued" : "Available")
       << "|";
    return os;
}
