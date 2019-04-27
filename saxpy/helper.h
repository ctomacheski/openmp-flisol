#ifndef HELPER_H
#define HELPER_H

#include<iostream>
#include<vector>

void initialize(std::vector<int> &y,
    std::vector<int> &x,
    int &a);

void validate(std::vector<int> reference,
    std::vector<int> test,
    size_t n);

#endif