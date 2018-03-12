#ifndef PERSPECTIVE_CORRECION_H
#define PERSPECTIVE_CORRECION_H

namespace PerspectiveCorrection
{
    struct UserData
    {
        cv::Mat im;
        std::vector<cv::Point2f> points;
    };

    void mouseHandler(int ev, int x, int y, int flags, void* dataPtr)
    {
        std::ignore = flags;

        if  ( ev == cv::EVENT_LBUTTONDOWN )
        {
            auto data = static_cast<UserData*>(dataPtr);
            cv::circle(data->im, cv::Point{ x,y }, 3, cv::Scalar{ 0, 0, 255 }, 5, CV_AA);
            cv::imshow("Image", data->im);
            if (data->points.size() < 4)
                data->points.emplace_back(cv::Point2f{ x, y });
        }
    }

    void test(const std::string& path)
    {
        cv::Mat imgSrc = cv::imread(path);
        cv::Size size{ 300, 400 };
        cv::Mat imgDst = cv::Mat::zeros(size, CV_8UC3);

        std::vector<cv::Point2f> ptsDst{
            { 0, 0 },
            { size.width - 1, 0 },
            { size.width - 1, size.height - 1 },
            { 0, size.height - 1 },
        };

        cv::Mat imgTemp = imgSrc.clone();
        UserData data;
        data.im = imgTemp;

        std::cout
            << "Click on the four corners of the book -- top left first and"
            << std::endl
            << "bottom left last -- and then hit ENTER"
            << std::endl;

        cv::imshow("Image", imgTemp);
        cv::setMouseCallback("Image", mouseHandler, &data);
        cv::waitKey(0);

        cv::Mat h = cv::findHomography(data.points, ptsDst);
        cv::warpPerspective(imgSrc, imgDst, h, size);

        cv::imshow("Image", imgDst);
        cv::waitKey(0);
    }
}

#endif //PERSPECTIVE_CORRECION
