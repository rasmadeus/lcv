#ifndef DETECT_FACE_SMILE_DEMO_H
#define DETECT_FACE_SMILE_DEMO_H

namespace DetectFaceAndSmileDemo
{
    void test(const std::string& dir)
    {
        const int smileNeighborsMax = 100;
        const int neighborStep = 2;

        std::string faceCascadePath = dir + "/models/haarcascade_frontalface_default.xml";
        std::string smileCascadePath = dir + "/models/haarcascade_smile.xml";
        cv::CascadeClassifier faceCascade, smileCascade;

        if(!faceCascade.load(faceCascadePath ) )
        {
            std::cout << "--(!)Error loading face cascade\n";
            return;
        };

        if(!smileCascade.load(smileCascadePath))
        {
            std::cout << "--(!)Error loading smile cascade\n";
            return;
        };

        std::vector<cv::Rect> faces;

        cv::Mat frame = cv::imread(dir + "/hillary_clinton.jpg");
        cv::Mat frameGray, frameClone;
        cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

        faceCascade.detectMultiScale(frameGray, faces, 1.4, 5);

        for (std::size_t i = 0; i < faces.size(); i++)
        {
            const int x = faces[i].x;
            const int y = faces[i].y;
            const int w = faces[i].width;
            const int h = faces[i].height;

            cv::rectangle(frame, cv::Point{ x, y }, cv::Point{ x + w, y + h }, cv::Scalar{ 255, 0, 0 }, 2, 4);
            cv::Mat faceROI = frameGray(faces[i]);

            for (int height = 0; height < smileNeighborsMax; height = height + neighborStep)
            {
                std::vector<cv::Rect> smile;
                cv::Mat frameClone = frame.clone();
                cv::Mat faceROIClone = frameClone(faces[i]);
                smileCascade.detectMultiScale(faceROI, smile, 1.5, height);

                for(std::size_t j = 0; j < smile.size(); j++)
                {
                    const int smileX = smile[j].x;
                    const int smileY = smile[j].y;
                    const int smileW = smile[j].width;
                    const int smileH = smile[j].height;

                    cv::rectangle(faceROIClone, cv::Point{ smileX, smileY }, cv::Point{ smileX + smileW, smileY + smileH }, cv::Scalar{ 0, 255, 0 }, 2, 4);
                }

                cv::putText(frameClone, cv::format("# Neighbors = %d", height), cv::Point{ 10, 50 }, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar{0, 0, 255}, 4);
                cv::imshow("Face and Smile Demo", frameClone);

                const int k = cv::waitKey(1000);
                if(k == 27)
                {
                    cv::destroyAllWindows();
                    break;
                }
            }
        }
    }
}

#endif //#ifndef DETECT_FACE_SMILE_DEMO_H
