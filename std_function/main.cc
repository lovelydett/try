#include <functional>
#include <iostream>

using namespace std;

template <typename T>
function<T> get_func(function<T> in_func) {
    function<T> out_func = in_func;
    return out_func;
}

int main() {
    function<int(int, int)> func1;
    func1 = [=](int a, int b) -> int {
        return a + b;
    };
    cout << func1(1, 2) << endl;

    function<int(int, int)> func2 = get_func<int(int, int)> ([=](int a, int b) -> int {
        return a + b;
    });

    cout << func2(1, 2) << endl;
    

    return 0;

}