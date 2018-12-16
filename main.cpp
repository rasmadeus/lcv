#include "image_classification_caffe.h"
#include "image_classification_tensorflow.h"
#include "train_digits.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    lcv::day5::train_digits();
}
