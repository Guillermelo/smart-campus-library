#pragma once

#include "Person.h"

#include <iosfwd>
#include <string>

class Member : public Person {
public:
    Member() = default;
    Member(int id, std::string name, std::string email, std::string role);

    const std::string& getRole() const;
    std::string getDisplayLabel() const override;

private:
    std::string role;
};

std::ostream& operator<<(std::ostream& output, const Member& member);
