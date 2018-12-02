#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "common.h"

namespace lcv
{
    void read_write_display()
    {
        auto image = imgFromQrc(QStringLiteral(":/res/sample.jpg"), cv::IMREAD_COLOR);
        if(image.empty()) // Check for invalid input
        {
            std::cout <<  "Could not open or find the image" << std::endl ;
            return;
        }

        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

        cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("gray image", cv::WINDOW_NORMAL);

        cv::imshow("image", image);
        cv::imshow("gray image", grayImage);

        cv::imwrite("result.jpg", image);
        cv::imwrite("result_gray.jpg", grayImage);
    }
}
