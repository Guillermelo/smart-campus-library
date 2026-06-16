#pragma once

#include <string>

enum class BookStatus {
    Available,
    Borrowed
};

class Book {
public:
    Book() = default;
    Book(int id, std::string title, std::string author, int year, std::string category);

    int getId() const;
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;
    const std::string& getCategory() const;
    BookStatus getStatus() const;

    bool isAvailable() const;
    void markBorrowed();
    void markAvailable();
    std::string statusText() const;

private:
    int id = 0;
    std::string title;
    std::string author;
    int year = 0;
    std::string category;
    BookStatus status = BookStatus::Available;
};
