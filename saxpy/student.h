#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<vector>

using namespace std;

void saxpy_parallel(vector<int> &y,
    vector<int> x,
    int a,
    size_t n);

#endif