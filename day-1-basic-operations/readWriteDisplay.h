#ifndef READ_WRITE_DISPLAY_H
#define READ_WRITE_DISPLAY_H

namespace ReadWriteDisplay
{
    void test(const std::string& path)
    {
        cv::Mat image = cv::imread(path, cv::IMREAD_COLOR);
        if(image.empty())
        {
            std::cerr <<  "Could not open or find the image" << std::endl;
            return;
        }

        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

        cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("gray image", cv::WINDOW_NORMAL);

        cv::imshow("image", image);
        cv::imshow("gray image", grayImage);

        cv::imwrite("result.jpg", image);
        cv::imwrite("result_gray.jpg", grayImage);

        cv::waitKey(0);
    }
}

#endif //READ_WRITE_DISPLAY_H
