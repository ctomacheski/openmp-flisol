#include <iostream>
#include <omp.h>
#include <chrono>
#include "random.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[])
{
    int n = 9000000;
    vector<int> array(n);
    initialize(array);

    steady_clock::time_point begin_serial = steady_clock::now();
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    steady_clock::time_point end_serial = steady_clock::now();

    cout << "Serial:" << sum << endl;
    cout << "Serial elapsed time: "
         << duration_cast<microseconds>(end_serial - begin_serial).count()
         << "us" << endl;

    steady_clock::time_point begin_pragma = steady_clock::now();
    sum = 0;
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    steady_clock::time_point end_pragma = steady_clock::now();

    cout << endl;
    cout << "Only pragma:" << sum << endl;
    cout << "Only pragma elapsed time: "
         << duration_cast<microseconds>(end_pragma - begin_pragma).count()
         << "us" << endl;


    steady_clock::time_point begin_lock = steady_clock::now();
    sum = 0;
    omp_lock_t writelock;
    omp_init_lock(&writelock);

    sum = 0;
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        omp_set_lock(&writelock);
        sum += array[i];
        omp_unset_lock(&writelock);
    }

    omp_destroy_lock(&writelock);
    steady_clock::time_point end_lock = steady_clock::now();

    cout << endl;
    cout << "Using locks:" << sum << endl;
    cout << "Using locks elapsed time: "
         << duration_cast<microseconds>(end_lock - begin_lock).count()
         << "us" << endl;

    steady_clock::time_point begin_critical = steady_clock::now();
    sum = 0;
    #pragma omp parallel for
    for(int i = 0; i < n; i++)
    {
        #pragma omp critical
        sum += array[i];
    }
    steady_clock::time_point end_critical = steady_clock::now();

    cout << endl;
    cout << "Using critical:" << sum << endl;
    cout << "Using critical elapsed time: "
         << duration_cast<microseconds>(end_critical - begin_critical).count()
         << "us" << endl;

    steady_clock::time_point begin_reduction = steady_clock::now();
    sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    steady_clock::time_point end_reduction = steady_clock::now();

    cout << endl;
    cout << "Using reduction:" << sum << endl;
    cout << "Using reduction elapsed time: "
         << duration_cast<microseconds>(end_reduction - begin_reduction).count()
         << "us" << endl;
}