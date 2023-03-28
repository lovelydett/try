#include <iostream>
#include <ucontext.h>
#include <chrono>
#include <thread>

using namespace std;

static ucontext_t ctx;

// loop happens in function
void func(int n) {
    getcontext(&ctx);
    if (n > 10) {
        return;
    }
    cout << n++ << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    setcontext(&ctx);
}

int main() {
    cout << "begin\n";

    func(1);

    cout << "end\n";

}