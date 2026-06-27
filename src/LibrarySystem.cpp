#include "LibrarySystem.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

static const int LOAN_DAYS  = 14;
static const int RENEW_DAYS = 7;

LibrarySystem::LibrarySystem() {
    loadData();
}

Transaction* LibrarySystem::findActiveTransaction(const std::string& studentID,
                                                   const std::string& isbn) {
    for (auto& t : activeTransactions)
        if (t.getStudentID() == studentID && t.getBookISBN() == isbn)
            return &t;
    return nullptr;
}

void LibrarySystem::registerStudent(const std::string& id, const std::string& name,
                                     const std::string& pwd) {
    if (users.count(id)) {
        std::cout << "[ERROR] Student ID '" << id << "' already exists.\n";
        return;
    }
    users.emplace(id, Student(id, name, pwd));
    FileManager::saveUsers(users);
    std::cout << "[OK] Student registered: " << name << " (ID: " << id << ")\n";
}

Student* LibrarySystem::loginStudent(const std::string& id, const std::string& pwd) {
    auto it = users.find(id);
    if (it != users.end() && it->second.authenticate(pwd)) {
        std::cout << "[OK] Login successful! Welcome, " << it->second.getName() << ".\n";
        return &(it->second);
    }
    std::cout << "[ERROR] Invalid Student ID or Password.\n";
    return nullptr;
}

void LibrarySystem::borrowBook(const std::string& studentID, const std::string& isbn) {
    auto bookIt = books.find(isbn);
    if (bookIt == books.end()) {
        std::cout << "[ERROR] Book with ISBN '" << isbn << "' not found.\n";
        return;
    }
    auto userIt = users.find(studentID);
    if (userIt == users.end()) {
        std::cout << "[ERROR] Student not found.\n";
        return;
    }

    if (userIt->second.hasBorrowed(isbn)) {
        std::cout << "[ERROR] You have already borrowed this book.\n";
        return;
    }

    if (bookIt->second.getCopies() > 0) {
        bookIt->second.updateCopies(-1);

        std::string txnID      = Utils::generateID("TXN");
        std::string borrowDate = Utils::getDate();
        std::string dueDate    = Utils::addDays(borrowDate, LOAN_DAYS);

        Transaction t(txnID, studentID, isbn, "borrow", borrowDate, dueDate);
        activeTransactions.push_back(t);

        userIt->second.addBorrowed(isbn);

        FileManager::saveBooks(books);
        FileManager::saveTransactions(activeTransactions);
        FileManager::saveUsers(users);

        std::cout << "[OK] Book borrowed successfully!\n";
        std::cout << "     Title   : " << bookIt->second.getTitle() << "\n";
        std::cout << "     Borrow  : " << borrowDate << "\n";
        std::cout << "     Due     : " << dueDate << "\n";
        std::cout << "     Txn ID  : " << txnID << "\n";
    } else {
        auto& resQueue = reservations[isbn];
        if (resQueue.getISBN().empty()) resQueue = Reservation(isbn);

        if (resQueue.isInQueue(studentID)) {
            std::cout << "[INFO] You are already in the reservation queue for this book.\n";
        } else {
            resQueue.addToQueue(studentID);
            FileManager::saveReservations(reservations);
            std::cout << "[OK] No copies available. You have been added to the reservation queue.\n";
        }
    }
}

void LibrarySystem::returnBook(const std::string& studentID, const std::string& isbn) {
    auto bookIt = books.find(isbn);
    if (bookIt == books.end()) {
        std::cout << "[ERROR] Book with ISBN '" << isbn << "' not found.\n";
        return;
    }
    auto userIt = users.find(studentID);
    if (userIt == users.end()) {
        std::cout << "[ERROR] Student not found.\n";
        return;
    }
    if (!userIt->second.hasBorrowed(isbn)) {
        std::cout << "[ERROR] You have not borrowed this book.\n";
        return;
    }

    Transaction* txn = findActiveTransaction(studentID, isbn);
    std::string returnDate = Utils::getDate();

    if (txn) {
        txn->setReturnDate(returnDate);
        txn->setType("return");
        FileManager::appendToHistory(*txn); 

        activeTransactions.erase(
            std::remove_if(activeTransactions.begin(), activeTransactions.end(),
                [&](const Transaction& t) {
                    return t.getStudentID() == studentID && t.getBookISBN() == isbn;
                }),
            activeTransactions.end());
    }

    bookIt->second.updateCopies(1);
    userIt->second.removeBorrowed(isbn);

    FileManager::saveBooks(books);
    FileManager::saveTransactions(activeTransactions);
    FileManager::saveUsers(users);

    std::cout << "[OK] Book returned: " << bookIt->second.getTitle() << "\n";

    auto resIt = reservations.find(isbn);
    if (resIt != reservations.end() && !resIt->second.isEmpty()) {
        std::string nextStudent = resIt->second.nextStudent();
        FileManager::saveReservations(reservations);
        std::cout << "[INFO] Auto-issuing to next reserved student: " << nextStudent << "\n";
        borrowBook(nextStudent, isbn);
    }
}

void LibrarySystem::renewBook(const std::string& studentID, const std::string& isbn) {
    auto userIt = users.find(studentID);
    if (userIt == users.end() || !userIt->second.hasBorrowed(isbn)) {
        std::cout << "[ERROR] You have not borrowed this book.\n";
        return;
    }

    Transaction* txn = findActiveTransaction(studentID, isbn);
    if (!txn) {
        std::cout << "[ERROR] Active transaction not found.\n";
        return;
    }

    auto resIt = reservations.find(isbn);
    if (resIt != reservations.end() && !resIt->second.isEmpty()) {
        std::cout << "[ERROR] Cannot renew — other students are waiting for this book.\n";
        return;
    }

    std::string newDue = Utils::addDays(txn->getDueDate(), RENEW_DAYS);
    txn->setDueDate(newDue);
    txn->setType("renew");
    FileManager::appendToHistory(*txn);        // record the renewal event
    FileManager::saveTransactions(activeTransactions);

    std::cout << "[OK] Book renewed. New due date: " << newDue << "\n";
}

void LibrarySystem::reserveBook(const std::string& studentID, const std::string& isbn) {
    if (books.find(isbn) == books.end()) {
        std::cout << "[ERROR] Book with ISBN '" << isbn << "' not found.\n";
        return;
    }

    auto& resQueue = reservations[isbn];
    if (resQueue.getISBN().empty()) resQueue = Reservation(isbn);

    if (resQueue.isInQueue(studentID)) {
        std::cout << "[INFO] You are already in the reservation queue.\n";
        return;
    }

    resQueue.addToQueue(studentID);
    FileManager::saveReservations(reservations);
    std::cout << "[OK] Reservation placed for ISBN: " << isbn << "\n";
}

void LibrarySystem::viewBorrowedBooks(const std::string& studentID) const {
    auto userIt = users.find(studentID);
    if (userIt == users.end()) return;

    const auto& isbns = userIt->second.getBorrowedISBNs();
    if (isbns.empty()) {
        std::cout << "[INFO] You have no currently borrowed books.\n";
        return;
    }
    std::cout << "\n--- Currently Borrowed Books ---\n";
    for (const auto& isbn : isbns) {
        auto bookIt = books.find(isbn);
        std::string title = (bookIt != books.end()) ? bookIt->second.getTitle() : "Unknown";
        std::string dueDate = "N/A";
        for (const auto& t : activeTransactions)
            if (t.getStudentID() == studentID && t.getBookISBN() == isbn)
                dueDate = t.getDueDate();
        std::cout << "  ISBN: " << isbn
                  << " | Title: " << title
                  << " | Due: " << dueDate << "\n";
    }
}

void LibrarySystem::viewTransactionHistoryFromCSV(const std::string& studentID) const {
    std::vector<Transaction> transactions;
    FileManager::loadHistory(transactions);          // completed/returned/renewed
    FileManager::loadTransactions(transactions);     // still-active borrows

    std::cout << "\n--- Transaction History for student " << studentID << " ---\n";
    bool found = false;
    for (const auto& t : transactions) {
        if (t.getStudentID() == studentID) {
            found = true;
            auto bookIt = books.find(t.getBookISBN());
            std::string title = (bookIt != books.end()) ? bookIt->second.getTitle() : t.getBookISBN();
            std::cout << "  [" << t.getTransactionID() << "] "
                      << std::left << std::setw(10) << t.getType()
                      << " | Book: " << title
                      << " | Borrowed: " << t.getBorrowDate()
                      << " | Due: " << t.getDueDate();
            if (!t.getReturnDate().empty())
                std::cout << " | Returned: " << t.getReturnDate();
            std::cout << "\n";
        }
    }
    if (!found) {
        std::cout << "  No transactions found.\n";
    }
}

void LibrarySystem::showDashboard() const {
    int totalCopies = 0;
    for (auto it = books.begin(); it != books.end(); ++it) {
        totalCopies += it->second.getCopies();
    }

    std::cout << "\n╔══════════════════════════════════╗\n";
    std::cout <<   "║     LIBRARY DASHBOARD            ║\n";
    std::cout <<   "╠══════════════════════════════════╣\n";
    std::cout <<   "║  Total book titles : " << std::setw(11) << books.size()             << " ║\n";
    std::cout <<   "║  Total copies avail: " << std::setw(11) << totalCopies              << " ║\n";
    std::cout <<   "║  Registered students:" << std::setw(10) << users.size()             << "  ║\n";
    std::cout <<   "║  Active loans      : " << std::setw(11) << activeTransactions.size() << " ║\n";
    std::cout <<   "╚══════════════════════════════════╝\n";
}

void LibrarySystem::showAllBooks() const {
    std::cout << "\n--- All Books in Library ---\n";
    for (auto it = books.begin(); it != books.end(); ++it) {
        it->second.printDetails();
    }
}

void LibrarySystem::loadData() {
    FileManager::loadUsers(users);
    FileManager::loadBooks(books);
    FileManager::loadTransactions(activeTransactions);
    FileManager::loadReservations(reservations);

    for (const auto& t : activeTransactions) {
        auto it = users.find(t.getStudentID());
        if (it != users.end() && !it->second.hasBorrowed(t.getBookISBN()))
            it->second.addBorrowed(t.getBookISBN());
    }
}

void LibrarySystem::saveData() {
    FileManager::saveUsers(users);
    FileManager::saveBooks(books);
    FileManager::saveTransactions(activeTransactions);
    FileManager::saveReservations(reservations);
}
