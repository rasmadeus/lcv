INCLUDEPATH += \
    $$(OPENCV_HOME)/include/opencv4

LIBS += \
    -L$$(OPENCV_HOME)/lib -lopencv_dnn -lopencv_calib3d -lopencv_objdetect -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_video -lopencv_core
