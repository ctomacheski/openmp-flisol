#ifndef SERIAL_H
#define SERIAL_H

#include<iostream>
#include<vector>

using namespace std;

void saxpy_serial(vector<int> &y,
    vector<int> x,
    int a,
    size_t n);

#endif