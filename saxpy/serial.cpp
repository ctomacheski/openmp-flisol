#include<iostream>
#include<vector>

void saxpy_serial(std::vector<int> &y, std::vector<int> x, int a, size_t n)
{    
    for(size_t i = 0; i < n; i++)
    {
        y[i] = a * x[i] + y[i];
    }
}