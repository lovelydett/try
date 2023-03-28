#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <functional>
#include <optional>

using namespace std;

optional<int> func() {
    return 1;
}

int main () {
    auto a = func();
    if (a) {
        cout << *a << endl;
    }
}
