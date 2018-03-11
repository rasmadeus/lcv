#ifndef VIDEO_READ_H
#define VIDEO_READ_H

namespace VideoRead
{
    void test(const std::string& path)
    {
        cv::VideoCapture cap{ path };
        if(!cap.isOpened())
        {
            std::cerr << "Error opening video stream or file" << std::endl;
            return;
        }

        while(true)
        {
            cv::Mat frame;
            cap >> frame;

            if (frame.empty())
                break;

            cv::imshow( "Frame", frame );

            const auto c = static_cast<char>(cv::waitKey(25));
            if(c == 27)
                break;
        }

        cap.release();
        cv::destroyAllWindows();
    }
}

#endif //VIDEO_READ
