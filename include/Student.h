#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <vector>
#include <string>

class Student : public User {
private:
    std::vector<std::string> borrowedISBNs; // currently borrowed books

public:
    Student() : User("", "", "") {}
    Student(const std::string& id, const std::string& name, const std::string& pwd);

    void addBorrowed(const std::string& isbn);
    void removeBorrowed(const std::string& isbn);
    bool hasBorrowed(const std::string& isbn) const;
    const std::vector<std::string>& getBorrowedISBNs() const;

    void displayMenu() const override;
};

#endif