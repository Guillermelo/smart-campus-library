#include "Member.h"

#include <utility>

Member::Member(int id, std::string name, std::string email, std::string role)
    : id(id), name(std::move(name)), email(std::move(email)), role(std::move(role)) {}

int Member::getId() const {
    return id;
}

const std::string& Member::getName() const {
    return name;
}

const std::string& Member::getEmail() const {
    return email;
}

const std::string& Member::getRole() const {
    return role;
}
