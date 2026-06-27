#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string userID;
    std::string name;
    std::string password;

public:
    User(const std::string& id, const std::string& name, const std::string& pwd);
    virtual ~User() = default;

    std::string getID() const;
    std::string getName() const;
    std::string getPassword() const;
    bool authenticate(const std::string& pwd) const;

    virtual void displayMenu() const = 0;
};

#endif