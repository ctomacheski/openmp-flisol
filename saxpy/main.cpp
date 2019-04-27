#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

#define SIZE 5000000

#include "helper.h"
#include "serial.h"
#include "student.h"

int main()
{
    std::vector<int> x(SIZE);
    std::vector<int> y(SIZE);
    int a;

    initialize(y, x, a);

    std::vector<int> y_omp(y);

    std::chrono::time_point begin_serial = std::chrono::steady_clock::now();
    saxpy_serial(y, x, a, SIZE);
    std::chrono::steady_clock::time_point end_serial = std::chrono::steady_clock::now();

    std::cout << "Serial elapsed time: "
         << std::chrono::duration_cast<std::chrono::microseconds>(end_serial - begin_serial).count()
         << "us" << std::endl;

    std::chrono::steady_clock::time_point begin_parallel = std::chrono::steady_clock::now();
    saxpy_parallel(y_omp, x, a, SIZE);
    std::chrono::steady_clock::time_point end_parallel = std::chrono::steady_clock::now();

    std::cout << "Parallel elapsed time: "
         << std::chrono::duration_cast<std::chrono::microseconds>(end_parallel - begin_parallel).count()
         << "us" << std::endl;

    validate(y, y_omp, SIZE);

    exit(EXIT_SUCCESS);
}