#include "Book.h"

#include <utility>

Book::Book(int id, std::string title, std::string author, int year, std::string category)
    : id(id), title(std::move(title)), author(std::move(author)), year(year), category(std::move(category)) {}

int Book::getId() const {
    return id;
}

const std::string& Book::getTitle() const {
    return title;
}

const std::string& Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

const std::string& Book::getCategory() const {
    return category;
}

BookStatus Book::getStatus() const {
    return status;
}

bool Book::isAvailable() const {
    return status == BookStatus::Available;
}

void Book::markBorrowed() {
    status = BookStatus::Borrowed;
}

void Book::markAvailable() {
    status = BookStatus::Available;
}

std::string Book::statusText() const {
    return isAvailable() ? "Available" : "Borrowed";
}

std::ostream& operator<<(std::ostream& output, const Book& book) {
    output << "[" << book.getId() << "] "
           << book.getTitle()
           << " by " << book.getAuthor()
           << " (" << book.getYear() << ") - "
           << book.statusText();
    return output;
}
