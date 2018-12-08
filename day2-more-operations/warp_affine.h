#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "common.h"

namespace lcv
{
    void warp_affine()
    {
        auto source = imgFromQrc(QStringLiteral(":/res/sample.jpg"));
        source.at<cv::Vec3b>(100,100)[0]=0;
        source.at<cv::Vec3b>(100,100)[1]=255;
        source.at<cv::Vec3b>(100,100)[2]=0;
        source.at<cv::Vec3b>(100,98)[0]=0;
        source.at<cv::Vec3b>(100,98)[1]=255;
        source.at<cv::Vec3b>(100,98)[2]=0;
        source.at<cv::Vec3b>(100,102)[0]=0;
        source.at<cv::Vec3b>(100,102)[1]=255;
        source.at<cv::Vec3b>(100,102)[2]=0;
        source.at<cv::Vec3b>(102,100)[0]=0;
        source.at<cv::Vec3b>(102,100)[1]=255;
        source.at<cv::Vec3b>(102,100)[2]=0;
        source.at<cv::Vec3b>(98,100)[0]=0;
        source.at<cv::Vec3b>(98,100)[1]=255;
        source.at<cv::Vec3b>(98,100)[2]=0;
        source.at<cv::Vec3b>(98,98)[0]=0;
        source.at<cv::Vec3b>(98,98)[1]=255;
        source.at<cv::Vec3b>(98,98)[2]=0;
        source.at<cv::Vec3b>(98,102)[0]=0;
        source.at<cv::Vec3b>(98,102)[1]=255;
        source.at<cv::Vec3b>(98,102)[2]=0;
        source.at<cv::Vec3b>(102,102)[0]=0;
        source.at<cv::Vec3b>(102,102)[1]=255;
        source.at<cv::Vec3b>(102,102)[2]=0;
        source.at<cv::Vec3b>(102,98)[0]=0;
        source.at<cv::Vec3b>(102,98)[1]=255;
        source.at<cv::Vec3b>(102,98)[2]=0;
        source.at<cv::Vec3b>(280,360)[0]=0;
        source.at<cv::Vec3b>(280,360)[1]=255;
        source.at<cv::Vec3b>(280,360)[2]=0;
        source.at<cv::Vec3b>(278,360)[0]=0;
        source.at<cv::Vec3b>(278,360)[1]=255;
        source.at<cv::Vec3b>(278,360)[2]=0;
        source.at<cv::Vec3b>(282,360)[0]=0;
        source.at<cv::Vec3b>(282,360)[1]=255;
        source.at<cv::Vec3b>(282,360)[2]=0;
        source.at<cv::Vec3b>(280,362)[0]=0;
        source.at<cv::Vec3b>(280,362)[1]=255;
        source.at<cv::Vec3b>(280,362)[2]=0;
        source.at<cv::Vec3b>(280,358)[0]=0;
        source.at<cv::Vec3b>(280,358)[1]=255;
        source.at<cv::Vec3b>(280,358)[2]=0;
        source.at<cv::Vec3b>(278,358)[0]=0;
        source.at<cv::Vec3b>(278,358)[1]=255;
        source.at<cv::Vec3b>(278,358)[2]=0;
        source.at<cv::Vec3b>(282,358)[0]=0;
        source.at<cv::Vec3b>(282,358)[1]=255;
        source.at<cv::Vec3b>(282,358)[2]=0;
        source.at<cv::Vec3b>(282,362)[0]=0;
        source.at<cv::Vec3b>(282,362)[1]=255;
        source.at<cv::Vec3b>(282,362)[2]=0;
        source.at<cv::Vec3b>(278,362)[0]=0;
        source.at<cv::Vec3b>(278,362)[1]=255;
        source.at<cv::Vec3b>(278,362)[2]=0;
        source.at<cv::Vec3b>(400,300)[0]=0;
        source.at<cv::Vec3b>(400,300)[1]=255;
        source.at<cv::Vec3b>(400,300)[2]=0;
        source.at<cv::Vec3b>(402,300)[0]=0;
        source.at<cv::Vec3b>(402,300)[1]=255;
        source.at<cv::Vec3b>(402,300)[2]=0;
        source.at<cv::Vec3b>(398,300)[0]=0;
        source.at<cv::Vec3b>(398,300)[1]=255;
        source.at<cv::Vec3b>(398,300)[2]=0;
        source.at<cv::Vec3b>(402,298)[0]=0;
        source.at<cv::Vec3b>(402,298)[1]=255;
        source.at<cv::Vec3b>(402,298)[2]=0;
        source.at<cv::Vec3b>(400,298)[0]=0;
        source.at<cv::Vec3b>(400,298)[1]=255;
        source.at<cv::Vec3b>(400,298)[2]=0;
        source.at<cv::Vec3b>(398,298)[0]=0;
        source.at<cv::Vec3b>(398,298)[1]=255;
        source.at<cv::Vec3b>(398,298)[2]=0;
        source.at<cv::Vec3b>(400,302)[0]=0;
        source.at<cv::Vec3b>(400,302)[1]=255;
        source.at<cv::Vec3b>(400,302)[2]=0;
        source.at<cv::Vec3b>(402,302)[0]=0;
        source.at<cv::Vec3b>(402,302)[1]=255;
        source.at<cv::Vec3b>(402,302)[2]=0;
        source.at<cv::Vec3b>(398,302)[0]=0;
        source.at<cv::Vec3b>(398,302)[1]=255;
        source.at<cv::Vec3b>(398,302)[2]=0;

        cv::line(source, cv::Point2f{ 102, 102 }, cv::Point2f{ 358, 278 }, cv::Scalar{ 255, 0, 0 }, 1, 8,0);
        cv::line(source, cv::Point2f{ 362, 282 }, cv::Point2f{ 298, 398 }, cv::Scalar{ 255, 0, 0 }, 1, 8,0);
        cv::line(source, cv::Point2f{102, 102 }, cv::Point2f{ 298, 402 }, cv::Scalar{ 255, 0, 0 }, 1, 8,0);
        cv::imshow("points",source);

        cv::Mat warpMat = (cv::Mat_<double>(2,3) << 1.2, 0.2, 2, -0.3, 1.3, 1);
        cv::Mat warpMat2 = (cv::Mat_<double>(2,3) << 1.2, 0.3, 2, 0.2, 1.3, 1);

        cv::Mat result;
        cv::Mat result2;

        cv::warpAffine(source, result, warpMat, cv::Size{ static_cast<int>(1.5*source.rows), static_cast<int>(1.4*source.cols) }, cv::INTER_LINEAR, cv::BORDER_REFLECT_101);
        cv::warpAffine(source, result2, warpMat2,cv::Size{ static_cast<int>(1.5*source.rows), static_cast<int>(1.4*source.cols) }, cv::INTER_LINEAR, cv::BORDER_REFLECT_101);

        cv::imshow("Original", source);
        cv::imshow("Result", result);
        cv::imshow("Result2", result2);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }
}
