#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "common.h"

namespace lcv
{
    void draw_shape()
    {
        auto image = imgFromQrc(QStringLiteral(":/res/mark.jpg"));
        auto imageLine = image.clone();
        cv::line(imageLine, cv::Point{ 322, 179 }, cv::Point{ 400, 183 }, cv::Scalar{ 0, 255, 0 }, 1, cv::LINE_AA);
        cv::imshow("line", imageLine);
        cv::imwrite(":/res/imageLine.jpg", imageLine);

        auto imageCircle = image.clone();
        cv::circle(imageCircle, cv::Point{ 350, 200 }, 150, cv::Scalar{ 0, 255, 0 }, 1, cv::LINE_AA);
        cv::imshow("circle", imageCircle);
        cv::imwrite(":/res/imageCircle.jpg", imageCircle);

        auto imageEllipse = image.clone();
        cv::ellipse(imageEllipse, cv::Point{ 360,200 }, cv::Size{ 100, 170 }, 45, 0, 360, cv::Scalar{ 255, 0, 0 }, 1, 8);
        cv::ellipse(imageEllipse, cv::Point{ 360,200 }, cv::Size{ 100, 170 }, 135, 0, 360, cv::Scalar{ 0, 0, 255 }, 1, 8);
        cv::imshow("ellipse", imageEllipse);
        cv::imwrite(":/res/imageEllipse.jpg", imageEllipse);

        auto imageRectangle = image.clone();
        cv::rectangle(imageRectangle, cv::Point{ 208, 55 }, cv::Point{ 450, 355 }, cv::Scalar{ 0, 255, 0 }, 1, 8);
        cv::imshow("rectangle", imageRectangle);
        cv::imwrite(":/res/imageRectangle.jpg", imageRectangle);

        auto imageText = image.clone();
        cv::putText(imageText, "Mark Zuckerberg", cv::Point{ 205, 50 }, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar{ 0, 255, 0 }, 1);
        cv::imshow("text", imageText);
        cv::imwrite(":/res/imageText.jpg", imageText);
    }
}
