#pragma once

#include "Book.h"
#include "Loan.h"
#include "Member.h"

#include <optional>
#include <string>
#include <vector>

class Library {
public:
    void seedDemoData();

    bool addBook(const std::string& title, const std::string& author, int year, const std::string& category);
    bool addMember(const std::string& name, const std::string& email, const std::string& role);
    bool borrowBook(int bookId, int memberId);
    bool returnBook(int bookId);

    std::vector<Book> searchBooks(const std::string& keyword) const;
    const std::vector<Book>& getBooks() const;
    const std::vector<Member>& getMembers() const;
    const std::vector<Loan>& getLoans() const;
    std::vector<Loan> getActiveLoans() const;

    void replaceData(std::vector<Book> newBooks, std::vector<Member> newMembers, std::vector<Loan> newLoans);

private:
    std::optional<std::size_t> findBookIndex(int bookId);
    std::optional<std::size_t> findMemberIndex(int memberId) const;
    std::optional<std::size_t> findActiveLoanIndexByBook(int bookId);

    int nextBookId() const;
    int nextMemberId() const;
    int nextLoanId() const;

    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;
};
