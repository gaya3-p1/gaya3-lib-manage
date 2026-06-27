# Smart Library Management System
A console-based C++ application for managing a library — handling student registration, book borrowing, returns, renewals, and reservations with full CSV-backed persistence.
 
Books, students, active loans, reservations, and transaction history are stored in flat CSV files in the `data/` directory, so all data persists across sessions.
 
## Data Files
 
| File | Contents |
| --- | --- |
| `data/books.csv` | Book catalogue (ISBN, title, author, category, available copies) |
| `data/users.csv` | Registered students (ID, name, password) |
| `data/transactions.csv` | Currently active borrows |
| `data/history.csv` | Completed transactions (returned/renewed) |
| `data/reservations.csv` | Per-book reservation queues |
 
## Loan Policy
 
| Rule | Value |
| --- | --- |
| Default loan period | 14 days |
| Renewal extension | 7 days |
| Renewal allowed | Only if no other student has reserved the book |
| No copies available | Student is automatically added to the reservation queue |
 
## How to Build and Run
 
```bash
make run
```
 
 The Main Menu :
 
```
 SMART LIBRARY MANAGEMENT SYSTEM
 
1. Register Student
2. Login Student
3. View all books
4. Show Dashboard
5. Exit
Enter your choice:
```
 
## Walkthrough
 
### Registering a new student
 
```
Enter your choice: 1
---------------------------------------
REGISTER HERE.....
Enter Student ID: 24CS10119
Enter Name: Pinninti Gayathri
Enter Password: 12345
Student registered: Pinninti Gayathri (ID: 24CS10119)
 
Registration completed, you can now Login.
```
 
### Logging in
 
```
Enter your choice: 2
----------------------------------------
LOGIN HERE.....
Enter Student ID: 24CS10119
Enter Password: 12345
Login successful! Welcome, Pinninti Gayathri.
 
======= Student Menu [Pinninti Gayathri] =======
1. View all Books
2. Borrow Book
3. Return Book
4. Renew Book
5. Reserve Book
6. View Currently Borrowed Books
7. View Full Transaction History
8. Logout
=========================================
```
 
### Borrowing a book
 
```
Enter ISBN: ISBN067
 Book borrowed successfully! :)
     Title   : Finding Perfect
     Borrow  : 2026-06-27
     Due     : 2026-07-11
     Txn ID  : TXN000004
```
 
### Returning a book
 
```
Enter choice: 3
Enter ISBN: ISBN010
Book returned: The Lord of the Rings
```
 
If another student had reserved the book, it is automatically issued to them:
 
```
Info : Auto-issuing to next reserved student: 24CS11119
```
 
### Renewing a book
 
```
Enter choice: 4
Enter ISBN: ISBN010
Book renewed. New due date: 2026-07-18
```
 
### Reserving a book (no copies available)
 
```
Enter choice: 5
Enter ISBN: ISBN010
No copies available. You have been added to the reservation queue.
```
 
### Viewing currently borrowed books
 
```
Enter choice: 6

 --- Currently Borrowed Books ---
  ISBN: ISBN056 | Title: November 9 | Due: 2026-07-11
  ISBN: ISBN067 | Title: Finding Perfect | Due: 2026-07-11
```
 
### Viewing full transaction history
 
```
Enter choice: 7
 
--- Transaction History for student 24CS10119 ---
  [TXN000003] return     | Book: The Lost World | Borrowed: 2026-06-27 | Due: 2026-07-11 | Returned: 2026-06-27
  [TXN000001] return     | Book: The Lord of the Rings | Borrowed: 2026-06-27 | Due: 2026-07-11 | Returned: 2026-06-27
  [TXN000002] borrow     | Book: November 9 | Borrowed: 2026-06-27 | Due: 2026-07-11
  [TXN000004] borrow     | Book: Finding Perfect | Borrowed: 2026-06-27 | Due: 2026-07-11

```
 
### Dashboard (from main menu)
 
```
Enter your choice: 4
---------------------------------------------------------
|    LIBRARY DASHBOARD
---------------------------------------------------------
|  Total book titles :         105
|  Total copies avail:         572
|  Registered students:        31
|  Active loans      :           2
----------------------------------------------------------
```
 
## Class Structure
 
| Class | Role |
| --- | --- |
| `User` | Abstract base — stores ID, name, password, authentication |
| `Student` | Extends `User` — tracks currently borrowed ISBNs, student menu |
| `Book` | Stores ISBN, title, author, category, available copies |
| `Transaction` | Records a single borrow/renew/return event with dates |
| `Reservation` | FIFO queue of student IDs waiting for a specific book |
| `FileManager` | Static load/save methods for all CSV files |
| `LibrarySystem` | Orchestrates all operations; owns books, users, transactions, reservations |
| `Utils` | Date helpers (`getDate`, `addDays`, `daysBetween`) and ID generator |
