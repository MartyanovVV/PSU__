#include <iostream>
#include <vector>
#include <algorithm>

//https://contest.yandex.ru/contest/35212/run-report/65805892/

int Bakterii(int &n) {
    std::vector<int> v(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        v[i] = v[i - 1] + 1;
        if (!(i % 4)) v[i] = std::min(v[i], v[i / 4] + 1);
        if (!(i % 5)) v[i] = std::min(v[i], v[i / 5] + 1);

    }
    //i = кол-ву бактерий, v[i]= наим кол-во дней для достижения i бактерий
    return v[n];
}

int main() {
    int n = 0;
    std::cin >> n;
    std::cout << Bakterii(n);
    return 0;
}
