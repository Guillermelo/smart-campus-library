#include "Member.h"

#include <ostream>
#include <utility>

Member::Member(int id, std::string name, std::string email, std::string role)
    : Person(id, std::move(name), std::move(email)), role(std::move(role)) {}

const std::string& Member::getRole() const {
    return role;
}

std::string Member::getDisplayLabel() const {
    return getName() + " (" + role + ")";
}

std::ostream& operator<<(std::ostream& output, const Member& member) {
    output << member.getId() << " - " << member.getDisplayLabel()
           << " - " << member.getEmail();
    return output;
}
