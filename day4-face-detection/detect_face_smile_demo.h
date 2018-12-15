#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "common.h"

namespace lcv
{
    namespace day4
    {
        void detect_face_smile()
        {
            cv::CascadeClassifier faceCascade;
            cv::CascadeClassifier smileCascade;

            auto const smileNeighborsMax = 100;
            auto const neighborStep = 2;

            auto const faceCascadePath = QStringLiteral("models/haarcascade_frontalface_default.xml");
            auto const smileCascadePath = QStringLiteral("models/haarcascade_smile.xml");

            if (!faceCascade.load(faceCascadePath.toStdString()))
            {
                printf("--(!)Error loading face cascade\n");
                return;
            };

            if (!smileCascade.load(smileCascadePath.toStdString()))
            {
                printf("--(!)Error loading smile cascade\n");
                return;
            };

            std::vector<cv::Rect> faces;
            auto const frame = lcv::imgFromQrc(QStringLiteral(":/res/models/hillary_clinton.jpg"));

            cv::Mat frameGray;
            cv::Mat frameClone;
            cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

            faceCascade.detectMultiScale(frameGray, faces, 1.4, 5);

            for (size_t i = 0; i < faces.size(); ++i)
            {
                auto const x = faces[i].x;
                auto const y = faces[i].y;
                auto const w = faces[i].width;
                auto const h = faces[i].height;

                cv::rectangle(frame, cv::Point{ x, y }, cv::Point{ x + w, y + h }, cv::Scalar{ 255, 0, 0 }, 2, 4);
                auto const faceROI = frameGray(faces[i]);
                for(int neight = 0; neight < smileNeighborsMax; neight = neight + neighborStep)
                {
                    std::vector<cv::Rect> smile;
                    auto const frameClone = frame.clone();
                    auto const faceROIClone = frameClone( faces[i] );
                    smileCascade.detectMultiScale(faceROI, smile, 1.5, neight);

                    for ( size_t j = 0; j < smile.size(); j++ )
                    {
                        auto const smileX = smile[j].x;
                        auto const smileY = smile[j].y;
                        auto const smileW = smile[j].width;
                        auto const smileH = smile[j].height;

                        cv::rectangle(faceROIClone, cv::Point{ smileX, smileY }, cv::Point{ smileX + smileW, smileY + smileH }, cv::Scalar{ 0, 255, 0 }, 2, 4);
                    }

                    cv::putText(frameClone, cv::format("# Neighbors = %d", neight), cv::Point{ 10, 50 }, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar{ 0, 0, 255 }, 4);
                    cv::imshow( "Face and Smile Demo", frameClone);
                    auto const k = cv::waitKey(500);
                    if(k ==  27)
                    {
                        cv::destroyAllWindows();
                        break;
                    }
                }
            }
        }
    }
}

