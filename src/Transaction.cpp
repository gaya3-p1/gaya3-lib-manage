#include "Transaction.h"

Transaction::Transaction(const std::string& tid, const std::string& sid,
                         const std::string& isbn, const std::string& type,
                         const std::string& borrowDate, const std::string& dueDate,
                         const std::string& returnDate)
    : transactionID(tid), studentID(sid), bookISBN(isbn), type(type),
      borrowDate(borrowDate), dueDate(dueDate), returnDate(returnDate) {}

std::string Transaction::getTransactionID() const { return transactionID; }
std::string Transaction::getStudentID() const { return studentID; }
std::string Transaction::getBookISBN() const { return bookISBN; }
std::string Transaction::getType() const { return type; }
std::string Transaction::getBorrowDate() const { return borrowDate; }
std::string Transaction::getDueDate() const { return dueDate; }
std::string Transaction::getReturnDate() const { return returnDate; }

void Transaction::setReturnDate(const std::string& d) { returnDate = d; }
void Transaction::setType(const std::string& t) { type = t; }
void Transaction::setDueDate(const std::string& d) { dueDate = d; }