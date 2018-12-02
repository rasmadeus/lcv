QT += core gui widgets

TARGET = lcv
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += precompile_header c++14
PRECOMPILED_HEADER = pch.h

include(./opencv.pri)

SOURCES += \
    main.cpp

HEADERS += \
    pch.h
