#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::string stripCR(std::string s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

static std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) tokens.push_back(stripCR(item));
    return tokens;
}

static int safeStoi(const std::string& s) {
    if (s.empty()) return 0;
    try { return std::stoi(s); }
    catch (...) { std::cerr << "[WARN] Invalid int: '" << s << "'\n"; return 0; }
}

void FileManager::loadBooks(std::unordered_map<std::string, Book>& books) {
    std::ifstream file(DataFiles::BOOKS);
    if (!file.is_open()) { std::cerr << "[INFO] books.csv not found.\n"; return; }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string isbn, title, author, category, copiesStr;
        std::getline(ss, isbn,     ',');
        std::getline(ss, title,    ',');
        std::getline(ss, author,   ',');
        std::getline(ss, category, ',');
        std::getline(ss, copiesStr,',');
        isbn     = stripCR(isbn);
        copiesStr= stripCR(copiesStr);
        if (isbn.empty()) continue;
        books.emplace(isbn, Book(isbn, title, author, category, safeStoi(copiesStr)));
    }
}

void FileManager::saveBooks(const std::unordered_map<std::string, Book>& books) {
    std::ofstream file(DataFiles::BOOKS);
    for (auto it = books.begin(); it != books.end(); ++it) {
        const Book& b = it->second;
        file << b.getISBN() << ','
             << b.getTitle() << ','
             << b.getAuthor() << ','
             << b.getCategory() << ','
             << b.getCopies() << '\n';
    }
}

void FileManager::loadUsers(std::unordered_map<std::string, Student>& users) {
    std::ifstream file(DataFiles::USERS);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto t = splitCSV(line);
        if (t.size() >= 3)
            users.emplace(t[0], Student(t[0], t[1], t[2]));
    }
}

void FileManager::saveUsers(const std::unordered_map<std::string, Student>& users) {
    std::ofstream file(DataFiles::USERS);
    for (auto it = users.begin(); it != users.end(); ++it) {
        const Student& s = it->second;
        file << s.getID() << ',' << s.getName() << ',' << s.getPassword() << '\n';
    }
}

void FileManager::loadTransactions(std::vector<Transaction>& transactions) {
    std::ifstream file(DataFiles::TRANSACTIONS);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto t = splitCSV(line);
        if (t.size() >= 6)
            transactions.emplace_back(t[0], t[1], t[2], t[3], t[4], t[5]);
    }
}

void FileManager::saveTransactions(const std::vector<Transaction>& transactions) {
    std::ofstream file(DataFiles::TRANSACTIONS);
    for (const auto& t : transactions) {
        file << t.getTransactionID() << ','
             << t.getStudentID()     << ','
             << t.getBookISBN()      << ','
             << t.getType()          << ','
             << t.getBorrowDate()    << ','
             << t.getDueDate()       << '\n';
    }
}

void FileManager::loadHistory(std::vector<Transaction>& history) {
    std::ifstream file(DataFiles::HISTORY);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto t = splitCSV(line);
        if (t.size() >= 7)
            history.emplace_back(t[0], t[1], t[2], t[3], t[4], t[5], t[6]);
        else if (t.size() >= 6)
            history.emplace_back(t[0], t[1], t[2], t[3], t[4], t[5]);
    }
}

void FileManager::appendToHistory(const Transaction& t) {
    std::ofstream file(DataFiles::HISTORY, std::ios::app);
    file << t.getTransactionID() << ','
         << t.getStudentID()     << ','
         << t.getBookISBN()      << ','
         << t.getType()          << ','
         << t.getBorrowDate()    << ','
         << t.getDueDate()       << ','
         << t.getReturnDate()    << '\n';
}

void FileManager::loadReservations(std::unordered_map<std::string, Reservation>& reservations) {
    std::ifstream file(DataFiles::RESERVATIONS);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto t = splitCSV(line);
        if (t.empty()) continue;
        Reservation r(t[0]);
        for (size_t i = 1; i < t.size(); ++i)
            if (!t[i].empty()) r.addToQueue(t[i]);
        reservations.emplace(t[0], r);
    }
}

void FileManager::saveReservations(const std::unordered_map<std::string, Reservation>& reservations) {
    std::ofstream file(DataFiles::RESERVATIONS);
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        const std::string& key = it->first;
        const Reservation& r = it->second;
        if (r.isEmpty()) continue;
        file << key;
        for (const auto& sid : r.getQueue()) {
            file << ',' << sid;
        }
        file << '\n';
    }
}