#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<vector>

void saxpy_parallel(std::vector<int> &y,
    std::vector<int> x,
    int a,
    size_t n);

#endif