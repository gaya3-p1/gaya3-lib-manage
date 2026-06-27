#include "Book.h"
#include <iostream>

Book::Book(const std::string& isbn, const std::string& title,
           const std::string& author, const std::string& category, int copies)
    : isbn(isbn), title(title), author(author), category(category), copies(copies) {}

std::string Book::getISBN() const { return isbn; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getCategory() const { return category; }
int Book::getCopies() const { return copies; }

void Book::updateCopies(int change) {
    copies += change;
    if (copies < 0) copies = 0;
}

void Book::printDetails() const {
    std::cout << "ISBN: " << isbn
              << " | Title: " << title
              << " | Author: " << author
              << " | Category: " << category
              << " | Copies Available: " << copies
              << std::endl;
}