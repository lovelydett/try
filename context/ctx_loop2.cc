#include <iostream>
#include <ucontext.h>
#include <chrono>
#include <thread>
#include <functional>

using namespace std;

static ucontext_t ctx_to_exec, ctx_to_continue;

// loop through calling this function
void func(int n) {
    if (n > 10) {
        return;
    }
    cout << n << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
}

int main() {
    cout << "begin\n";

    char stack[128];
    getcontext(&ctx_to_exec);
    ctx_to_exec.uc_stack.ss_sp = stack;
    ctx_to_exec.uc_stack.ss_size = 128;
    ctx_to_exec.uc_stack.ss_flags = 0;

    ctx_to_exec.uc_link = &ctx_to_continue;

    auto f = bind(func, 1);
    makecontext(&ctx_to_exec, &func, 1, 1);

    swapcontext(&ctx_to_continue, &ctx_to_exec);

    cout << "end\n";

}