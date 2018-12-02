#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <QFile>
#include <QStringView>
#include <opencv2/opencv.hpp>

namespace lcv
{
    inline cv::Mat imgFromQrc(QStringView qrc, int flag = cv::IMREAD_COLOR)
    {
        QFile file{ qrc.toString() };
        cv::Mat res;
        if (file.open(QIODevice::ReadOnly))
        {
            auto const size = file.size();
            std::vector<uchar> buf;
            buf.resize(static_cast<std::vector<uchar>::size_type>(size));
            file.read(reinterpret_cast<char*>(buf.data()), size);
            res = cv::imdecode(buf, flag);
        }
        return  res;
    }
}

#endif // COMMON_H
