INCLUDEPATH += \
    $$(OPENCV_HOME)/include

LIBS += \
    -L$$(OPENCV_HOME)/lib -lopencv_dnn -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_core