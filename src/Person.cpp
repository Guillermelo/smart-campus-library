#include "Person.h"

#include <utility>

Person::Person(int id, std::string name, std::string email)
    : id(id), name(std::move(name)), email(std::move(email)) {}

int Person::getId() const {
    return id;
}

const std::string& Person::getName() const {
    return name;
}

const std::string& Person::getEmail() const {
    return email;
}

std::string Person::getDisplayLabel() const {
    return name + " <" + email + ">";
}
