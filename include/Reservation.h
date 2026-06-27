#ifndef RESERVATION_H
#define RESERVATION_H

#include <deque>
#include <string>

class Reservation {
private:
    std::string bookISBN;
    std::deque<std::string> studentQueue;

public:
    Reservation() : bookISBN("") {}
    explicit Reservation(const std::string& isbn);

    void addToQueue(const std::string& studentID);
    std::string nextStudent();
    bool isEmpty() const;
    bool isInQueue(const std::string& studentID) const;

    const std::string& getISBN() const { return bookISBN; }
    const std::deque<std::string>& getQueue() const { return studentQueue; }
};

#endif