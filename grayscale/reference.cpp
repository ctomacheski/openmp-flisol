#include <iostream>
#include "rgb.h"

using namespace std;

void process_image_serial(struct rgb *input_image,
    unsigned char *output_image,
    size_t rows,
    size_t cols)
{
    for(size_t r = 0; r < rows; r++)
    {
        for(size_t c = 0; c < cols; c++)
        {
            size_t index = r * cols + c;
            struct rgb pixel = input_image[index];

            float channel = .299f * pixel.red 
                + .587f * pixel.green
                + .114f * pixel.blue;

            output_image[index] = channel;
        }
    }
}