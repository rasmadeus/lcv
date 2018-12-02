#include <QApplication>
#include "crop_and_resize.h"
#include "datatype_conversion.h"
#include "read_write_display.h"
#include "rotate.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };
    lcv::rotate();
    return app.exec();
}
