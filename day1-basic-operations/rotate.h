#include "common.h"

namespace lcv
{
    void rotate()
    {
        auto source = imgFromQrc(QStringLiteral(":/res/sample.jpg"), cv::IMREAD_COLOR);
        cv::Point2f center{ static_cast<float>(source.cols / 2.0), static_cast<float>(source.rows / 2.0) };

        constexpr double rotationAngle = 30;
        constexpr double scale = 1.0;

        auto rotateMatrix = cv::getRotationMatrix2D(center, rotationAngle, scale);

        cv::Mat res;
        cv::warpAffine(source, res, rotateMatrix, cv::Size{ source.cols, source.rows });

        cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Rotated Image", cv::WINDOW_AUTOSIZE);

        cv::imshow("Original Image", source);
        cv::imshow("Rotated Image", res);
    }
}
