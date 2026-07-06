#ifndef BOOK_H
#define BOOK_H

#include <product.h>

class Book : public Product {
protected:
    string author_last;
    string author_init;
    string title;
    int year;
    string binding;
public:
    Book(const string& id, int price, int quantity,
         const string& author_last, const string& author_init,
         const string& title, int year, const string& binding);
    void print() const override;

    string getAuthorLast() const;
    string getAuthorInit() const;
    string getTitle() const;
    int getYear() const;
    string getBinding() const;

    void setAuthorLast(const string& newLast);
    void setAuthorInit(const string& newInit);
    void setTitle(const string& newTitle);
    void setYear(int newYear);
    void setBinding(const string& newBinding);
};

#endif // BOOK_H
