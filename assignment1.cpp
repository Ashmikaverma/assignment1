#include <iostream>
#include<string>
#include <vector>
#include<algorithm>


using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    double price;
    int quantity;

    Book(string t, string a, string i, double p, int q)
        : title(t), author(a), isbn(i), price(p), quantity(q) {}

    void display() {
        cout << "Book: " << title << " by " << author
             << " (ISBN: " << isbn << "), Price: $" << price
             << ", Quantity: " << quantity << endl;
    }
};

class Magazine {
public:
    string title;
    string issueNumber;
    double price;
    int quantity;

    Magazine(string t, string i, double p, int q)
        : title(t), issueNumber(i), price(p), quantity(q) {}

    void display() {
        cout << "Magazine: " << title << " (Issue: " << issueNumber
             << "), Price: $" << price << ", Quantity: " << quantity << endl;
    }
};

class Inventory {
public:
    vector<Book> books;
    vector<Magazine> magazines;

    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addMagazine(const Magazine& magazine) {
        magazines.push_back(magazine);
    }

    void removeBook(string isbn) {
        auto it = find_if(books.begin(), books.end(), [&isbn](Book& book) {
            return book.isbn == isbn;
        });
        if (it != books.end()) {
            cout << "Removed book: " << it->title << endl;
            books.erase(it);
        } else {
            cout << "Book with ISBN " << isbn << " not found in inventory." << endl;
        }
    }

    void removeMagazine(string issueNumber) {
        auto it = find_if(magazines.begin(), magazines.end(), [&issueNumber](Magazine& magazine) {
            return magazine.issueNumber == issueNumber;
        });
        if (it != magazines.end()) {
            cout << "Removed magazine: " << it->title << endl;
            magazines.erase(it);
        } else {
            cout << "Magazine with ISSN " << issueNumber << " not found in inventory." << endl;
        }
    }

    void applyDiscount(string itemKey, bool isBook, double discountPercent) {
        if (isBook) {
            auto it = find_if(books.begin(), books.end(), [&itemKey](Book& book) {
                return book.isbn == itemKey;
            });
            if (it != books.end()) {
                it->price -= (it->price * discountPercent / 100);
                cout << "Applied " << discountPercent << "% discount to book: " << it->title << endl;
            } else {
                cout << "Book with ISBN " << itemKey << " not found in inventory." << endl;
            }
        } else {
            auto it = find_if(magazines.begin(), magazines.end(), [&itemKey](Magazine& magazine) {
                return magazine.issueNumber == itemKey;
            });
            if (it != magazines.end()) {
                it->price -= (it->price * discountPercent / 100);
                cout << "Applied " << discountPercent << "% discount to magazine: " << it->title << endl;
            } else {
                cout << "Magazine with ISSN " << itemKey << " not found in inventory." << endl;
            }
        }
    }
 void sellBook(string isbn, int qty) {
        for (auto& book : books) {
            if (book.isbn == isbn) {
                if (book.quantity >= qty) {
                    book.quantity -= qty;
                    cout << "Sold " << qty << " copies of " << book.title << endl;
                } else {
                    cout << "Not enough stock for " << book.title << endl;
                }
                return;
            }
        }
        cout << "Book not found in inventory!" << endl;
    }

    void sellMagazine(string issueNumber, int qty) {
        for (auto& magazine : magazines) {
            if (magazine.issueNumber == issueNumber) {
                if (magazine.quantity >= qty) {
                    magazine.quantity -= qty;
                    cout << "Sold " << qty << " copies of " << magazine.title << endl;
                } else {
                    cout << "Not enough stock for " << magazine.title << endl;
                }
                return;
            }
        }
        cout << "Magazine not found in inventory!" << endl;
    }

    void displayInventory() {
        cout << "\nBooks in Inventory:" << endl;
        for (auto& book : books) {
            book.display();
        }
        cout << "\nMagazines in Inventory:" << endl;
        for (auto& magazine : magazines) {
            magazine.display();
        }
    }
};

class Person {
public:
    string name;

    Person(string n) : name(n) {}
};

class Manager : public Person {
public:
    Manager(string n) : Person(n) {}

    void addBookToInventory(Inventory& inventory) {
        string title, author, isbn;
        double price;
        int quantity;

        cout << "Enter book details:" << endl;
        cout << "Title: ";
        cin.ignore(); 
        getline(cin, title);

        cout << "Author: ";
        getline(cin, author);

        cout << "ISBN: ";
        cin >> isbn;

        cout << "Price: ";
        cin >> price;

        cout << "Quantity: ";
        cin >> quantity;

        inventory.addBook(Book(title, author, isbn, price, quantity));
        cout << name << " added the book: " << title << " to inventory." << endl;
    }

    void addMagazineToInventory(Inventory& inventory) {
        string title, issueNumber;
        double price;
        int quantity;

        cout << "Enter magazine details:" << endl;
        cout << "Title: ";
        cin.ignore(); 
        getline(cin, title);

        cout << "ISSN: ";
        cin >> issueNumber;

        cout << "Price: ";
        cin >> price;

        cout << "Quantity: ";
        cin >> quantity;

        inventory.addMagazine(Magazine(title, issueNumber, price, quantity));
        cout << name << " added the magazine: " << title << " to inventory." << endl;
    }

    void removeBookFromInventory(Inventory& inventory) {
        string isbn;
        cout << "Enter ISBN of the book to remove: ";
        cin >> isbn;
        inventory.removeBook(isbn);
    }

    void removeMagazineFromInventory(Inventory& inventory) {
        string issueNumber;
        cout << "Enter ISSN of the magazine to remove: ";
        cin >> issueNumber;
        inventory.removeMagazine(issueNumber);
    }

    void applyDiscountToItem(Inventory& inventory) {
        string itemKey;
        bool isBook;
        double discountPercent;

        cout << "Enter 1 for Book or 0 for Magazine: ";
        cin >> isBook;
        cout << "Enter " << (isBook ? "ISBN" : "ISSN") << ": ";
        cin >> itemKey;
        cout << "Enter discount percentage: ";
        cin >> discountPercent;

        inventory.applyDiscount(itemKey, isBook, discountPercent);
    }
};
class Cashier : public Person {
public:
    Cashier(string n) : Person(n) {}

    void sellItem(Inventory& inventory, string itemKey, int qty, bool isBook) {
        if (isBook) {  
            inventory.sellBook(itemKey, qty);
        } else {
            inventory.sellMagazine(itemKey, qty);
        }
    }
};

class Customer : public Person {
public:
    Customer(string n) : Person(n) {}

    void buyItem(Cashier& cashier, Inventory& inventory) {
        string itemKey;
        int qty;
        bool isBook;

        cout << "Enter 1 to buy a Book or 0 to buy a Magazine: ";
        cin >> isBook;
        cout << "Enter " << (isBook ? "ISBN" : "ISSN") << ": ";
        cin >> itemKey;
        cout << "Enter quantity: ";
        cin >> qty;

        cashier.sellItem(inventory, itemKey, qty, isBook);
    }
};
int main() {
    Inventory inventory;

    
 
    string managerName;
    cout << "Enter store manager's name: "<<endl;
    cin>>managerName;
    Manager manager(managerName);
    string CashierName;
    cout << "Enter store cashier's name: "<<endl;
    cin>>CashierName;
    Cashier cashier(CashierName);

    while (true) {
        cout << "\n1. Add Book to Inventory" << endl;
        cout << "2. Add Magazine to Inventory" << endl;
        cout << "3. Remove Book from Inventory" << endl;
        cout << "4. Remove Magazine from Inventory" << endl;
        cout << "5. Apply Discount" << endl;
        cout << "6. Display Inventory" << endl;
        cout << "7. Customer Purchase"<<endl;;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            manager.addBookToInventory(inventory);
            break;
        case 2:
            manager.addMagazineToInventory(inventory);
            break;
        case 3:
            manager.removeBookFromInventory(inventory);
            break;
        case 4:
            manager.removeMagazineFromInventory(inventory);
            break;
        case 5:
            manager.applyDiscountToItem(inventory);
            break;
        case 6:
            inventory.displayInventory();
            break;
        case 7: {
            cout << "Enter customer name: "<<endl;
            string customerName;
            cin>>customerName;

            Customer customer(customerName);
            customer.buyItem(cashier, inventory);
            break;
        }
        case 8:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}
