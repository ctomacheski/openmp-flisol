#ifndef HELPER_H
#define HELPER_H

#include<iostream>
#include<vector>

using namespace std;

void initialize(vector<int> &y,
    vector<int> &x,
    int &a);

void validate(vector<int> reference,
    vector<int> test,
    size_t n);

#endif