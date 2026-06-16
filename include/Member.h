#pragma once

#include <string>

class Member {
public:
    Member() = default;
    Member(int id, std::string name, std::string email, std::string role);

    int getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getRole() const;

private:
    int id = 0;
    std::string name;
    std::string email;
    std::string role;
};
