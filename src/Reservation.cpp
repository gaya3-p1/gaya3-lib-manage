#include "Reservation.h"
#include <algorithm>
 
Reservation::Reservation(const std::string& isbn) : bookISBN(isbn) {}
 
void Reservation::addToQueue(const std::string& studentID) {
    studentQueue.push_back(studentID);
}
 
std::string Reservation::nextStudent() {
    if (studentQueue.empty()) return "";
    std::string next = studentQueue.front();
    studentQueue.pop_front();
    return next;
}
 
bool Reservation::isEmpty() const {
    return studentQueue.empty();
}
 
bool Reservation::isInQueue(const std::string& studentID) const {
    return std::find(studentQueue.begin(), studentQueue.end(), studentID) != studentQueue.end();
}