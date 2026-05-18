# Smart Campus Library System

## Object-Oriented Programming Project Report

**Student:** Guillermo Benitez  
**Course:** Object-Oriented Programming  
**Project Type:** C++ Console Application  
**Language:** C++20  

## 1. Abstract

The Smart Campus Library System is a console-based C++ application designed to manage a small university library. The system allows users to register books, register members, borrow books, return books, search the catalog, list active loans, and save the current state to CSV files.

The project demonstrates object-oriented programming principles through separate domain classes, encapsulated data, business logic separation, and a simple persistence layer. The application is intentionally lightweight so it can be compiled and tested easily in a standard CMake environment.

## 2. Motivation

University libraries need a reliable way to organize books and borrowing records. Even a small department library can become difficult to manage if book availability, member records, and loan dates are tracked manually.

This project solves that problem by providing a simple digital system where the librarian can:

- Maintain a book catalog.
- Register students and faculty members.
- Track which books are currently borrowed.
- Search books by title, author, or category.
- Save data between executions.

## 3. Project Objectives

The main objectives of this project are:

- Apply object-oriented design in a practical C++ project.
- Use classes to represent real-world entities.
- Separate user interface, business logic, and data storage responsibilities.
- Implement a functional menu-driven program.
- Persist application data using local CSV files.
- Produce readable and maintainable source code.

## 4. System Features

The application includes the following features:

- List all books with their availability status.
- List all registered members.
- Add new books to the catalog.
- Add new library members.
- Borrow available books.
- Return borrowed books.
- Search books using a keyword.
- Show all active loans.
- Save and reload data from the `data/` directory.

## 5. Object-Oriented Design

The project is organized around six main classes.

### Book

The `Book` class represents one item in the library catalog. It stores the book ID, title, author, publication year, category, and availability status.

Important responsibilities:

- Store book information.
- Report whether the book is available.
- Change status when the book is borrowed or returned.

### Member

The `Member` class represents a person who can borrow books from the library.

Important responsibilities:

- Store member ID, name, email, and role.
- Provide read-only access to member data through getters.

### Loan

The `Loan` class represents a borrowing transaction between a member and a book.

Important responsibilities:

- Store loan ID, book ID, member ID, borrowed date, due date, and return date.
- Track whether the loan is active or returned.

### Library

The `Library` class contains the main business logic of the system.

Important responsibilities:

- Add books and members.
- Borrow and return books.
- Search books.
- Generate new IDs.
- Keep the collections of books, members, and loans consistent.

### Storage

The `Storage` class handles data persistence.

Important responsibilities:

- Load books, members, and loans from CSV files.
- Save books, members, and loans to CSV files.
- Keep file operations separate from the business logic.

### Menu

The `Menu` class controls the console user interface.

Important responsibilities:

- Display available actions.
- Read user input.
- Call the correct `Library` methods.
- Trigger data saving.

## 6. OOP Principles Applied

### Encapsulation

Class attributes are private, and outside code accesses object data through public methods. For example, a book status can only be changed using `markBorrowed()` or `markAvailable()`.

### Abstraction

The menu does not need to know how loans are stored or how IDs are generated. It only calls high-level methods such as `borrowBook()` and `returnBook()`.

### Separation of Responsibilities

Each class has a specific responsibility. The `Library` class manages rules, `Storage` manages files, and `Menu` manages user interaction.

### Composition

The `Library` class owns collections of `Book`, `Member`, and `Loan` objects. This models the real relationship between a library and its records.

## 7. Folder Structure

```text
OOP_GuillermoBenitez/
├── CMakeLists.txt
├── README.md
├── data/
│   ├── books.csv
│   ├── loans.csv
│   └── members.csv
├── docs/
│   └── class-design.md
├── include/
│   ├── Book.h
│   ├── Library.h
│   ├── Loan.h
│   ├── Member.h
│   ├── Menu.h
│   └── Storage.h
└── src/
    ├── Book.cpp
    ├── Library.cpp
    ├── Loan.cpp
    ├── Member.cpp
    ├── Menu.cpp
    ├── Storage.cpp
    └── main.cpp
```

## 8. Build Instructions

### Requirements

- CMake 3.20 or newer
- A C++20 compatible compiler
- CLion, Visual Studio, MinGW, or another CMake-compatible environment

### Build with CMake

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

### Run

On Windows with a typical CMake debug build:

```bash
.\cmake-build-debug\OOP_GuillermoBenitez.exe
```

If the executable is generated in a configuration subfolder, run:

```bash
.\cmake-build-debug\Debug\OOP_GuillermoBenitez.exe
```

## 9. Example Usage

When the program starts, it loads existing CSV files from `data/`. If no valid files exist, it creates demo records automatically.

Example workflow:

1. Choose `1` to list all books.
2. Choose `2` to list all members.
3. Choose `5` to borrow a book.
4. Enter a valid book ID and member ID.
5. Choose `8` to view active loans.
6. Choose `0` to save and exit.

## 10. Data Persistence

The system stores data in three CSV files:

- `data/books.csv`
- `data/members.csv`
- `data/loans.csv`

This approach is simple and suitable for a small academic project. In a larger system, the storage layer could be replaced by a database without changing the domain classes significantly.

## 11. Limitations

The current version has some intentional limitations:

- CSV values should not contain commas.
- There is no password-based authentication.
- The application is single-user and console-based.
- Loan due dates are fixed at fourteen days.

These limitations keep the project focused on object-oriented programming rather than database design or user management.

## 12. Future Improvements

Possible improvements include:

- Add administrator login.
- Add overdue fine calculation.
- Add sorting and filtering options.
- Export reports to text or PDF.
- Replace CSV storage with SQLite.
- Add automated unit tests.

## 13. Conclusion

The Smart Campus Library System demonstrates a complete object-oriented C++ application with a clear structure, functional user interaction, persistent data storage, and a practical academic use case. The project applies encapsulation, abstraction, composition, and separation of responsibilities while remaining simple enough to understand, compile, and extend.
