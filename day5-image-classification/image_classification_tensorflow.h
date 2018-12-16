#include <fstream>
#include <sstream>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "common.h"

namespace lcv
{
    namespace day5
    {
        void image_classification_tensorflow()
        {
            std::vector<std::string> classes;
            std::string weightFile = "models_day5/tensorflow_inception_graph.pb";
            auto const frame = imgFromQrc(QStringLiteral(":/res/panda.jpg"));
            std::string classFile = "models_day5/imagenet_comp_graph_label_strings.txt";
            std::ifstream ifs{ classFile.c_str() };
            std::string line;
            while (getline(ifs, line))
                classes.push_back(line);

            double const scale = 1.0;
            int const inHeight = 224;
            int const inWidth = 224;
            bool const swapRB = true;
            auto const mean = cv::Scalar{ 117, 117, 117 };

            auto net = cv::dnn::readNetFromTensorflow(weightFile);

            cv::Mat blob;
            cv::dnn::blobFromImage(frame, blob, scale, cv::Size{ inWidth, inHeight }, mean, swapRB, false);
            net.setInput(blob);

            cv::Mat prob = net.forward();
            cv::Point classIdPoint;
            double confidence;
            minMaxLoc(prob.reshape(1, 1), nullptr, &confidence, nullptr, &classIdPoint);
            int const classId = classIdPoint.x;

            std::string label = cv::format("Predicted Class : %s, confidence : %.3f", (classes[classId].c_str()), confidence);
            std::cout << label << std::endl;
            cv::putText(frame, label, cv::Point{ 10, 30 }, cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar{ 0, 0, 255 }, 2, cv::LINE_AA);

            cv::imshow("Classification Output", frame);
            cv::waitKey(0);
            cv::destroyAllWindows();
        }
    }
}
