#ifndef VIRTUAL_BILLBOARD_H
#define VIRTUAL_BILLBOARD_H

namespace VirtualBillboard
{
    struct UserData
    {
        cv::Mat im;
        std::vector<cv::Point2f> points;
    };

    void mouseHandler(int ev, int x, int y, int flags, void* dataPtr)
    {
        std::ignore = flags;

        if (ev == cv::EVENT_LBUTTONDOWN )
        {
            auto data = static_cast<UserData*>(dataPtr);
            cv::circle(data->im, cv::Point{ x, y }, 3, cv::Scalar{ 0, 255, 255 }, 5, CV_AA);
            cv::imshow("Image", data->im);
            if (data->points.size() < 4)
                data->points.emplace_back(cv::Point2f{ x, y });
        }
    }

    void test(const std::string& dir)
    {
        cv::Mat imgSrc = cv::imread(dir + "/first-image.jpg");
        cv::Size size = imgSrc.size();

        std::vector<cv::Point2f> ptsSrc{
            { 0 , 0 },
            { size.width - 1, 0 },
            { size.width - 1, size.height - 1 },
            { 0, size.height - 1 },
        };

        cv::Mat imgDst = cv::imread(dir + "/times-square.jpg");

        cv::Mat imgTemp = imgDst.clone();
        UserData data;
        data.im = imgTemp;

        cv::imshow("Image", imgTemp);

        std::cout
            << "Click on four corners of a billboard and then press ENTER"
            << std::endl;

        cv::setMouseCallback("Image", mouseHandler, &data);
        cv::waitKey(0);

        cv::Mat h = cv::findHomography(ptsSrc, data.points);
        cv::warpPerspective(imgSrc, imgTemp, h, imgTemp.size());

        cv::Point ptsDst[4];
        for( int i = 0; i < 4; i++)
            ptsDst[i] = data.points[i];

        cv::fillConvexPoly(imgDst, ptsDst, 4, cv::Scalar{ 0 }, CV_AA);

        imgDst = imgDst + imgTemp;
        cv::imshow("Image", imgDst);
        cv::waitKey(0);
    }
}

#endif //VIRTUAL_BILLBOARD_H
