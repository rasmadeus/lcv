#include "common.h"

namespace lcv
{
    void datatype_conversion()
    {
        constexpr double scale = 1 / 255.0;
        constexpr double shift = 0.0;

        auto source = imgFromQrc(QStringLiteral(":/res/sample.jpg"), cv::IMREAD_COLOR);
        source.convertTo(source, CV_32FC3, scale, shift);
        source.convertTo(source, CV_8UC3, 1.0 / scale, shift);

        cv::imshow("Converted img", source);
    }
}
