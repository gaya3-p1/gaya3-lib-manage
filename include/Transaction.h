#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string transactionID;
    std::string studentID;
    std::string bookISBN;
    std::string type;
    std::string borrowDate;
    std::string dueDate;
    std::string returnDate;

public:
    Transaction(const std::string& tid, const std::string& sid,
                const std::string& isbn, const std::string& type,
                const std::string& borrowDate, const std::string& dueDate,
                const std::string& returnDate = "");

    std::string getTransactionID() const;
    std::string getStudentID() const;
    std::string getBookISBN() const;
    std::string getType() const;
    std::string getBorrowDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;

    void setReturnDate(const std::string& d);
    void setType(const std::string& t);
    void setDueDate(const std::string& d);
};

#endif