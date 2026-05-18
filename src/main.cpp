#include "Library.h"
#include "Menu.h"
#include "Storage.h"

#include <iostream>
#include <utility>
#include <vector>

int main() {
    Library library;
    Storage storage("data");

    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

    if (storage.load(books, members, loans)) {
        library.replaceData(std::move(books), std::move(members), std::move(loans));
        std::cout << "Stored library data loaded.\n";
    } else {
        library.seedDemoData();
        storage.save(library.getBooks(), library.getMembers(), library.getLoans());
        std::cout << "Demo library data created.\n";
    }

    Menu menu(library, storage);
    menu.run();
    return 0;
}
