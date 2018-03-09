#include "starter.h"

int main(int argc, char *argv[])
{
    QApplication app{ argc, argv };
    Starter starter;
    starter.show();
    return app.exec();
}
