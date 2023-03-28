#include <sys/stat.h>
#include <assert.h>
#include <iostream>

int main() {
    auto ret = mkdir("/home/tt/Codes/temp/cpp_mkdir/test_dir", S_IRWXU);
    if (ret != 0) {
        std::cout << "enable to mkdir, errno: " << ret << std::endl;
    }
    return 0;
}