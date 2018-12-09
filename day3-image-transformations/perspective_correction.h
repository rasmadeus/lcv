#include <QtGlobal>
#include <vector>
#include <opencv2/opencv.hpp>
#include "common.h"

namespace lcv
{
    struct userdata
    {
        cv::Mat im;
        std::vector<cv::Point2f> points;
    };

    void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
    {
        Q_UNUSED(flags)

        if  ( event == cv::EVENT_LBUTTONDOWN )
        {
            auto data = static_cast<userdata*>(data_ptr);
            cv::circle(data->im, cv::Point{ x,y }, 3, cv::Scalar{ 0, 0, 255 }, 5, cv::LINE_AA);
            cv::imshow("Image", data->im);
            if (data->points.size() < 4)
                data->points.push_back(cv::Point2f{ static_cast<float>(x), static_cast<float>(y) });
        }
    }

    void perspective_correction()
    {
        auto im_src = imgFromQrc(QStringLiteral(":/res/book1.jpg"));
        cv::Size size{ 300, 400 };
        cv::Mat im_dst = cv::Mat::zeros(size, CV_8UC3);

        std::vector<cv::Point2f> pts_dst;
        pts_dst.push_back(cv::Point2f(0,0));
        pts_dst.push_back(cv::Point2f(size.width - 1, 0));
        pts_dst.push_back(cv::Point2f(size.width - 1, size.height -1));
        pts_dst.push_back(cv::Point2f(0, size.height - 1 ));

        auto im_temp = im_src.clone();
        userdata data;
        data.im = im_temp;

        cv::imshow("Image", im_temp);
        cv::setMouseCallback("Image", mouseHandler, &data);
        cv::waitKey(0);

        auto h = findHomography(data.points, pts_dst);
        cv::warpPerspective(im_src, im_dst, h, size);

        cv::imshow("Image", im_dst);
        cv::waitKey(0);
    }
}
