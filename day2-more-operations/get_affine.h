#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <vector>

namespace lcv
{
    void get_affine()
    {
        std::vector<cv::Point2f> tri1;
        tri1.push_back(cv::Point2f{ 50, 50 });
        tri1.push_back(cv::Point2f{ 180, 140 });
        tri1.push_back(cv::Point2f{ 150, 200 });

        std::vector<cv::Point2f> tri2;
        tri2.push_back(cv::Point2f{ 72, 51 });
        tri2.push_back(cv::Point2f{ 246, 129 });
        tri2.push_back(cv::Point2f{ 222, 216 });

        std::vector<cv::Point2f> tri3;
        tri3.push_back(cv::Point2f{ 77, 76 });
        tri3.push_back(cv::Point2f{ 260, 219 });
        tri3.push_back(cv::Point2f{ 242, 291 });

        auto const warp = cv::getAffineTransform(tri1,tri2);
        auto const warp2 = cv::getAffineTransform(tri1,tri3);

        std::cout << "Warp Matrix 1 : \n\n " << warp << "\n\n" << "Warp Matrix 2 : \n" << warp2 << std::endl;
    }
}
