#include <iostream>
#include <vector>
#include <algorithm>

//https://contest.yandex.ru/contest/35212/run-report/65801067/

/*
Утверждение жадное решение является оптимальным
Док-во: От противного.
Пусть в жадном решении k людей и существует болеее оптимальное решение,
состоящее из более чем k людей, упорядочим людей по их силе в обоих отрезках,
они автоматом также будут упорядочены и по массе(условие задачи).
Найдем первого человека отличающегося в жадном решении от оптиммального.
У такого человека оптимального решения меньше сила чем в жадном,тогда заметим,
что по построению жадного решения человек должен быть с меньшей силой, тогда
это противоречит построению дажного решению=> неверное=> жадное является
оптимаьным решением.
*/


struct Atletics {
    unsigned int strenght = 0;
    unsigned int weight = 0;

    explicit Atletics(int weight, int strenght) : weight(weight), strenght(strenght) {}
};

void Sort(std::vector<Atletics> &v) {
    std::sort(v.begin(), v.end(), [&v](Atletics a1, Atletics a2) {
        return a1.strenght < a2.strenght;
    });
}

unsigned int Height(std::vector<Atletics> &v) {
    Sort(v);
    int height = 0;
    int summ = 0;
    for (auto &elem: v) {
        if (elem.strenght >= summ) {
            ++height;
            summ += elem.weight;
        }
    }
    return height;
}

int main() {
    unsigned int strenght = 0;
    unsigned int weight = 0;
    std::vector<Atletics> v;
    while (std::cin >> weight >> strenght) {
        v.push_back(Atletics(weight, strenght));
        if (!std::cin) break;
    }
    std::cout << Height(v);
    return 0;
}
