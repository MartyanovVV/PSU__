#include <iostream>
#include <vector>
#include <algorithm>

//https://contest.yandex.ru/contest/35212/run-report/65888679/

struct TreeNode {
    int Parent = 0;
    int Maxway = 0;
    int Height_ = 0;
    int Height__ = 0;
    std::vector<int> Children;
};

void Height(std::vector<TreeNode> &v, int index) {
    for (auto elem: v[index].Children) {
        if (v[elem].Height_ + 1 >= v[index].Height_) {
            v[index].Height__ = std::max(v[index].Height_, v[index].Height__);
            v[index].Height_ = v[elem].Height_ + 1;
        } else if (v[elem].Height_ + 1 >= v[index].Height__) {
            v[index].Height__ = v[elem].Height_ + 1;
        }
    }
}

void Lowness(std::vector<TreeNode> &v, int index, int k) {
    if (index == 0) v[index].Maxway = 0;
    else {
        if (v[v[index].Parent].Height_ == v[index].Height_ + 1) {
            v[index].Maxway = std::max(v[v[index].Parent].Height__ + 1, v[v[index].Parent].Maxway + 1);
        } else {
            v[index].Maxway = std::max(v[v[index].Parent].Height_ + 1, v[v[index].Parent].Maxway + 1);
        }
    }
    for (auto elem: v[index].Children) {
        Lowness(v, elem, k + 1);
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<TreeNode> v(n);
    for (int i = 1; i < n; ++i) {
        int parent = 0;
        int children = 0;
        std::cin >> parent >> children;
        v[parent].Children.push_back(children);
        v[children].Parent = parent;
    }
    for (int i = n - 1; i >= 0; --i) {
        Height(v, i);
    }
    Lowness(v, 0, 0);
    for (auto elem: v) {
        std::cout << std::max(std::max(elem.Maxway, elem.Height_), elem.Height__) << std::endl;
    }
    return 0;
}
