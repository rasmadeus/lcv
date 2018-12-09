#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "common.h"

namespace lcv
{
    void homography_book()
    {
        auto im_src = imgFromQrc(QStringLiteral(":/res/book2.jpg"));
        auto im_dst = imgFromQrc(QStringLiteral(":/res/book1.jpg"));

        std::vector<cv::Point2f> pts_src;
        std::vector<cv::Point2f> pts_dst;

        pts_src.push_back(cv::Point2f(141, 131));
        pts_src.push_back(cv::Point2f(480, 159));
        pts_src.push_back(cv::Point2f(493, 630));
        pts_src.push_back(cv::Point2f(64, 601));

        pts_dst.push_back(cv::Point2f(318, 256));
        pts_dst.push_back(cv::Point2f(534, 372));
        pts_dst.push_back(cv::Point2f(316, 670));
        pts_dst.push_back(cv::Point2f(73, 473));

        cv::Mat im_out;
        auto h = cv::findHomography(pts_src, pts_dst);

        cv::warpPerspective(im_src, im_out, h, im_out.size());

        cv:: imshow("Source Image", im_src);
        cv::imshow("Destination Image", im_dst);
        cv::imshow("Warped Source Image", im_out);
        cv::waitKey(0);
    }
}
