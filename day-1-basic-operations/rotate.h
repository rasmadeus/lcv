#ifndef ROTATE_H
#define ROTATE_H

namespace Rotate
{
    void test(const std::string& path)
    {
        cv::Mat source = cv::imread(path, 1);
        cv::Mat result;

        const cv::Point2f center{ source.cols / 2.0f, source.rows / 2.0f };
        const double rotationAngle = 30.0;
        const double scale = 1.0;

        cv::Mat M = cv::getRotationMatrix2D(center, rotationAngle, scale);
        cv::warpAffine(source, result, M, cv::Size{ source.cols, source.rows });

        cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Rotated Image", cv::WINDOW_AUTOSIZE);

        cv::imshow("Original Image", source);
        cv::imshow("Rotated Image", result);

        cv::waitKey(0);
    }
}

#endif //ROTATE_H
