#pragma once

#include <iosfwd>
#include <string>

enum class LoanStatus {
    Active,
    Returned
};

class Loan {
public:
    Loan() = default;
    Loan(int id, int bookId, int memberId, std::string borrowedDate, std::string dueDate);

    int getId() const;
    int getBookId() const;
    int getMemberId() const;
    const std::string& getBorrowedDate() const;
    const std::string& getDueDate() const;
    const std::string& getReturnedDate() const;
    LoanStatus getStatus() const;

    bool isActive() const;
    void markReturned(std::string date);
    std::string statusText() const;

private:
    int id = 0;
    int bookId = 0;
    int memberId = 0;
    std::string borrowedDate;
    std::string dueDate;
    std::string returnedDate;
    LoanStatus status = LoanStatus::Active;
};

std::ostream& operator<<(std::ostream& output, const Loan& loan);
