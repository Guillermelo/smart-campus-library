#include "Loan.h"

#include <utility>

Loan::Loan(int id, int bookId, int memberId, std::string borrowedDate, std::string dueDate)
    : id(id),
      bookId(bookId),
      memberId(memberId),
      borrowedDate(std::move(borrowedDate)),
      dueDate(std::move(dueDate)) {}

int Loan::getId() const {
    return id;
}

int Loan::getBookId() const {
    return bookId;
}

int Loan::getMemberId() const {
    return memberId;
}

const std::string& Loan::getBorrowedDate() const {
    return borrowedDate;
}

const std::string& Loan::getDueDate() const {
    return dueDate;
}

const std::string& Loan::getReturnedDate() const {
    return returnedDate;
}

LoanStatus Loan::getStatus() const {
    return status;
}

bool Loan::isActive() const {
    return status == LoanStatus::Active;
}

void Loan::markReturned(std::string date) {
    returnedDate = std::move(date);
    status = LoanStatus::Returned;
}

std::string Loan::statusText() const {
    return isActive() ? "Active" : "Returned";
}

std::ostream& operator<<(std::ostream& output, const Loan& loan) {
    output << "Loan #" << loan.getId()
           << " | Book: " << loan.getBookId()
           << " | Member: " << loan.getMemberId()
           << " | Status: " << loan.statusText();
    return output;
}
