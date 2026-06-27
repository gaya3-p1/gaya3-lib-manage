#include "LibrarySystem.h"
#include <iostream>
#include <limits>
#include <string>

int main() {
    LibrarySystem system;
    int choice;

    while (true) {
        std::cout << "\n SMART LIBRARY MANAGEMENT SYSTEM \n\n";
        std::cout << "1. Register Student\n";
        std::cout << "2. Login Student\n";
        std::cout << "3. View all books\n";
        std::cout << "4. Show Dashboard\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        if (choice == 1) {
            std::string id, name, pwd;
            std::cout << "---------------------------------------\n";
            std::cout << "REGISTER HERE.....\n";
            std::cout << "Enter Student ID: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Name: ";
            std::getline(std::cin, name);
            std::cout << "Enter Password: ";
            std::getline(std::cin, pwd);
            system.registerStudent(id, name, pwd);
            std::cout << "\nRegistration completed, you can now Login.\n";
        }
        else if (choice == 2) {
            std::cout << "----------------------------------------\n";
            std::cout << "LOGIN HERE.....\n";
            std::string id, pwd;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter Student ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter Password: ";
            std::getline(std::cin, pwd);

            Student* student = system.loginStudent(id, pwd);
            if (student) {
                int sChoice;
                do {
                    student->displayMenu();
                    std::cout << "Enter choice: ";
                    std::cin >> sChoice;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid choice. Try again.\n";
                        continue;
                    }

                    if (sChoice == 1) {
                        system.showAllBooks();         
                    }
                    else if (sChoice == 2) {
                        std::string isbn;
                        std::cout << "Enter ISBN: ";
                        std::cin >> isbn;
                        system.borrowBook(id, isbn);
                    }
                    else if (sChoice == 3) {
                        std::string isbn;
                        std::cout << "Enter ISBN: ";
                        std::cin >> isbn;
                        system.returnBook(id, isbn);
                    }
                    else if (sChoice == 4) {
                        std::string isbn;
                        std::cout << "Enter ISBN: ";
                        std::cin >> isbn;
                        system.renewBook(id, isbn);
                    }
                    else if (sChoice == 5) {
                        std::string isbn;
                        std::cout << "Enter ISBN: ";
                        std::cin >> isbn;
                        system.reserveBook(id, isbn);
                    }
                    else if (sChoice == 6) {
                        system.viewBorrowedBooks(id);  
                    }
                    else if (sChoice == 7) {
                        system.viewTransactionHistoryFromCSV(id);  
                    }
                    else if (sChoice != 8) {
                        std::cout << "Invalid choice. Try again.\n";
                    }
                } while (sChoice != 8);
                std::cout << "Logged out.\n";
            }
        }
        else if (choice == 3) {
            system.showAllBooks();          
        }
        else if (choice == 4) {
            system.showDashboard();
        }
        else if (choice == 5) {
            system.saveData();
            std::cout << "Exiting system. See you again!\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}