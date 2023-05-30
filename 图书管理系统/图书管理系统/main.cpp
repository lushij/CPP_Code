#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>

class Book {
public:
    Book(const std::string& title, const std::string& author, const std::string& isbn)
        : m_title(title), m_author(author), m_isbn(isbn) {}

    const std::string& getTitle() const {
        return m_title;
    }

    const std::string& getAuthor() const {
        return m_author;
    }

    const std::string& getISBN() const {
        return m_isbn;
    }

private:
    std::string m_title;
    std::string m_author;
    std::string m_isbn;
};

class Library {
public:
    void addBook(const Book& book) {
        m_books.push_back(book);
    }

    void removeBookByISBN(const std::string& isbn) {
        m_books.erase(std::remove_if(m_books.begin(), m_books.end(),
            [&](const Book& book) { return book.getISBN() == isbn; }),
            m_books.end());
    }

    void listBooks() const {
        for (const auto& book : m_books) {
            std::cout << "Title: " << book.getTitle()
                << ", Author: " << book.getAuthor()
                << ", ISBN: " << book.getISBN() << std::endl;
        }
    }

private:
    std::vector<Book> m_books;
};

int main() {
    Library library;
    library.addBook({ "Effective C++", "Scott Meyers", "9780321334879" });
    library.addBook({ "C++ Primer", "Stanley B. Lippman", "9780321714114" });
    library.addBook({ "The C++ Programming Language", "Bjarne Stroustrup", "9780321563842" });

    std::cout << "Library content:\n";
    library.listBooks();

    library.removeBookByISBN("9780321334879");

    std::cout << "Library content after removing a book:\n";
    library.listBooks();

    return 0;
}