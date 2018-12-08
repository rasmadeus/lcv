#include <QApplication>
#include "draw_shape.h"
#include "get_affine.h"
#include "warp_affine.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };
    lcv::warp_affine();
    return app.exec();
}
