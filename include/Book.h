#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    std::string category;
    int copies;

public:
    Book(const std::string& isbn, const std::string& title,
         const std::string& author, const std::string& category, int copies);

    std::string getISBN() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getCategory() const;
    int getCopies() const;

    void updateCopies(int change);
    void printDetails() const;
};

#endif
