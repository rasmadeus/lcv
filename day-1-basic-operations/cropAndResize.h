#ifndef CROP_AND_RESIZE_H
#define CROP_AND_RESIZE_H

namespace CropAndResize
{
    void test(const std::string& path)
    {
        cv::Mat scaleDown;
        cv::Mat scaleUp;

        cv::Mat source = cv::imread(path, 1);

        const double scaleX = 0.6;
        const double scaleY = 0.6;

        cv::resize(source, scaleDown, cv::Size(), scaleX, scaleY, cv::INTER_LINEAR);
        cv::resize(source, scaleUp, cv::Size(), scaleX * 3, scaleY * 3, cv::INTER_LINEAR);

        cv::Mat crop = source(cv::Range{ 50, 150 }, cv::Range{ 20, 200 });

        cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Scaled Down", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Scaled Up", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Cropped Image", cv::WINDOW_AUTOSIZE);

        cv::imshow("Original", source);
        cv::imshow("Scaled Down", scaleDown);
        cv::imshow("Scaled Up", scaleUp);
        cv::imshow("Cropped Image", crop);

        cv::waitKey(0);
    }
}

#endif //CROP_AND_RESIZE_H
