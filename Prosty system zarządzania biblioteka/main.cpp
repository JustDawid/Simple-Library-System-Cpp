#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Klasa reprezentuj¹ca pojedyncz¹ ksi¹¿kê
class Book {
private:
    std::string title;
    std::string author;
    bool isBorrowed;

public:
    // Konstruktor
    Book(std::string t, std::string a) : title(std::move(t)), author(std::move(a)), isBorrowed(false) {}

    // Gettery
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    bool getStatus() const { return isBorrowed; }

    // Metody modyfikuj¹ce stan
    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }

    // Wyœwietlanie informacji o ksi¹¿ce
    void display() const {
        std::cout << "Tytul: " << title << " | Autor: " << author
                  << " | Status: " << (isBorrowed ? "Wypozyczona" : "Dostepna") << "\n";
    }
};

// Klasa reprezentuj¹ca bibliotekê
class Library {
private:
    std::vector<Book> books;

public:
    // Dodawanie nowej ksi¹¿ki
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "[+] Dodano ksiazke: " << book.getTitle() << "\n";
    }

    // Wyœwietlanie wszystkich ksi¹¿ek
    void displayAllBooks() const {
        std::cout << "\n--- ZASOBY BIBLIOTEKI ---\n";
        if (books.empty()) {
            std::cout << "Biblioteka jest pusta.\n";
            return;
        }
        for (const auto& book : books) {
            book.display();
        }
        std::cout << "-------------------------\n\n";
    }

    // Wypo¿yczanie ksi¹¿ki z u¿yciem std::find_if i lambdy
    void borrowBook(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(), [&title](const Book& b) {
            return b.getTitle() == title;
        });

        if (it != books.end()) {
            if (!it->getStatus()) {
                it->borrowBook();
                std::cout << "[V] Sukces: Wypozyczono ksiazke '" << title << "'.\n";
            } else {
                std::cout << "[X] Blad: Ksiazka '" << title << "' jest juz wypozyczona.\n";
            }
        } else {
            std::cout << "[?] Blad: Nie znaleziono ksiazki '" << title << "' w systemie.\n";
        }
    }

    // Zwracanie ksi¹¿ki
    void returnBook(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(), [&title](const Book& b) {
            return b.getTitle() == title;
        });

        if (it != books.end()) {
            if (it->getStatus()) {
                it->returnBook();
                std::cout << "[V] Sukces: Zwrocono ksiazke '" << title << "'.\n";
            } else {
                std::cout << "[X] Blad: Ksiazka '" << title << "' nie byla wypozyczona.\n";
            }
        } else {
            std::cout << "[?] Blad: Nie znaleziono ksiazki '" << title << "' w systemie.\n";
        }
    }
};

int main() {
    Library myLibrary;

    std::cout << "Rozpoczecie pracy systemu bibliotecznego...\n\n";

    // Inicjalizacja danych
    myLibrary.addBook(Book("Wladca Pierscieni", "J.R.R. Tolkien"));
    myLibrary.addBook(Book("Dziuna", "Frank Herbert"));
    myLibrary.addBook(Book("Wiedzmin", "Andrzej Sapkowski"));

    // Wyswietlenie zasobow
    myLibrary.displayAllBooks();

    // Testowanie logiki biznesowej
    myLibrary.borrowBook("Dziuna");
    myLibrary.borrowBook("Dziuna"); // Próba wypo¿yczenia ju¿ wypo¿yczonej
    myLibrary.borrowBook("Harry Potter"); // Próba wypo¿yczenia nieistniej¹cej

    myLibrary.displayAllBooks();

    myLibrary.returnBook("Dziuna");

    myLibrary.displayAllBooks();

    return 0;
}
