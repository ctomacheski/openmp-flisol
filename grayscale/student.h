#ifndef STUDENT_H
#define STUDENT_H

void process_image_parallel(struct rgb *input_image,
    unsigned char *output_image,
    size_t rows,
    size_t cols);

#endif