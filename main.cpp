#include <iostream>
#include <cstdlib>
#include <chrono>
#include <opencv2/opencv.hpp>

#include "rgb.h"
#include "reference.h"
#include "handler.h"
#include "student.h"

using namespace std;
using namespace chrono;
using namespace cv;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Usage: ./runner input_file" << endl;
        exit(EXIT_FAILURE);
    }

    string input_file = string(argv[1]);
    string reference_file = "reference.jpg";
    string output_file = "output.jpg";

    Mat image;
    image = imread(input_file.c_str(), CV_LOAD_IMAGE_COLOR);

    Mat color_image;
    cvtColor(image, color_image, CV_BGR2RGB);

    Mat reference_gray_image;
    reference_gray_image.create(image.rows, image.cols, CV_8UC1);

    Mat output_gray_image;
    output_gray_image.create(image.rows, image.cols, CV_8UC1);

    struct rgb *input_image = (struct rgb *)color_image.ptr<unsigned char>(0);
    unsigned char *reference_image = reference_gray_image.ptr<unsigned char>(0);
    unsigned char *output_image = output_gray_image.ptr<unsigned char>(0);

    steady_clock::time_point begin_serial = steady_clock::now();
    process_image_serial(input_image, reference_image, color_image.rows, color_image.cols);
    steady_clock::time_point end_serial = steady_clock::now();

    cout << "Serial elapsed time: "
         << duration_cast<microseconds>(end_serial - begin_serial).count()
         << "ms" << endl;

    steady_clock::time_point begin_parallel = steady_clock::now();
    process_image_parallel(input_image, output_image, color_image.rows, color_image.cols);
    steady_clock::time_point end_parallel = steady_clock::now();

    cout << "Parallel elapsed time: "
         << duration_cast<microseconds>(end_parallel - begin_parallel).count()
         << "ms" << endl;

    post_process_image(reference_file, reference_image, color_image.rows, color_image.cols);
    post_process_image(output_file, output_image, color_image.rows, color_image.cols);

    compare_images(reference_file, output_file);
}