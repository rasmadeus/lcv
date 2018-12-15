#include <QApplication>
#include "detect_face_demo.h"
#include "detect_face_smile_demo.h"
#include "face_detection_opencv_dnn.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    lcv::day4::face_detection_dnn();
}
