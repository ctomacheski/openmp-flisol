#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include "rgb.h"

using namespace std;
using namespace cv;

void post_process_image(string output_file,
    unsigned char *output_image,
    size_t rows, size_t cols)
{
    Mat gray_output(rows, cols, CV_8UC1, (void *)output_image);
    imwrite(output_file.c_str(), gray_output);
}

void compare_images(string reference_file,
    string test_file)
{
    Mat reference_image = imread(reference_file, -1);
    Mat test_image = imread(test_file, -1);

    Mat difference = abs(reference_image - test_image);
    Mat difference_channel = difference.reshape(1, 0);

    double min_val, max_val;
    minMaxLoc(difference_channel, &min_val, &max_val, NULL, NULL);

    difference_channel = (difference_channel - min_val) * (255. / (max_val - min_val));
    difference = difference_channel.reshape(reference_image.channels(), 0);

    imwrite("difference.jpg", difference);

    unsigned char *reference = reference_image.ptr<unsigned char>(0);
    unsigned char *test = test_image.ptr<unsigned char>(0);

    size_t image_dimension = reference_image.rows * reference_image.cols
        * reference_image.channels();

    for(size_t i = 0; i < image_dimension; i++)
    {
        if(reference[i] != test[i])
        {
            cerr << "Differencce at pos " << i << endl;
            cerr << "Reference: " << setprecision(17) << +reference[i] <<
                  "\nOMP      : " << +test[i] << endl;

            exit(EXIT_FAILURE);
        }
    }

    cout << "Image is correct" << endl;
}