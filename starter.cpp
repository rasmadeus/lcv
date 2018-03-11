#include "starter.h"

#include "readWriteDisplay.h"
#include "cropAndResize.h"
#include "rotate.h"

#include "drawShape.h"
#include "highguiMouse.h"
#include "videoRead.h"
#include "videoWrite.h"

Starter::Starter(QWidget* parent)
    : QWidget{ parent }
{
    auto layout = new QVBoxLayout{ this };

    auto readWriteButton = new QPushButton{ tr("Read write display"), this };
    layout->addWidget(readWriteButton);
    connect(readWriteButton, &QPushButton::clicked, this, &Starter::readWriteDisplay);

    auto cropAndResizeButton = new QPushButton{ tr("Crop and resize example"), this };
    layout->addWidget(cropAndResizeButton);
    connect(cropAndResizeButton, &QPushButton::clicked, this, &Starter::cropAndResize);

    auto rotateButton = new QPushButton{ tr("Rotate example"), this };
    layout->addWidget(rotateButton);
    connect(rotateButton, &QPushButton::clicked, this, &Starter::rotate);

    auto drawShapeButton = new QPushButton{ tr("Draw shape"), this };
    layout->addWidget(drawShapeButton);
    connect(drawShapeButton, &QPushButton::clicked, this, &Starter::drawShape);

    auto paintButton = new QPushButton{ tr("Higui mouse"), this };
    layout->addWidget(paintButton);
    connect(paintButton, &QPushButton::clicked, this, &Starter::highguiMouse);

    auto readVideoButton = new QPushButton{ tr("Read video"), this };
    layout->addWidget(readVideoButton);
    connect(readVideoButton, &QPushButton::clicked, this, &Starter::videoRead);

    auto writeVideoButton = new QPushButton{ tr("Write video"), this };
    layout->addWidget(writeVideoButton);
    connect(writeVideoButton, &QPushButton::clicked, this, &Starter::videoWrite);
}

void Starter::readWriteDisplay()
{
    const auto path = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (!path.isEmpty())
    {
        ReadWriteDisplay::test(path.toStdString());
    }
}

void Starter::cropAndResize()
{
    const auto path = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (!path.isEmpty())
    {
        CropAndResize::test(path.toStdString());
    }
}

void Starter::rotate()
{
    const auto path = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (!path.isEmpty())
    {
        Rotate::test(path.toStdString());
    }
}

void Starter::drawShape()
{
    const auto path = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (!path.isEmpty())
    {
        DrawShape::test(path.toStdString());
    }
}

void Starter::highguiMouse()
{
    const auto path = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (!path.isEmpty())
    {
        HiguiMouse::test(path.toStdString());
    }
}

void Starter::videoRead()
{
    const auto path = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (!path.isEmpty())
    {
        VideoRead::test(path.toStdString());
    }
}

void Starter::videoWrite()
{
    VideoWrite::test();
}
