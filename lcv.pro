QT += core gui widgets

TARGET = lcv
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += precompile_header c++14
PRECOMPILED_HEADER = pch.h

include(./opencv.pri)
include(./day-1-basic-operations/day-1-basic-operations.pri)

SOURCES += \
    main.cpp \
    starter.cpp

HEADERS += \
    pch.h \
    starter.h
