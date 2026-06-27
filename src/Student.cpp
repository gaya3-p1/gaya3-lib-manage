#include "Student.h"
#include <algorithm>
#include <iostream>

Student::Student(const std::string& id, const std::string& name, const std::string& pwd)
    : User(id, name, pwd) {}

void Student::addBorrowed(const std::string& isbn) {
    borrowedISBNs.push_back(isbn);
}

void Student::removeBorrowed(const std::string& isbn) {
    auto it = std::find(borrowedISBNs.begin(), borrowedISBNs.end(), isbn);
    if (it != borrowedISBNs.end()) borrowedISBNs.erase(it);
}

bool Student::hasBorrowed(const std::string& isbn) const {
    return std::find(borrowedISBNs.begin(), borrowedISBNs.end(), isbn) != borrowedISBNs.end();
}

const std::vector<std::string>& Student::getBorrowedISBNs() const {
    return borrowedISBNs;
}

void Student::displayMenu() const {
    std::cout << "\n---------- Student Menu [" << name << "] ----------\n";
    std::cout << " | 1. View all Books\n";
    std::cout << " | 2. Borrow Book\n";
    std::cout << " | 3. Return Book\n";
    std::cout << " | 4. Renew Book\n";
    std::cout << " | 5. Reserve Book\n";
    std::cout << " | 6. View Currently Borrowed Books\n";
    std::cout << " | 7. View Full Transaction History\n";
    std::cout << " | 8. Logout\n";
    std::cout << "------------------------------------------------------\n";
}