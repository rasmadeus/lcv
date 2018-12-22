#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "common.h"

namespace lcv
{
    namespace day6
    {
        double const confThreshold = 0.5;
        double const nmsThreshold = 0.4;
        int const inpWidth = 416;
        int const inpHeight = 416;
        static std::vector<std::string> classes;

        void draw_pred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame)
        {
            cv::rectangle(frame, cv::Point{ left, top }, cv::Point{ right, bottom }, cv::Scalar{ 255, 178, 50 }, 3);
            std::string label = cv::format("%.2f", static_cast<double>(conf));
            if (!classes.empty())
            {
                CV_Assert(classId < static_cast<int>(classes.size()));
                label = classes[static_cast<std::size_t>(classId)] + ":" + label;
            }

            int baseLine{ 0 };
            cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            top = std::max(top, labelSize.height);
            cv::rectangle(
                frame,
                cv::Point{ left, static_cast<int>(top - round(1.5 * labelSize.height)) },
                cv::Point{ static_cast<int>(left + round(1.5 * labelSize.width)), top + baseLine },
                cv::Scalar{ 255, 255, 255 },
                cv::FILLED
            );
            putText(frame, label, cv::Point{ left, top }, cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar{ 0, 0, 0 }, 1);
        }

        void postprocess(cv::Mat& frame, std::vector<cv::Mat> const &outs)
        {
            std::vector<int> classIds;
            std::vector<float> confidences;
            std::vector<cv::Rect> boxes;

            for (size_t i = 0; i < outs.size(); ++i)
            {
                float* data = reinterpret_cast<float*>(outs[i].data);
                for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
                {
                    cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
                    cv::Point classIdPoint;
                    double confidence{ 0 };
                    cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
                    if (confidence > confThreshold)
                    {
                        auto const centerX = static_cast<int>(data[0] * frame.cols);
                        auto const centerY = static_cast<int>(data[1] * frame.rows);
                        auto const width = static_cast<int>(data[2] * frame.cols);
                        auto const height = static_cast<int>(data[3] * frame.rows);
                        auto const left = centerX - width / 2;
                        auto const top = centerY - height / 2;

                        classIds.push_back(classIdPoint.x);
                        confidences.push_back(static_cast<float>(confidence));
                        boxes.push_back(cv::Rect(left, top, width, height));
                    }
                }
            }

            std::vector<int> indices;
            cv::dnn::NMSBoxes(boxes, confidences, confThreshold, static_cast<float>(nmsThreshold), indices);
            for (size_t i = 0; i < indices.size(); ++i)
            {
                auto const idx = static_cast<std::size_t>(indices[i]);
                auto const box = boxes[idx];
                draw_pred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width, box.y + box.height, frame);
            }
        }

        std::vector<cv::String> get_outputs_names(cv::dnn::Net const& net)
        {
            static std::vector<cv::String> names;
            if (names.empty())
            {
                std::vector<int> outLayers = net.getUnconnectedOutLayers();
                std::vector<cv::String> layersNames = net.getLayerNames();
                names.resize(outLayers.size());
                for (size_t i = 0; i < outLayers.size(); ++i)
                    names[i] = layersNames[static_cast<std::size_t>(outLayers[i] - 1)];
            }
            return names;
        }

        void detect(bool hasImage, bool hasVideo)
        {
            auto const classesFile = lcv::moveFile(QStringLiteral(":/res/coco.names"));
            std::ifstream ifs(classesFile.toStdString().c_str());
            std::string line;
            while (getline(ifs, line))
                classes.push_back(line);

            cv::String modelConfiguration = "yolov3.cfg";
            cv::String modelWeights = "yolov3.weights";

            cv::dnn::Net net = cv::dnn::readNetFromDarknet(modelConfiguration, modelWeights);
            std::string str;
            std::string outputFile;
            cv::VideoCapture cap;
            cv::VideoWriter video;
            cv::Mat frame;
            cv::Mat blob;

            try {

                outputFile = "yolo_out_cpp.avi";
                if (hasImage)
                {
                    str = "bird.jpg";
                    std::ifstream ifile(str);
                    if (!ifile) throw("error");
                    cap.open(str);
                    str.replace(str.end()-4, str.end(), "_yolo_out_cpp.jpg");
                    outputFile = str;
                }
                else if (hasVideo)
                {
                    // Open the video file
                    str = "run.mp4";
                    std::ifstream ifile(str);
                    if (!ifile) throw("error");
                    cap.open(str);
                    str.replace(str.end()-4, str.end(), "_yolo_out_cpp.avi");
                    outputFile = str;
                }
                else
                {
                    cap.open(0);
                }

            }
            catch(...)
            {
                std::cout << "Could not open the input image/video stream" << std::endl;
                return;
            }

            // Get the video writer initialized to save the output video
            if (!hasImage)
            {
                video.open(
                    outputFile,
                    cv::VideoWriter::fourcc('M','J','P','G'),
                    28,
                    cv::Size{ static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)) }
                );
            }
            static std::string const kWinName = "Deep learning object detection in OpenCV";
            cv::namedWindow(kWinName, cv::WINDOW_NORMAL);

            while (cv::waitKey(1) < 0)
            {
                cap >> frame;

                if (frame.empty())
                {
                    std::cout << "Done processing !!!" << std::endl;
                    std::cout << "Output file is stored as " << outputFile << std::endl;
                    cv::waitKey(3000);
                    break;
                }

                cv::dnn::blobFromImage(frame, blob, 1/255.0, cv::Size{ inpWidth, inpHeight }, cv::Scalar{ 0, 0, 0 }, true, false);
                net.setInput(blob);

                std::vector<cv::Mat> outs;
                net.forward(outs, get_outputs_names(net));
                postprocess(frame, outs);

                std::vector<double> layersTimes;
                double freq = cv::getTickFrequency() / 1000;
                double t = net.getPerfProfile(layersTimes) / freq;
                std::string label = cv::format("Inference time for a frame : %.2f ms", t);
                cv::putText(frame, label, cv::Point{ 0, 15 }, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar{ 0, 0, 255 });

                cv::Mat detectedFrame;
                frame.convertTo(detectedFrame, CV_8U);
                if (hasImage)
                    cv::imwrite(outputFile, detectedFrame);
                else
                    video.write(detectedFrame);

                cv::imshow(kWinName, frame);

            }

            cap.release();
            if (hasImage)
                video.release();
        }
    }
}
