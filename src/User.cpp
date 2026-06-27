#include "User.h"

User::User(const std::string& id, const std::string& name, const std::string& pwd)
    : userID(id), name(name), password(pwd) {}

std::string User::getID() const { return userID; }
std::string User::getName() const { return name; }
std::string User::getPassword() const { return password; }

bool User::authenticate(const std::string& pwd) const {
    return password == pwd;
}