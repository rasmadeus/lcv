#ifndef HOMOGRAPHY_BOOK_H
#define HOMOGRAPHY_BOOK_H

namespace HomographyBook
{
    void test(const std::string& dir)
    {
        cv::Mat imgSrc = cv::imread(dir + "/book2.jpg");
        cv::Mat imgDst = cv::imread(dir + "/book1.jpg");

        std::vector<cv::Point2f> ptsSrc{
            { 141, 131 },
            { 480, 159 },
            { 493, 630 },
            { 64, 601 },
        };

        std::vector<cv::Point2f> ptsDst{
            { 318, 256 },
            { 534, 372 },
            { 316, 670 },
            { 73, 473 },
        };

        cv::Mat imOut;
        cv::Mat h = cv::findHomography(ptsSrc, ptsDst);

        cv::warpPerspective(imgSrc, imOut, h, imOut.size());

        cv::imshow("Source Image", imgSrc);
        cv::imshow("Destination Image", imgDst);
        cv::imshow("Warped Source Image", imOut);

        cv::waitKey(0);
    }
}

#endif //HOMOGRAPHY_BOOK_H
