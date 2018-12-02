#include "common.h"

namespace lcv
{
    void crop_and_resize()
    {
        cv::Mat source = imgFromQrc(QStringLiteral(":/res/sample.jpg"), cv::IMREAD_COLOR);
        cv::Mat scaleDown;
        cv::Mat scaleUp;

        double const scaleX = 0.6;
        double const scaleY = 0.6;

        cv::resize(source, scaleDown, {}, scaleX, scaleY, cv::INTER_LINEAR);
        cv::resize(source, scaleUp, {}, scaleX * 3, scaleY * 3, cv::INTER_LINEAR);

        cv::Mat const crop = source(cv::Range{ 50, 150 }, cv::Range{ 20, 200 });
        cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Scaled Down", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Scaled Up", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Cropped Image", cv::WINDOW_AUTOSIZE);

        cv::imshow("Original", source);
        cv::imshow("Scaled Down", scaleDown);
        cv::imshow("Scaled Up", scaleUp);
        cv::imshow("Cropped Image", crop);
    }
}

