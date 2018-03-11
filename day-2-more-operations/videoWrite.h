#ifndef VIDEO_WRITE_H
#define VIDEO_WRITE_H

namespace VideoWrite
{
    void test()
    {
        cv::VideoCapture cap{ 0 };
        if(!cap.isOpened())
        {
            std::cerr << "Error opening video stream" << std::endl;
            return;
        }

        const int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        const int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        cv::VideoWriter video{ "outcpp.avi", CV_FOURCC('M','J','P','G'), 10, cv::Size{ frame_width, frame_height } };

        while(true)
        {
            cv::Mat frame;
            cap >> frame;

            if (frame.empty())
                break;

            video.write(frame);
            cv::imshow("Frame", frame );

            const auto c = static_cast<char>(cv::waitKey(1));
            if(c == 27)
                break;
        }

        cap.release();
        video.release();

        cv::destroyAllWindows();
    }
}

#endif //VIDEO_WRITE_H
