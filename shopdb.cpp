#include "shopdb.h"
#include <template.h>

static void Header() {
    cout << left << setw(12) << "ID"
         << setw(10) << "Type"
         << right << setw(12)  << "Price(rub)"
         << setw(8)  << "Qty"
         << " | "    << left  << setw(20) << "Author"
         << ' '     << left  << setw(26) << "Title"
         << right << setw(6)  << "Year"
         << setw(9)  << "Binding"
         << "\n";
    cout << string(12 + 10 + 12 + 8 + 3 + 1 + 20 + 1 + 26 + 6 + 9, '-') << "\n";
}

Product::Product(const string& id, const string& type, int price, int quantity) : id(id), type(type), price(price), quantity(quantity) {}

void Product::print() const {
    cout << left << setw(12) << id
         << setw(10) << type
         << right << setw(12) << price
         << setw(8) << quantity;
}

string Product::getType()    const { return type; }
string Product::getID()      const { return id; }
int    Product::getPrice()   const { return price; }
int    Product::getQuantity()const { return quantity; }

void Product::setPrice(int newPrice)      { price = newPrice; }
void Product::setQuantity(int newQty)      { quantity = newQty; }

Book::Book(const string& id, int price, int quantity,
           const string& author_last, const string& author_init,
           const string& title, int year, const string& binding)
    : Product(id, "Book", price, quantity),
      author_last(author_last), author_init(author_init),
      title(title), year(year), binding(binding) {}

void Book::print() const {

    Product::print();

    string author = author_last + " " + author_init;

    cout << " | "
         << left  << setw(20) << author
         << ' '
         << left  << setw(26) << title
         << right << setw(6)  << year
         << setw(9)  << binding
         << "\n";
}

string Book::getAuthorLast() const { return author_last; }
string Book::getAuthorInit() const { return author_init; }
string Book::getTitle()      const { return title; }
int    Book::getYear()       const { return year; }
string Book::getBinding()    const { return binding; }

void Book::setAuthorLast(const string& newLast)   { author_last = newLast; }
void Book::setAuthorInit(const string& newInit)   { author_init = newInit; }
void Book::setTitle(const string& newTitle)       { title = newTitle; }
void Book::setYear(int newYear)                   { year = newYear; }
void Book::setBinding(const string& newBinding)   { binding = newBinding; }


ShopDB::ShopDB(const string& fname) : filename(fname) {
    load();
}

ShopDB::~ShopDB() {
    for (auto p : products)
        delete p;
}

void ShopDB::product_add() {
    cout << "Введите данные нового продукта:\n";
    string id;
    while (true) {
        id = read_typename<string>("Номенклатурный номер: ");
        bool id_check = false;
        for (auto p : products) {
            if (p->getID() == id) {
                id_check = true;
                break;
            }
        }

        if (id_check) {
            cout << "Продукт с ID " << id << " уже существует. Введите другой.\n\n";
        } else {
            break;
        }
    }
    string type  = read_typename<string>("Вид продукции: "); ;
    int price  = read_typename<int>("Цена (в рублях): "); ;
    int quantity  = read_typename<int>("Количество: "); ;

    Product* p = nullptr;
    if (type == "Book") {
        string author_last = read_typename<string>("Фамилия автора: ");
        string author_init = read_typename<string>("Инициалы автора (формат: A.S.): ");
        string title = read_typename<string>("Название книги: ");
        int year = read_typename<int>("Год издания: ");
        string binding = read_typename<string>("Вид переплета: ");
        p = new Book(id, price, quantity,
                     author_last, author_init,
                     title, year, binding);
    } else {
        p = new Product(id, type, price, quantity);
    }

    products.push_back(p);
    save();
    cout << "Запись добавлена.\n";
}

void ShopDB::product_delete(const string& id) {
    auto it = products.begin();
    bool found = false;
    while (it != products.end()) {
        if ((*it)->getID() == id) {
            delete *it;
            it = products.erase(it);
            found = true;
            break;
        }
        ++it;
    }
    if (found) {
        save();
        cout << "Запись с номером " << id << " удалена.\n";
    } else {
        cout << "Продукт с номером " << id << " не найден.\n";
    }
}

void ShopDB::product_edit(const string& id) {
    for (auto p : products) {
        if (p->getID() == id) {
            cout << "Текущая запись:\n";
            Header();
            if (auto b = dynamic_cast<Book*>(p)) b->print();
            else {
                p->print();
                cout<<" | "<<left<<setw(15)<<""<<' '<<left<<setw(24)<<""<<right<<setw(6)<<""<<setw(8)<<""<<"\n";
            }

            cout << "\nВыберите поле для редактирования:\n"
                 << "1) Price  2) Qty";
            if (dynamic_cast<Book*>(p)) cout << "  3) Author 4) Title 5) Year 6) Binding";
            int fld = read_typename<int>("\nВаш выбор: ");

            switch (fld) {
                case 1: {
                    int v= read_typename<int>("Новая цена: ");
                    p->setPrice(v);
                    break;
                }
                case 2: {
                    int v= read_typename<int>("Новое количество: ");
                    p->setQuantity(v);
                    break;
                }
                case 3: case 4: case 5: case 6: {
                    auto b = dynamic_cast<Book*>(p);
                    if (!b) {
                        cout << "Это не книга.\n";
                        return;
                    }
                    if (fld == 3) {
                        string v = read_typename<string>("Новая фамилия автора: ");
                        b->setAuthorLast(v);
                        string v2 = read_typename<string>("Новые инициалы автора(формат: A.S.): ");
                        b->setAuthorInit(v2);
                    } else if (fld == 4) {
                        string v = read_typename<string>("Новое название: ");
                        b->setTitle(v);
                    } else if (fld == 5) {
                        int v = read_typename<int>("Новый год издания: ");
                        b->setYear(v);
                    } else {
                        string v = read_typename<string>("Новый вид переплёта: ");
                        b->setBinding(v);
                    }
                    break;
                }
                default:
                    cout << "Неверный выбор поля.\n";
                    return;
            }

            save();
            cout << "Запись обновлена.\n";
            return;
        }
    }
    cout << "Запись с ID = " << id << " не найдена.\n";
}


void ShopDB::data_display() const {
    if (products.empty()) {
        cout << "База данных пуста.\n";
        return;
    }

    Header();

    for (auto p : products) {
        if (auto b = dynamic_cast<Book*>(p)) {
            b->print();
        } else {
            p->print();
            cout << " | "
                 << left << setw(15) << "" << ' '
                 << left << setw(24) << ""
                 << right << setw(6)  << ""
                 << setw(8)  << ""
                 << "\n";
        }
    }
}

void ShopDB::type_list(const string& type) const {
    bool found = false;
    for (auto p : products) {
        if (p->getType() == type) {
            found = true;
        }
    }
    if (!found) {
        cout << "Продукция вида " << type << " не найдена.\n";
        return;
    }

    Header();
    for (auto p : products) {
        if (p->getType() == type) {
            if (auto b = dynamic_cast<Book*>(p)) {
                b->print();
            } else {
                p->print();
                cout << " | "
                     << left << setw(15) << "" << ' '
                     << left << setw(24) << ""
                     << right << setw(6)  << ""
                     << setw(8)  << ""
                     << "\n";
            }
        }
    }
}

void ShopDB::BooksByAuthor_list(const string& author_last) const {
    bool found = false;
    for (auto p : products) {
        if (auto b = dynamic_cast<Book*>(p)) {
            if (b->getAuthorLast() == author_last) {
                found = true;
            }
        }
    }
    if (!found) {
        cout << "Книг автора " << author_last << " не найдено.\n";
        return;
    }

    Header();
    for (auto p : products) {
        if (auto b = dynamic_cast<Book*>(p)) {
            if (b->getAuthorLast() == author_last) {
                b->print();
                found = true;
            }
        }
    }
}

void ShopDB::TypeCost_list(const string& type) const {
    bool found = false;
    for (auto p : products) {
        if (p->getType() == type) {
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Продукции вида \"" << type << "\" не найдено.\n";
        return;
    }

    int total = 0;
    for (auto p : products) {
        if (p->getType() == type)
            total += p->getPrice() * p->getQuantity();
    }
    cout << "Общая стоимость продукции вида " << type << ": " << total << "\n";
}

void ShopDB::save() const {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Ошибка открытия файла для записи: " << filename << "\n";
        return;
    }
    int count = products.size();
    file.write((char*)&count, sizeof(count));
    for (auto p : products) {
        string type = p->getType();
        int len = type.size();
        file.write((char*)&len, sizeof(len));
        file.write(type.c_str(), len);
        string id = p->getID();
        len = id.size();
        file.write((char*)&len, sizeof(len));
        file.write(id.c_str(), len);
        int price = p->getPrice();
        int quantity = p->getQuantity();
        file.write((char*)&price, sizeof(price));
        file.write((char*)&quantity, sizeof(quantity));
        if (type == "Book") {
            Book* book = dynamic_cast<Book*>(p);
            if (book) {
                string author_last = book->getAuthorLast();
                int len2 = author_last.size();
                file.write((char*)&len2, sizeof(len2));
                file.write(author_last.c_str(), len2);
                string author_init = book->getAuthorInit();
                int len3 = author_init.size();
                file.write((char*)&len3, sizeof(len3));
                file.write(author_init.c_str(), len3);
                string title = book->getTitle();
                int len4 = title.size();
                file.write((char*)&len4, sizeof(len4));
                file.write(title.c_str(), len4);
                int year = book->getYear();
                file.write((char*)&year, sizeof(year));
                string binding = book->getBinding();
                int len5 = binding.size();
                file.write((char*)&len5, sizeof(len5));
                file.write(binding.c_str(), len5);
            }
        }
    }
    file.close();
}

void ShopDB::load() {
    ifstream file(filename, ios::binary);
    if (!file) {
        return;
    }
    int count;
    file.read((char*)&count, sizeof(count));
    for (int i = 0; i < count; ++i) {
        int len;
        file.read((char*)&len, sizeof(len));
        string type;
        type.resize(len);
        file.read(&type[0], len);
        file.read((char*)&len, sizeof(len));
        string id;
        id.resize(len);
        file.read(&id[0], len);
        int price, quantity;
        file.read((char*)&price, sizeof(price));
        file.read((char*)&quantity, sizeof(quantity));
        if (type == "Book") {
            file.read((char*)&len, sizeof(len));
            string author_last;
            author_last.resize(len);
            file.read(&author_last[0], len);
            file.read((char*)&len, sizeof(len));
            string author_init;
            author_init.resize(len);
            file.read(&author_init[0], len);
            file.read((char*)&len, sizeof(len));
            string title;
            title.resize(len);
            file.read(&title[0], len);
            int year;
            file.read((char*)&year, sizeof(year));
            file.read((char*)&len, sizeof(len));
            string binding;
            binding.resize(len);
            file.read(&binding[0], len);
            Book* book = new Book(id, price, quantity, author_last, author_init, title, year, binding);
            products.push_back(book);
        } else {
            Product* p = new Product(id, type, price, quantity);
            products.push_back(p);
        }
    }
    file.close();
}
