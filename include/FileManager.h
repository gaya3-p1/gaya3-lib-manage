#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Book.h"
#include "Student.h"
#include "Transaction.h"
#include "Reservation.h"
#include <vector>
#include <unordered_map>
#include <string>

namespace DataFiles {
    const std::string BOOKS        = "data/books.csv";
    const std::string USERS        = "data/users.csv";
    const std::string TRANSACTIONS = "data/transactions.csv";  // active borrows only
    const std::string HISTORY      = "data/history.csv";       // completed/returned transactions
    const std::string RESERVATIONS = "data/reservations.csv";
}

class FileManager {
public:
    static void loadBooks(std::unordered_map<std::string, Book>& books);
    static void saveBooks(const std::unordered_map<std::string, Book>& books);

    static void loadUsers(std::unordered_map<std::string, Student>& users);
    static void saveUsers(const std::unordered_map<std::string, Student>& users);

    static void loadTransactions(std::vector<Transaction>& transactions);
    static void saveTransactions(const std::vector<Transaction>& transactions);

    static void loadHistory(std::vector<Transaction>& history);
    static void appendToHistory(const Transaction& t);

    static void loadReservations(std::unordered_map<std::string, Reservation>& reservations);
    static void saveReservations(const std::unordered_map<std::string, Reservation>& reservations);
};

#endif