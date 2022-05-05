#include <iostream>
#include <string>
#include <vector>

//https://contest.yandex.ru/contest/35212/run-report/66732771/

const std::string Deleted = "DELETED__DELETED!!!";

unsigned long long Sum(const std::string &s, int table_size) {
    unsigned long long sum = 0;
    for (int i = 0; i < s.length(); ++i) {
        sum += sum * 29 + s[i];
    }
    return sum % table_size;
}

int Hash(const std::string &s, int i, int table_size, unsigned long long k = 0) {
    return (k + i * i / 2 + i / 2) % table_size;
}

class HashTable {
private:
    std::vector<std::string> table;
    int Size;
    void ReTable() {
        HashTable table2(table.size() * 2);
        for (std::string &elem: table) {
            if (elem != "0" && elem != Deleted) {
                table2.Add(elem);
            }
        }
        *this = std::move(table2);
    }

public:
    explicit HashTable(int table_size) : table(table_size, "0"), Size(0) {}

    std::pair<bool, int> Has(const std::string &s) const {
        int iteration = 1;
        unsigned long long summa = Sum(s, table.size());
        int hash = Hash(s, iteration, table.size(), summa);
        int hash0 = hash;
        int hash_string = hash0;
        while (iteration <= table.size()) {
            if (table[hash] == s) {
                return {true, hash};
            }
            if (table[hash] == "0") {
                return {false, hash_string == hash0 ? hash : hash_string};
            }
            if (hash0 == hash_string && table[hash] == Deleted) {
                hash_string = hash;
            }
            iteration += 1;
            hash = Hash(s, iteration, table.size(), hash0);
            
        }
        return {false, hash_string};
    }

    bool Add(const std::string &s) {
        if (table.size() * 3 < Size * 4) {
            ReTable();
        }
        std::pair<bool, int> has_pair = Has(s);
        if (has_pair.first) {
            return false;
        }
        Size += 1;
        table[has_pair.second] = s;
        return true;
    }

    bool Remove(const std::string &s) {
        std::pair<bool, int> has_pair = Has(s);
        if (!has_pair.first) {
            return false;
        }
        table[has_pair.second] = Deleted;
        return true;
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
            std::cout << (table.Has(value).first ? "OK" : "FAIL") << std::endl;
        } else if (command == '-') {
            std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
        }
    }
    return 0;
}
