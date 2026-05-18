#pragma once

#include "Book.h"
#include "Loan.h"
#include "Member.h"

#include <string>
#include <vector>

class Storage {
public:
    explicit Storage(std::string baseDirectory);

    bool load(std::vector<Book>& books, std::vector<Member>& members, std::vector<Loan>& loans) const;
    bool save(const std::vector<Book>& books, const std::vector<Member>& members, const std::vector<Loan>& loans) const;

private:
    std::string booksPath() const;
    std::string membersPath() const;
    std::string loansPath() const;

    std::string baseDirectory;
};
