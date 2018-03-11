#ifndef DRAW_SHAPE_H
#define DRAW_SHAPE_H

namespace DrawShape
{
    void test(const std::string& path)
    {
        cv::Mat image = cv::imread(path);

        cv::Mat imageLine = image.clone();
        cv::line(imageLine, cv::Point{ 322, 179 }, cv::Point{ 400, 183 }, cv::Scalar{ 0, 255, 0 }, 1, CV_AA);
        cv::imshow("line", imageLine);
        cv::imwrite("imageLine.jpg", imageLine);

        cv::Mat imageCircle = image.clone();
        cv::circle(imageCircle, cv::Point{ 350, 200 }, 150, cv::Scalar{ 0, 255, 0 }, 1, CV_AA);
        cv::imshow("circle", imageCircle);
        cv::imwrite("imageCircle.jpg", imageCircle);

        cv::Mat imageEllipse = image.clone();
        cv::ellipse(imageEllipse, cv::Point{ 360,200 }, cv::Size{ 100, 170 }, 45, 0, 360, cv::Scalar{ 255, 0, 0 }, 1, 8);
        cv::ellipse(imageEllipse, cv::Point{ 360,200 }, cv::Size{ 100, 170 }, 135, 0, 360, cv::Scalar{ 0, 0, 255 }, 1, 8);
        cv::imshow("ellipse", imageEllipse);
        cv::imwrite("imageEllipse.jpg", imageEllipse);

        cv::Mat imageRectangle = image.clone();
        cv::rectangle(imageRectangle, cv::Point{ 208, 55 }, cv::Point{ 450, 355 }, cv::Scalar{ 0, 255, 0 }, 1, 8);
        cv::imshow("rectangle", imageRectangle);
        cv::imwrite("imageRectangle.jpg", imageRectangle);

        cv::Mat imageText = image.clone();
        cv::putText(imageText, "Mark Zuckerberg", cv::Point{ 205,50 }, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar{ 0, 255, 0 }, 1);
        cv::imshow("text", imageText);
        cv::imwrite("imageText.jpg", imageText);

        cv::waitKey(0);
    }
}

#endif //DRAW_SHAPE
