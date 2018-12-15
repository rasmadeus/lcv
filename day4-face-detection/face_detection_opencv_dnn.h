#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include "common.h"

namespace lcv
{
    namespace day4
    {
        size_t const inWidth = 300;
        size_t const inHeight = 300;
        double const inScaleFactor = 1.0;
        float const confidenceThreshold = 0.7f;
        cv::Scalar const meanVal{ 104.0, 177.0, 123.0 };

        void detect_face_opencv_dnn(cv::dnn::Net net, cv::Mat &frameOpenCVDNN)
        {
            auto const frameHeight = frameOpenCVDNN.rows;
            auto const frameWidth = frameOpenCVDNN.cols;
            auto const inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size{ inWidth, inHeight }, meanVal, true, false);

            net.setInput(inputBlob, "data");
            cv::Mat detection = net.forward("detection_out");
            cv::Mat detectionMat{ detection.size[2], detection.size[3], CV_32F, detection.ptr<float>() };

            for(int i = 0; i < detectionMat.rows; ++i)
            {
                float const confidence = detectionMat.at<float>(i, 2);
                if(confidence > confidenceThreshold)
                {
                    auto const x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
                    auto const y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
                    auto const x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
                    auto const y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);
                    cv::rectangle(frameOpenCVDNN, cv::Point{ x1, y1 }, cv::Point{ x2, y2 }, cv::Scalar{ 0, 255, 0 }, 2, 4);
                }
            }
        }

        void face_detection_dnn()
        {
            auto const caffeConfigFile = QStringLiteral("models/deploy.prototxt");
            auto const caffeWeightFile = QStringLiteral("models/res10_300x300_ssd_iter_140000_fp16.caffemodel");
            cv::dnn::Net net = cv::dnn::readNetFromCaffe(caffeConfigFile.toStdString(), caffeWeightFile.toStdString());

            cv::VideoCapture source{ 0 };
            cv::Mat frame;

            double tt_opencvDNN = 0;
            double fpsOpencvDNN = 0;

            while(true)
            {
                source >> frame;
                if(frame.empty())
                    break;

                double const t = cv::getTickCount();
                detect_face_opencv_dnn(net, frame);
                tt_opencvDNN = (static_cast<double>(cv::getTickCount()) - t) / cv::getTickFrequency();
                fpsOpencvDNN = 1.0 / tt_opencvDNN;
                cv::putText(frame, cv::format("OpenCV DNN ; FPS = %.2f", fpsOpencvDNN), cv::Point{ 10, 50 }, cv::FONT_HERSHEY_SIMPLEX, 1.4, cv::Scalar{ 0, 0, 255 }, 4);
                cv::imshow( "OpenCV - DNN Face Detection", frame);

                auto const k = cv::waitKey(5);
                if(k == 27)
                {
                    cv::destroyAllWindows();
                    break;
                }
            }
        }
    }
}

#define CAFFE
