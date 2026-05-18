#include "Storage.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <utility>

namespace {
std::vector<std::string> splitCsvLine(const std::string& line) {
    std::vector<std::string> parts;
    std::stringstream stream(line);
    std::string part;

    while (std::getline(stream, part, ',')) {
        parts.push_back(part);
    }

    return parts;
}
}

Storage::Storage(std::string baseDirectory) : baseDirectory(std::move(baseDirectory)) {}

bool Storage::load(std::vector<Book>& books, std::vector<Member>& members, std::vector<Loan>& loans) const {
    books.clear();
    members.clear();
    loans.clear();

    std::ifstream bookFile(booksPath());
    std::ifstream memberFile(membersPath());
    std::ifstream loanFile(loansPath());

    if (!bookFile.good() || !memberFile.good() || !loanFile.good()) {
        return false;
    }

    std::string line;
    while (std::getline(bookFile, line)) {
        const auto parts = splitCsvLine(line);
        if (parts.size() != 6) {
            continue;
        }

        Book book(std::stoi(parts[0]), parts[1], parts[2], std::stoi(parts[3]), parts[4]);
        if (parts[5] == "Borrowed") {
            book.markBorrowed();
        }
        books.push_back(book);
    }

    while (std::getline(memberFile, line)) {
        const auto parts = splitCsvLine(line);
        if (parts.size() != 4) {
            continue;
        }
        members.emplace_back(std::stoi(parts[0]), parts[1], parts[2], parts[3]);
    }

    while (std::getline(loanFile, line)) {
        const auto parts = splitCsvLine(line);
        if (parts.size() != 7) {
            continue;
        }

        Loan loan(std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]), parts[3], parts[4]);
        if (parts[5] == "Returned") {
            loan.markReturned(parts[6]);
        }
        loans.push_back(loan);
    }

    return true;
}

bool Storage::save(const std::vector<Book>& books, const std::vector<Member>& members, const std::vector<Loan>& loans) const {
    std::filesystem::create_directories(baseDirectory);

    std::ofstream bookFile(booksPath());
    std::ofstream memberFile(membersPath());
    std::ofstream loanFile(loansPath());

    if (!bookFile.good() || !memberFile.good() || !loanFile.good()) {
        return false;
    }

    for (const auto& book : books) {
        bookFile << book.getId() << ','
                 << book.getTitle() << ','
                 << book.getAuthor() << ','
                 << book.getYear() << ','
                 << book.getCategory() << ','
                 << book.statusText() << '\n';
    }

    for (const auto& member : members) {
        memberFile << member.getId() << ','
                   << member.getName() << ','
                   << member.getEmail() << ','
                   << member.getRole() << '\n';
    }

    for (const auto& loan : loans) {
        loanFile << loan.getId() << ','
                 << loan.getBookId() << ','
                 << loan.getMemberId() << ','
                 << loan.getBorrowedDate() << ','
                 << loan.getDueDate() << ','
                 << loan.statusText() << ','
                 << loan.getReturnedDate() << '\n';
    }

    return true;
}

std::string Storage::booksPath() const {
    return baseDirectory + "/books.csv";
}

std::string Storage::membersPath() const {
    return baseDirectory + "/members.csv";
}

std::string Storage::loansPath() const {
    return baseDirectory + "/loans.csv";
}
