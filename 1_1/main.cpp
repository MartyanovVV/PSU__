#include <iostream>
#include <string>
#include <vector>

//https://contest.yandex.ru/contest/35212/run-report/66134733/

unsigned long long Sum(const std::string &s, int table_size) {
    int sum = 0;
    for (int i = 0; i < s.length(); ++i) {
        sum += sum * 29 + s[i];
    }
    return sum % table_size;
    //горнер
}

int Hash(const std::string &s, int i, int table_size, unsigned long long k = 0) {
    if (s.empty()) return 0;
    if (i == 0 || i == 1) k = Sum(s, table_size);
    return (k + i * i / 2 + i / 4) % table_size;
    //квадратичное хеширование
}

class HashTable {
private:
    std::vector<std::string> table;
    int Size;

public:
    explicit HashTable(int table_size) : table(table_size, "0"), Size(0) {}

    unsigned long long Has(const std::string &s) const {
        int iteration = 0;
        unsigned long long hash = Hash(s, iteration, table.size());
        unsigned long long hashold = hash;
        unsigned long long hash_string = 0;
        while (iteration <= Size) {
            if (table[hash] == s) {
                return hash * 2;
            } else if (table[hash] == "0") {
                return hash_string ? hash_string * 2 + 1 : hash * 2 + 1;
                //hash_string-индекс где возможно стоит наш объект
            } else if (!hash_string && table[hash] == "DELETED__DELETED!!!") {
                hash_string = hash;
                ++iteration;
                hash = Hash(s, iteration, table.size(), hashold);
            } else {
                ++iteration;
                hash = Hash(s, iteration, table.size(), hashold);
            }
        }
        return hash_string ? hash_string * 2 + 1 : hash * 2 + 1;
        //+1 чтобы не спутать индекс 0 и значение 0;
    }
    //хотел узнать если вообще смысл так делать? Типо вроде мне даже и искать
    //место для вставки потом не нужно, но код становится страшным и ,наверное,
    //нечитаемым

    bool Add(const std::string &s) {
        if (table.size() * 3 < Size * 4) {
            ReTable();
        }
        unsigned long long hash = Has(s);
        if (!(hash % 2)) {
            return false;
        }
        ++Size;
        table[hash / 2] = s;
        return true;
    }

    bool Remove(const std::string &s) {
        unsigned long long hash = Has(s);
        if (hash % 2) {
            return false;
        }
        table[hash / 2] = "DELETED__DELETED!!!";
        return true;
    }

    void ReTable() {
        HashTable table2(table.size() * 2);
        for (std::string &elem: table) {
            if (elem != "0" && elem != "DELETED__DELETED!!!") {
                table2.Add(elem);
            }
        }
        *this = std::move(table2);
    }
};

int main() {
    HashTable table(8);
    char command = '-';
    std::string value = "s";
    while (std::cin >> command >> value) {
        if (command == '+') {
            std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
        } else if (command == '?') {
            std::cout << (!(table.Has(value) % 2) ? "OK" : "FAIL") << std::endl;
        } else if (command == '-') {
            std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
        }
    }
    return 0;
}
