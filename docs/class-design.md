# Class Design Notes

The application uses a small object-oriented model focused on responsibility separation.

- `Book` stores bibliographic information and availability state.
- `Member` stores the people who can borrow books.
- `Loan` records the relation between a book and a member over time.
- `Library` owns the main business rules, including borrowing, returning, searching, and ID generation.
- `Storage` handles file persistence and keeps CSV details outside the domain classes.
- `Menu` manages user input and delegates all real work to `Library`.
