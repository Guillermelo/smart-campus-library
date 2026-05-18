#include "Library.h"

#include <algorithm>
#include <chrono>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char character) {
        return static_cast<char>(std::tolower(character));
    });
    return value;
}

std::string todayPlusDays(int days) {
    const auto now = std::chrono::system_clock::now();
    const auto target = now + std::chrono::hours(24 * days);
    const std::time_t time = std::chrono::system_clock::to_time_t(target);
    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::ostringstream output;
    output << std::put_time(&localTime, "%Y-%m-%d");
    return output.str();
}
}

void Library::seedDemoData() {
    if (!books.empty() || !members.empty() || !loans.empty()) {
        return;
    }

    addBook("Clean Code", "Robert C. Martin", 2008, "Software Engineering");
    addBook("Design Patterns", "Erich Gamma et al.", 1994, "Object-Oriented Design");
    addBook("The Pragmatic Programmer", "Andrew Hunt and David Thomas", 1999, "Programming Practice");
    addBook("Introduction to Algorithms", "Thomas H. Cormen et al.", 2009, "Computer Science");

    addMember("Emily Carter", "emily.carter@university.edu", "Student");
    addMember("Daniel Wu", "daniel.wu@university.edu", "Student");
    addMember("Dr. Sophia Green", "sophia.green@university.edu", "Faculty");
}

bool Library::addBook(const std::string& title, const std::string& author, int year, const std::string& category) {
    if (title.empty() || author.empty() || year <= 0 || category.empty()) {
        return false;
    }

    books.emplace_back(nextBookId(), title, author, year, category);
    return true;
}

bool Library::addMember(const std::string& name, const std::string& email, const std::string& role) {
    if (name.empty() || email.empty() || role.empty()) {
        return false;
    }

    members.emplace_back(nextMemberId(), name, email, role);
    return true;
}

bool Library::borrowBook(int bookId, int memberId) {
    const auto bookIndex = findBookIndex(bookId);
    const auto memberIndex = findMemberIndex(memberId);

    if (!bookIndex.has_value() || !memberIndex.has_value() || !books[*bookIndex].isAvailable()) {
        return false;
    }

    books[*bookIndex].markBorrowed();
    loans.emplace_back(nextLoanId(), bookId, memberId, todayPlusDays(0), todayPlusDays(14));
    return true;
}

bool Library::returnBook(int bookId) {
    const auto bookIndex = findBookIndex(bookId);
    const auto loanIndex = findActiveLoanIndexByBook(bookId);

    if (!bookIndex.has_value() || !loanIndex.has_value()) {
        return false;
    }

    books[*bookIndex].markAvailable();
    loans[*loanIndex].markReturned(todayPlusDays(0));
    return true;
}

std::vector<Book> Library::searchBooks(const std::string& keyword) const {
    const auto query = toLower(keyword);
    std::vector<Book> results;

    for (const auto& book : books) {
        const auto searchable = toLower(book.getTitle() + " " + book.getAuthor() + " " + book.getCategory());
        if (searchable.find(query) != std::string::npos) {
            results.push_back(book);
        }
    }

    return results;
}

const std::vector<Book>& Library::getBooks() const {
    return books;
}

const std::vector<Member>& Library::getMembers() const {
    return members;
}

const std::vector<Loan>& Library::getLoans() const {
    return loans;
}

std::vector<Loan> Library::getActiveLoans() const {
    std::vector<Loan> activeLoans;
    for (const auto& loan : loans) {
        if (loan.isActive()) {
            activeLoans.push_back(loan);
        }
    }
    return activeLoans;
}

void Library::replaceData(std::vector<Book> newBooks, std::vector<Member> newMembers, std::vector<Loan> newLoans) {
    books = std::move(newBooks);
    members = std::move(newMembers);
    loans = std::move(newLoans);
}

std::optional<std::size_t> Library::findBookIndex(int bookId) {
    for (std::size_t index = 0; index < books.size(); ++index) {
        if (books[index].getId() == bookId) {
            return index;
        }
    }
    return std::nullopt;
}

std::optional<std::size_t> Library::findMemberIndex(int memberId) const {
    for (std::size_t index = 0; index < members.size(); ++index) {
        if (members[index].getId() == memberId) {
            return index;
        }
    }
    return std::nullopt;
}

std::optional<std::size_t> Library::findActiveLoanIndexByBook(int bookId) {
    for (std::size_t index = 0; index < loans.size(); ++index) {
        if (loans[index].getBookId() == bookId && loans[index].isActive()) {
            return index;
        }
    }
    return std::nullopt;
}

int Library::nextBookId() const {
    int maxId = 0;
    for (const auto& book : books) {
        maxId = std::max(maxId, book.getId());
    }
    return maxId + 1;
}

int Library::nextMemberId() const {
    int maxId = 0;
    for (const auto& member : members) {
        maxId = std::max(maxId, member.getId());
    }
    return maxId + 1;
}

int Library::nextLoanId() const {
    int maxId = 0;
    for (const auto& loan : loans) {
        maxId = std::max(maxId, loan.getId());
    }
    return maxId + 1;
}
