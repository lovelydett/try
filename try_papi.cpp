// Include PAPI header file
#include <papi.h>
#include <cstdio>
#include <cstdlib>

// Define a function to be profiled
void foo()
{
    printf("Foo\n");
    // Do some computation
    int x = 0;
    for (int i = 0; i < 1000000; i++)
    {
        x += i;
    }
}

int main()
{
    // Define and initialize two event codes
    int events[2] = {PAPI_TOT_INS, PAPI_L2_TCM};
    printf("A\n");
    
    // Define and initialize two event values
    long long values[2];

    // Initialize PAPI library
    if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
        exit(1);
    printf("B\n");

    // Start measuring events
    auto ret = PAPI_start_counters(events, 2);
    if (ret != PAPI_OK) {
        printf("PAPI_start_counters failed with error code %d\n", ret);
        exit(1);
    }
    printf("C\n");

    // Call the function to be profiled
    foo();

    // Stop measuring events and read event values
    if (PAPI_stop_counters(values, 2) != PAPI_OK)
        exit(1);
    printf("D\n");

    // Print results
    printf("Total instructions: %lld\n", values[0]);
    printf("L2 total cache misses: %lld\n", values[1]);

    return 0;
}