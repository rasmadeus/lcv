#ifndef HIGUI_MOUSE_H
#define HIGUI_MOUSE_H

namespace HiguiMouse
{
    class MousePainter
    {
    public:
        void paintOn(const std::string& path)
        {
            source = cv::imread(path, 1);
            cv::Mat dummy = source.clone();
            cv::namedWindow("Window");
            cv::setMouseCallback("Window", callback, this);
            start(dummy);
        }

    private:
        static void callback(int action, int x, int y, int flags, void* userdata)
        {
            std::ignore = flags;
            static_cast<MousePainter*>(userdata)->drawCircle(action, x, y);
        }

        void start(cv::Mat& dummy)
        {
            int k = 0;
            while(k != 27)
            {
                cv::imshow("Window", source );
                cv::putText(source,"Choose center, and drag, Press ESC to exit and c to clear", cv::Point{ 10, 30 }, cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar{ 255, 255, 255 }, 2 );
                k = cv::waitKey(20) & 0xFF;
                if(k == 99)
                    dummy.copyTo(source);
            }
        }

        void drawCircle(int action, int x, int y)
        {
            if( action == cv::EVENT_LBUTTONDOWN )
            {
                center = cv::Point{ x, y };
                cv::circle(source, center, 1, cv::Scalar{ 255,255,0 }, 2, CV_AA );
            }
            else if(action == cv::EVENT_LBUTTONUP)
            {
                circumference = cv::Point{ x,y };
                const float radius = std::sqrt(
                    std::pow(center.x - circumference.x, 2) +
                    std::pow(center.y - circumference.y, 2)
                );
                cv::circle(source, center, radius, cv::Scalar{ 0, 255, 0 }, 2, CV_AA );
                cv::imshow("Window", source);
            }
        }

    private:
        cv::Point center;
        cv::Point circumference;
        cv::Mat source;
    };

    void test(const std::string& path)
    {
        MousePainter painter;
        painter.paintOn(path);
    }
}

#endif //HIGUI_MOUSE_H
