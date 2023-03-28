#include <iostream>
#include <ucontext.h>

using namespace std;

void func1() {
    cout << "func1 called\n";
}

int main() {
    cout << "begin\n";

    char stack[128];
    ucontext_t ctx_to_exec, ctx_to_continue;

    // get current (undergoing) context, cuz we need to swap it!
    getcontext(&ctx_to_exec);

    // set up stack
    ctx_to_exec.uc_stack.ss_sp = stack;
    ctx_to_exec.uc_stack.ss_size = 128;
    ctx_to_exec.uc_stack.ss_flags = 0;

    // set up the successor context 
    ctx_to_exec.uc_link = &ctx_to_continue;

    // set up the function for current context to jump to
    makecontext(&ctx_to_exec, func1, 0);

    // this line do 2 things: 
    // 1. save current context of ctx_to_exec to ctx_to_continue
    // 2. toggle ctx_to_exec and we begin execute func1()
    swapcontext(&ctx_to_continue, &ctx_to_exec);

    cout << "end\n";
}

