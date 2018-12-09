#include <QtGlobal>
#include <vector>
#include <opencv2/opencv.hpp>
#include "common.h"

namespace lcv
{
    namespace day2
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
                cv::circle(data->im, cv::Point{ x, y }, 3, cv::Scalar{ 0, 0, 255 }, 5, cv::LINE_AA);
                cv::imshow("Image", data->im);
                if (data->points.size() < 4)
                    data->points.push_back(cv::Point2f{ static_cast<float>(x), static_cast<float>(y) });
            }
        }

        void virtual_billboard()
        {
            auto im_src = imgFromQrc(QStringLiteral(":/res/first-image.jpg"));
            auto const size = im_src.size();

            std::vector<cv::Point2f> pts_src;
            pts_src.push_back(cv::Point2f(0,0));
            pts_src.push_back(cv::Point2f(size.width - 1, 0));
            pts_src.push_back(cv::Point2f(size.width - 1, size.height -1));
            pts_src.push_back(cv::Point2f(0, size.height - 1 ));

            auto im_dst = imgFromQrc(QStringLiteral(":/res/times-square.jpg"));
            auto im_temp = im_dst.clone();
            userdata data;
            data.im = im_temp;

            cv::imshow("Image", im_temp);

            cv::setMouseCallback("Image", mouseHandler, &data);
            cv::waitKey(0);

            cv::Mat h = findHomography(pts_src, data.points);

            cv::warpPerspective(im_src, im_temp, h, im_temp.size());
            cv::Point pts_dst[4];
            for(std::size_t i = 0; i < 4; i++)
                pts_dst[i] = data.points[i];

            cv::fillConvexPoly(im_dst, pts_dst, 4, cv::Scalar(0), cv::LINE_AA);

            im_dst = im_dst + im_temp;

            cv::imshow("Image", im_dst);
            cv::waitKey(0);
        }
    }
}
