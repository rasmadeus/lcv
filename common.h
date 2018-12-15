#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <opencv2/opencv.hpp>

namespace lcv
{
    inline cv::Mat imgFromQrc(QString const &qrc, int flag = cv::IMREAD_COLOR)
    {
        QFile file{ qrc };
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

    inline QString moveFile(QString const &res)
    {
        QFile file{ res };
        if (!file.open(QIODevice::ReadOnly))
            return {};
        auto const path = QStringLiteral("%1/%2").arg(qApp->applicationDirPath()).arg(QFileInfo{ file.fileName() }.fileName());
        return file.copy(path) ? QString{} : path;
    }
}

#endif // COMMON_H
