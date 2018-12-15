#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "common.h"

namespace lcv
{
    namespace day4
    {
        void detect_face_demo()
        {
            int const faceNeighborsMax = 10;
            int const neighborStep = 1;

            auto const faceCascadePath = QString("models/haarcascade_frontalface_default.xml");
            cv::CascadeClassifier faceCascade;
            if(!faceCascade.load(faceCascadePath.toStdString()))
            {
                printf("--(!)Error loading face cascade\n");
                return;
            };

            std::vector<cv::Rect> faces;
            cv::Mat frame = imgFromQrc(QStringLiteral(":/res/models/hillary_clinton.jpg"));
            cv::Mat frameGray;
            cv::Mat frameClone;
            cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

            for (int neight = 0; neight < faceNeighborsMax; neight = neight + neighborStep)
            {
                frameClone = frame.clone();
                faceCascade.detectMultiScale( frameGray, faces, 1.2, neight);

                for(size_t i = 0; i < faces.size(); ++i)
                {
                    auto const x = faces[i].x;
                    auto const y = faces[i].y;
                    auto const w = faces[i].width;
                    auto const h = faces[i].height;

                    cv::rectangle(frameClone, cv::Point{ x, y }, cv::Point{ x + w, y + h }, cv::Scalar{ 255, 0, 0 }, 2, 4);
                }

                cv::putText(frameClone, cv::format("# Neighbors = %d", neight), cv::Point{ 10, 50 }, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar{ 0, 0, 255 }, 4);
                cv::imshow("Face Detection Demo", frameClone);
                auto const k = cv::waitKey(500);
                if(k == 27)
                {
                    cv::destroyAllWindows();
                    break;
                }
            }
        }
    }
}
