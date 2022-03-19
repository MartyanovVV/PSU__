#include <iostream>
#include <vector>

//https://contest.yandex.ru/contest/35212/run-report/65808358/

unsigned long long CountPyramid(int n) {
    std::vector<std::vector<unsigned long long>> v(n + 1, std::vector<unsigned long long>(n + 1, 0));
    for (int i = 0; i <= n; ++i) {
        v[0][i] = 1;
        v[i][0] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i >= j) v[i][j] += v[i - j][j];
            v[i][j] += v[i][j - 1];
        }
    }

    //i = кол-во кубиков в пирамиде
    //j <= кол-во кубиков в нижнем слое
    return v[n][n];
}

int main() {
    int n = 0;
    std::cin >> n;
    std::cout << CountPyramid(n);
    return 0;
}
