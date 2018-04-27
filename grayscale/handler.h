#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
using namespace std;

void post_process_image(string output_file,
    unsigned char *output_image,
    size_t rows, size_t cols);

void compare_images(string reference_file,
    string test_file);

#endif