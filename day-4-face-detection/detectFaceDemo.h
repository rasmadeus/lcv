#ifndef DETECT_FACE_DEMO_H
#define DETECT_FACE_DEMO_H

namespace DetectFaceDemo
{
    class Detect
    {
    public:
        void detect(const std::string& dir)
        {
            const std::string& faceCascadePath = dir + "/models/haarcascade_frontalface_default.xml";
            if(!faceCascade.load(faceCascadePath))
            {
                std::cerr << "--(!)Error loading face cascade\n";
                return;
            }

            std::vector<cv::Rect> faces;

            cv::Mat frame = cv::imread(dir + "/hillary_clinton.jpg");
            cv::Mat frameGray, frameClone;
            cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

            for (int neight = 0; neight < faceNeighborsMax; neight = neight + neighborStep)
            {
                frameClone = frame.clone();
                faceCascade.detectMultiScale(frameGray, faces, 1.2, neight);

                for (std::size_t i = 0; i < faces.size(); i++)
                {
                    const int x = faces[i].x;
                    const int y = faces[i].y;
                    const int w = faces[i].width;
                    const int h = faces[i].height;
                    cv::rectangle(frameClone, cv::Point{ x, y }, cv::Point{ x + w, y + h }, cv::Scalar(255, 0, 0), 2, 4);
                }

                cv::putText(frameClone, cv::format("# Neighbors = %d", neight), cv::Point{ 10, 50 }, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar{ 0, 0, 255 }, 4);
                cv::imshow( "Face Detection Demo", frameClone );

                if (wait())
                    break;
            }
        }

    private:
        bool wait()
        {
            const int k = cv::waitKey(500);
            if(k == 27)
            {
                cv::destroyAllWindows();
                return true;
            }
            return false;
        }

    private:
        cv::CascadeClassifier faceCascade;
        const int faceNeighborsMax = 10;
        const int neighborStep = 1;
    };

    void test(const std::string& dir)
    {
        Detect detector;
        detector.detect(dir);
    }
}

#endif //DETECT_FACE_DEMO
