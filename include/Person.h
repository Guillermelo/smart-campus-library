#pragma once

#include <string>

class Person {
public:
    Person() = default;
    Person(int id, std::string name, std::string email);
    virtual ~Person() = default;

    int getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;

    virtual std::string getDisplayLabel() const = 0;

private:
    int id = 0;
    std::string name;
    std::string email;
};
