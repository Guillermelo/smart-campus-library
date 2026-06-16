#include "Menu.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

namespace {
int readInt(const std::string& prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        if (std::cin.eof()) {
            return 0;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

std::string readLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void clearScreen() {
    std::cout << std::string(50, '\n');
}

void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

std::string chooseRole() {
    const std::vector<std::string> roles = {"Student", "Faculty", "Staff"};

    std::cout << "Role options\n";
    for (std::size_t index = 0; index < roles.size(); ++index) {
        std::cout << index + 1 << ". " << roles[index] << '\n';
    }

    while (true) {
        const int option = readInt("Choose role: ");
        if (option >= 1 && option <= static_cast<int>(roles.size())) {
            return roles[option - 1];
        }

        std::cout << "Invalid role option. Try again.\n";
    }
}

bool showAvailableBooksPreview(const Library& library) {
    bool hasAvailableBooks = false;

    std::cout << "\nAvailable books\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(34) << "Title"
              << std::setw(28) << "Author"
              << std::setw(8) << "Year"
              << "Category\n";

    for (const auto& book : library.getBooks()) {
        if (!book.isAvailable()) {
            continue;
        }

        hasAvailableBooks = true;
        std::cout << std::left << std::setw(5) << book.getId()
                  << std::setw(34) << book.getTitle().substr(0, 32)
                  << std::setw(28) << book.getAuthor().substr(0, 26)
                  << std::setw(8) << book.getYear()
                  << book.getCategory().substr(0, 22) << '\n';
    }

    if (!hasAvailableBooks) {
        std::cout << "There are no available books to borrow.\n";
    }

    return hasAvailableBooks;
}
}

Menu::Menu(Library& library, Storage& storage) : library(library), storage(storage) {}

void Menu::run() {
    bool running = true;
    while (running) {
        clearScreen();
        showMainMenu();
        const int option = readInt("Choose an option: ");

        switch (option) {
            case 1: listBooks(); waitForEnter(); break;
            case 2: listMembers(); waitForEnter(); break;
            case 3: addBook(); waitForEnter(); break;
            case 4: addMember(); waitForEnter(); break;
            case 5: borrowBook(); waitForEnter(); break;
            case 6: returnBook(); waitForEnter(); break;
            case 7: searchBooks(); waitForEnter(); break;
            case 8: listActiveLoans(); waitForEnter(); break;
            case 9: saveData(); waitForEnter(); break;
            case 0:
                saveData();
                running = false;
                break;
            default:
                std::cout << "Unknown option.\n";
                waitForEnter();
                break;
        }
    }
}

void Menu::showMainMenu() const {
    std::cout << "\n=== Smart Campus Library System ===\n"
              << "1. List books\n"
              << "2. List members\n"
              << "3. Add book\n"
              << "4. Add member\n"
              << "5. Borrow book\n"
              << "6. Return book\n"
              << "7. Search books\n"
              << "8. List active loans\n"
              << "9. Save data\n"
              << "0. Save and exit\n";
}

void Menu::listBooks() const {
    std::cout << "\nBooks\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(34) << "Title"
              << std::setw(28) << "Author"
              << std::setw(8) << "Year"
              << std::setw(24) << "Category"
              << "Status\n";

    for (const auto& book : library.getBooks()) {
        std::cout << std::left << std::setw(5) << book.getId()
                  << std::setw(34) << book.getTitle().substr(0, 32)
                  << std::setw(28) << book.getAuthor().substr(0, 26)
                  << std::setw(8) << book.getYear()
                  << std::setw(24) << book.getCategory().substr(0, 22)
                  << book.statusText() << '\n';
    }
}

void Menu::listMembers() const {
    std::cout << "\nMembers\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(24) << "Name"
              << std::setw(36) << "Email"
              << "Role\n";

    for (const auto& member : library.getMembers()) {
        std::cout << std::left << std::setw(5) << member.getId()
                  << std::setw(24) << member.getName().substr(0, 22)
                  << std::setw(36) << member.getEmail().substr(0, 34)
                  << member.getRole() << '\n';
    }
}

void Menu::listActiveLoans() const {
    const auto activeLoans = library.getActiveLoans();
    std::cout << "\nActive loans\n";

    if (activeLoans.empty()) {
        std::cout << "There are no active loans.\n";
        return;
    }

    std::cout << std::left << std::setw(8) << "Loan ID"
              << std::setw(8) << "Book"
              << std::setw(10) << "Member"
              << std::setw(14) << "Borrowed"
              << "Due date\n";

    for (const auto& loan : activeLoans) {
        std::cout << std::left << std::setw(8) << loan.getId()
                  << std::setw(8) << loan.getBookId()
                  << std::setw(10) << loan.getMemberId()
                  << std::setw(14) << loan.getBorrowedDate()
                  << loan.getDueDate() << '\n';
    }
}

void Menu::addBook() {
    const auto title = readLine("Title: ");
    const auto author = readLine("Author: ");
    const int year = readInt("Publication year: ");
    const auto category = readLine("Category: ");

    std::cout << (library.addBook(title, author, year, category) ? "Book added.\n" : "Book could not be added.\n");
}

void Menu::addMember() {
    const auto name = readLine("Name: ");
    const auto email = readLine("Email: ");
    const auto role = chooseRole();

    std::cout << (library.addMember(name, email, role) ? "Member added.\n" : "Member could not be added.\n");
}

void Menu::borrowBook() {
    if (!showAvailableBooksPreview(library)) {
        return;
    }

    const int bookId = readInt("Book ID: ");
    const int memberId = readInt("Member ID: ");

    std::cout << (library.borrowBook(bookId, memberId) ? "Loan registered.\n" : "Loan could not be registered.\n");
}

void Menu::returnBook() {
    const int bookId = readInt("Book ID to return: ");
    std::cout << (library.returnBook(bookId) ? "Book returned.\n" : "Return could not be processed.\n");
}

void Menu::searchBooks() const {
    const auto keyword = readLine("Search keyword: ");
    const auto results = library.searchBooks(keyword);

    if (results.empty()) {
        std::cout << "No books matched the keyword.\n";
        return;
    }

    for (const auto& book : results) {
        std::cout << "[" << book.getId() << "] " << book.getTitle()
                  << " by " << book.getAuthor()
                  << " - " << book.statusText() << '\n';
    }
}

void Menu::saveData() const {
    std::cout << (storage.save(library.getBooks(), library.getMembers(), library.getLoans())
                      ? "Data saved.\n"
                      : "Data could not be saved.\n");
}
