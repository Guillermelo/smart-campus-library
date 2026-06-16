# Smart Campus Library System

**Student Name:** Guillermo Benitez  
**Course:** Object-Oriented Programming  
**Project Title:** Smart Campus Library System  
**Programming Language:** C++20  

## 1. Problem Definition

The problem addressed by this project is the manual management of a small university library. In many academic environments, books, members, and borrowing records may be tracked using paper forms or simple spreadsheets. This can cause several issues, such as duplicated records, difficulty checking book availability, lack of loan history, and mistakes when returning borrowed books.

The objective of the Smart Campus Library System is to provide a simple console-based application that helps a librarian manage books, members, and loans in an organized way. The system allows the user to add books, add members, borrow books, return books, search the catalog, list active loans, and save data to files. The project focuses on applying object-oriented programming concepts in a practical and understandable C++ application.

## 2. Project Objectives

The main objectives of this project are:

- To design a functional C++ application using object-oriented programming.
- To represent real-world library entities using classes and objects.
- To separate business logic, user interface logic, and file storage logic.
- To allow users to manage books, members, and loan records.
- To save and load data using CSV files.
- To create a project structure that is easy to understand, maintain, and extend.

## 3. System Overview

The Smart Campus Library System is a menu-driven console application. When the program starts, it loads existing data from the `data` folder. If no valid data exists, it creates demo data automatically. The user can then interact with the system through a text menu.

The system supports the following operations:

- List all books.
- List all registered members.
- Add a new book.
- Add a new member.
- Borrow an available book.
- Return a borrowed book.
- Search books by keyword.
- List active loans.
- Save data.

The program stores information in three CSV files: `books.csv`, `members.csv`, and `loans.csv`.

## 4. OOP Concepts Used

This project applies several object-oriented programming concepts.

### Classes and Objects

The project uses classes to model the main entities of the system. For example, the `Book` class represents a book, the `Member` class represents a library user, and the `Loan` class represents a borrowing transaction. During execution, the program creates objects from these classes and stores them in collections managed by the `Library` class.

### Encapsulation

Encapsulation is used by keeping class attributes private and exposing only controlled public methods. For example, the `Book` class does not allow direct access to its status. Instead, the status is changed through methods such as `markBorrowed()` and `markAvailable()`. This protects the internal state of the object and prevents invalid modifications.

### Abstraction

Abstraction is applied by hiding implementation details behind simple methods. The menu does not need to know how a loan is created internally. It only calls the `borrowBook()` method from the `Library` class. This makes the program easier to use and easier to modify.

### Composition

Composition is used in the `Library` class. A library contains collections of books, members, and loans. This models the real-world relationship where a library owns and manages these records.

## 5. Program Design

The project is divided into several classes, each with a clear responsibility.

### Book Class

The `Book` class stores information about a book, including its ID, title, author, year, category, and availability status. It also provides methods to check whether the book is available and to update its status.

### Member Class

The `Member` class represents a person who can borrow books from the library. It stores the member ID, name, email, and role, such as Student or Faculty.

### Loan Class

The `Loan` class represents a borrowing operation. It stores the loan ID, book ID, member ID, borrowed date, due date, returned date, and loan status.

### Library Class

The `Library` class contains the main business logic. It manages books, members, and loans. It is responsible for adding records, borrowing books, returning books, searching books, and generating new IDs.

### Storage Class

The `Storage` class handles file persistence. It loads and saves data using CSV files. This keeps file handling separate from the main library logic.

### Menu Class

The `Menu` class handles the console interface. It displays the options, reads user input, and calls the appropriate methods from the `Library` class.

## 6. Modular Structure

The project is organized into folders to keep the code clean:

```text
include/    Header files with class declarations
src/        C++ source files with class implementations
data/       CSV files used for storage
docs/       Extra design documentation
README.md  Main project report and instructions
```

This structure separates declarations from implementations and makes the project easier to navigate.

## 7. Algorithm Description

The borrowing process works as follows:

1. The user selects the borrow option from the menu.
2. The system asks for the book ID and member ID.
3. The `Library` class checks whether the book exists.
4. The `Library` class checks whether the member exists.
5. The system verifies that the book is currently available.
6. If all conditions are valid, the book is marked as borrowed.
7. A new loan record is created with the current date and a due date fourteen days later.
8. The user receives a confirmation message.

The return process works as follows:

1. The user selects the return option.
2. The system asks for the book ID.
3. The `Library` class searches for an active loan related to that book.
4. If an active loan exists, the book is marked as available.
5. The loan is marked as returned.
6. The return date is saved.

## 8. Implementation and Output

The application was implemented in C++20 using CMake. It can be compiled from the command line or executed directly from CLion. The program displays a text menu where the user can choose the desired operation.

The console interface was improved to make the program easier to use. When adding a member, the user no longer has to type the role manually. Instead, the program displays role options such as Student, Faculty, and Staff, and the user selects one by number. This reduces typing mistakes and keeps member roles consistent in the saved data.

The borrowing process was also improved. Before asking for the book ID, the program displays a preview of all available books. This preview shows the book ID, title, author, year, and category. Because of this, the user can choose a valid available book without having to go back to the full book list first.

After each menu operation, the program waits for the user to press Enter and then clears the terminal screen. This keeps the console clean and makes the application easier to read during repeated use.

Example menu:

```text
=== Smart Campus Library System ===
1. List books
2. List members
3. Add book
4. Add member
5. Borrow book
6. Return book
7. Search books
8. List active loans
9. Save data
0. Save and exit
```

Example test case:

```text
Input:
1

Expected result:
The system displays the list of books with their ID, title, author, year, category, and status.
```

Another test case:

```text
Input:
5
Available books:
1 Clean Code
2 Design Patterns
Book ID: 1
Member ID: 1

Expected result:
The system registers a new loan and marks the selected book as borrowed.
```

Another test case:

```text
Input:
4
Name: John Smith
Email: john.smith@university.edu
Role options:
1. Student
2. Faculty
3. Staff
Choose role: 1

Expected result:
The system adds the member with the Student role.
```

## 9. Code Quality

The code was written with readability and maintainability in mind. Class names use clear nouns such as `Book`, `Member`, `Loan`, `Library`, `Storage`, and `Menu`. Method names describe the action they perform, such as `addBook()`, `borrowBook()`, `returnBook()`, and `searchBooks()`.

The project avoids placing all logic inside the `main()` function. Instead, responsibilities are divided among different classes. Input handling is located in the `Menu` class, business rules are located in the `Library` class, and file operations are located in the `Storage` class.

Basic error handling is included. For example, the program checks whether a book exists, whether a member exists, and whether a book is available before creating a loan.

## 10. Innovation and Complexity

Although the project is a console application, it includes several features that make it more complete than a basic CRUD program. It includes persistent data storage, automatic demo data creation, active loan tracking, due date generation, keyword search, role selection, an available-book preview during borrowing, and a cleaner terminal workflow.

The program was designed so it can be extended in the future. For example, the CSV storage layer could be replaced by a database without changing the main domain classes significantly.

## 11. How to Compile and Run

Open PowerShell in the project folder:

```powershell
cd C:\Users\Guillermo\CLionProjects\OOP_GuillermoBenitez
```

Configure the project:

```powershell
cmake -S . -B build-verify
```

Build the project:

```powershell
cmake --build build-verify --config Debug
```

Run the executable:

```powershell
.\build-verify\Debug\OOP_GuillermoBenitez.exe
```

The project can also be opened and executed from CLion by selecting the `OOP_GuillermoBenitez` target and pressing Run.

## 12. Limitations

The current version has some limitations:

- It uses CSV files instead of a real database.
- CSV fields should not contain commas.
- It does not include user authentication.
- It is designed for one user at a time.
- The due date is fixed at fourteen days after the borrowing date.
- The interface is console-based, not graphical.

## 13. Future Improvements

Possible future improvements include:

- Add administrator login.
- Add overdue fine calculation.
- Add more detailed search filters.
- Add sorting by title, author, or year.
- Add SQLite database support.
- Add unit tests.
- Add a graphical user interface.
- Generate automatic reports for active and returned loans.

## 14. Conclusion

The Smart Campus Library System is a complete object-oriented C++ project that solves a practical library management problem. It demonstrates the use of classes, objects, encapsulation, abstraction, composition, and responsibility separation. The project is organized into multiple files and folders, making the code easier to understand and maintain.

The application is functional because it allows users to manage books, members, and loans through a console menu. It also saves and loads data using CSV files, so information is preserved between executions. Overall, the project meets the requirements of an Object-Oriented Programming assignment and provides a solid base for future improvements.

## 15. Viva / Presentation Explanation

My project is a Smart Campus Library System developed in C++20. It is a console application that helps manage books, members, and book loans in a university library. The user can add books, add members, borrow books, return books, search books, view active loans, and save data.

The most important class is `Library`, because it controls the main logic of the program. The `Book`, `Member`, and `Loan` classes represent the main real-world entities. The `Storage` class manages CSV file saving and loading, while the `Menu` class handles the console interface.

This project uses object-oriented programming because data and behavior are grouped into classes. Encapsulation is used because class attributes are private. Abstraction is used because the menu calls simple methods such as `borrowBook()` without knowing the internal details. Composition is used because the `Library` class contains collections of books, members, and loans. The project is modular, functional, and easy to extend.
