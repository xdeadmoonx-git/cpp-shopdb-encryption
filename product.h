#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Product {
protected:
    string id;
    string type;
    int price;
    int quantity;
public:
    Product(const string& id, const string& type, int price, int quantity);
    virtual ~Product() {}
    virtual void print() const;

    string getType() const;
    string getID() const;
    int getPrice() const;
    int getQuantity() const;

    void setPrice(int newPrice);
    void setQuantity(int newQty);
};


#endif // PRODUCT_H
