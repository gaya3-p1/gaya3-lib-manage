#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include "Student.h"
#include "Book.h"
#include "Reservation.h"
#include "Transaction.h"
#include "FileManager.h"
#include <unordered_map>
#include <vector>
#include <string>

class LibrarySystem {
private:
    std::unordered_map<std::string, Student> users;
    std::unordered_map<std::string, Book> books;
    std::unordered_map<std::string, Reservation> reservations;
    std::vector<Transaction> activeTransactions;

    Transaction* findActiveTransaction(const std::string& studentID, const std::string& isbn);

public:
    LibrarySystem();

    void registerStudent(const std::string& id, const std::string& name, const std::string& pwd);
    Student* loginStudent(const std::string& id, const std::string& pwd);

    void borrowBook(const std::string& studentID, const std::string& isbn);
    void returnBook(const std::string& studentID, const std::string& isbn);
    void renewBook(const std::string& studentID, const std::string& isbn);
    void reserveBook(const std::string& studentID, const std::string& isbn);
    void viewTransactionHistoryFromCSV(const std::string& studentID) const;
    void viewBorrowedBooks(const std::string& studentID) const;

    void showDashboard() const;
    void showAllBooks() const;

    void loadData();
    void saveData();
};

#endif