#include <shopdb.cpp>
#include <EN_DEcryption.h>

int main(int argc, char* argv[]) {
    system("chcp 65001<nul");
    system("cls");
    if (argc != 2) {
        cout << "Неверно заданы параметры!\n";
        return 1;
    }
    string file = argv[1];

    if (file_check(file + ".enc") && file_check("key.txt.enc")) {
        cout << "Зашифрованный файл обнаружен и будет расшифрован.\n";
        decrypt(file);
    } else cout << "Зашифрованный файл или ключ не был найден!\n";

    if (file_check(file)) {
        cout << "\nФайл был обнаружен и загружен.\n\n";
    } else cout << "\nНе найден файл! Создана пустая база данных.\n\n";

    ShopDB db(file);

    while (true) {
        cout << "МЕНЮ:\n";
        cout << "1. Добавление записи\n";
        cout << "2. Удаление по номенклатурному номеру\n";
        cout << "3. Изменение по номенклатурному номеру\n";
        cout << "4. Просмотр всей базы\n";
        cout << "5. Список продукции определённого вида\n";
        cout << "6. Список книг определённого автора\n";
        cout << "7. Стоимость продукции определённого вида\n";
        cout << "0. Выход и шифрование файла\n";
        int choice = read_typename<int>("Выберите действие: ");
        switch (choice) {
            case 0: {
                char confirm;
                do {
                    confirm = read_typename<char>("Вы действительно хотите выйти? [y/n]: ");
                } while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');
                if (confirm == 'y' ||  confirm == 'Y') {
                    cout << "Выход...\n";
                    encrypt(argv[1]);
                    return 0;
                } else break;
            }
            case 1:
                system("cls");
                cout << endl;
                db.product_add();
                break;
            case 2: {
                system("cls");
                cout << endl;
                string id = read_typename<string>("Введите номенклатурный номер для удаления: ");
                db.product_delete(id);
                break;
            }
            case 3: {
                system("cls");
                cout << endl;
                string id = read_typename<string>("Введите номенклатурный номер для изменения записи: ");
                db.product_edit(id);
                break;
            }
            case 4:
                system("cls");
                cout << endl;
                db.data_display();
                break;
            case 5: {
                system("cls");
                cout << endl;
                string type = read_typename<string>("Введите вид продукции: ");
                cout << endl;
                db.type_list(type);
                break;
            }
            case 6: {
                system("cls");
                cout << endl;
                string author_last = read_typename<string>("Введите фамилию автора: ");
                cout << endl;
                db.BooksByAuthor_list(author_last);
                break;
            }
            case 7: {
                system("cls");
                cout << endl;
                string type = read_typename<string>("Введите вид продукции: ");
                cout << endl;
                db.TypeCost_list(type);
                break;
            }
            default:
                system("cls");
                cout << "Неверный выбор, попробуйте ещё раз.\n";
                cout << endl;
        }

        cout << "\nНажмите любую клавишу, чтобы продолжить...";
        system("pause>nul");
        system("cls");
    }
    return 0;
}
