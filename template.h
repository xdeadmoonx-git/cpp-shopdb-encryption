#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <shopdb.h>
#include <type_traits>

template<typename T>
bool parse(const string& s, T& out) {
    static_assert(!is_same<T, string>::value, "");
    istringstream iss(s);
    if (!(iss >> out)) return false;
    char c;
    return !(iss >> c);
}

template<>
inline bool parse<string>(const string& s, string& out) {
    if (s.empty())
        return false;
    out = s;
    return true;
}

template<typename T>
T read_typename(const string& prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            cin.clear();
            continue;
        }
        T val;
        if (parse<T>(line, val)) {
            return val;
        }
        cout << "Неверный формат. Попробуйте ещё раз.\n";
    }
}

#endif // TEMPLATE_H
