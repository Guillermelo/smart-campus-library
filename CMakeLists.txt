cmake_minimum_required(VERSION 3.20)
project(OOP_GuillermoBenitez LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OOP_GuillermoBenitez
        src/main.cpp
        src/Person.cpp
        src/Book.cpp
        src/Loan.cpp
        src/Member.cpp
        src/Library.cpp
        src/Storage.cpp
        src/Menu.cpp
)

target_include_directories(OOP_GuillermoBenitez PRIVATE include)
