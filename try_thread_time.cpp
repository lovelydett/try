// 引入必要的头文件
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

// 定义一个函数，用于模拟线程执行一些任务
void do_some_work()
{
    // 用一个循环来模拟任务
    for (int i = 0; i < 1000000; i++)
    {
        // 做一些简单的计算
        int x = i * i;
    }
}

double A[100][100], B[100][100], C[100][100];

void matmul1() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            for (int k = 0; k < 100; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmul2() {
    for (int i = 0; i < 100; i++) {
        for (int k = 0; k < 100; k++) {
            for (int j = 0; j < 100; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// 定义一个函数，用于获取某个线程的CPU时钟ID，并返回其thread time
double get_thread_time(pthread_t tid)
{
    // 定义一个clockid_t变量，用于存储CPU时钟ID
    clockid_t cid;
    
    // 调用pthread_getcpuclockid函数，传入线程的本地句柄和clockid_t变量的地址，获取CPU时钟ID

    int ret = pthread_getcpuclockid(tid, &cid);
    
    // 检查返回值是否为0，如果不为0，则表示出错，打印错误信息并返回-1
    if (ret != 0)
    {
        std::cerr << "Error: pthread_getcpuclockid for " << tid << " failed with return value: " << ret << "\n";
        return -1;
    }
    
    // 定义一个timespec结构体变量，用于存储时间信息
    struct timespec ts;
    
    // 调用clock_gettime函数，传入CPU时钟ID和timespec结构体变量的地址，获取时间信息
    ret = clock_gettime(cid, &ts);
    
    // 检查返回值是否为0，如果不为0，则表示出错，打印错误信息并返回-1
    if (ret != 0)
    {
        std::cerr << "Error: clock_gettime failed with return value: " << ret << "\n";
        return -1;
    }
    
    // 将timespec结构体变量中的秒和纳秒转换为浮点数，并相加得到thread time（单位为秒），并返回该值
    double thread_time = ts.tv_sec + ts.tv_nsec / 1e9;
    
    return thread_time;
}

// 主函数
int main()
{
   double start = get_thread_time(pthread_self());

   auto start_time = std::chrono::high_resolution_clock::now();
   
   matmul2();

   auto end_time = std::chrono::high_resolution_clock::now();

   double end = get_thread_time(pthread_self());

   auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1000.0;
   
   // 计算线程执行过程中消耗的thread time，并存储在elapsed变量中 
   double elapsed = end - start;
   
   // 打印结果 
   std::cout << "Thread time: " << elapsed * 1000 << " mili-seconds\n";
   std::cout << "Wall clock time: " << elapsed_ms << " mili-seconds\n";

   return 0;
}