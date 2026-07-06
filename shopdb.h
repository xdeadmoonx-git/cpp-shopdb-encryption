#ifndef SHOPDB_H
#define SHOPDB_H

#include <product.h>
#include <book.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

class ShopDB {
    vector<Product*> products;
    string filename;
    void save() const;
    void load();
public:
    ShopDB(const string& fname);
    ~ShopDB();
    void product_add();
    void product_delete(const string& id);
    void product_edit(const string& id);
    void data_display() const;
    void type_list(const string& type) const;
    void BooksByAuthor_list(const string& author_last) const;
    void TypeCost_list(const string& type) const;

};

#endif
