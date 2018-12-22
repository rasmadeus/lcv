QT += core gui widgets

TARGET = lcv
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += precompile_header c++14
PRECOMPILED_HEADER = pch.h

include(./opencv.pri)
include(./day1-basic-operations/day1-basic-operations.pri)
include(./day2-more-operations/day2-more-operations.pri)
include(./day3-image-transformations/day3-image-transformations.pri)
include(./day4-face-detection/day4-face-detection.pri)
include(./day5-image-classification/day5-image-classification.pri)
include(./day6-object-detection/day6-object-detection.pri)

SOURCES += \
    main.cpp

HEADERS += \
    pch.h \
    common.h

RESOURCES += \
    res.qrc
