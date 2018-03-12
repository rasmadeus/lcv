#include "starter.h"

#include "readWriteDisplay.h"
#include "cropAndResize.h"
#include "rotate.h"

#include "drawShape.h"
#include "highguiMouse.h"
#include "videoRead.h"
#include "videoWrite.h"

#include "homographyBook.h"
#include "perspectiveCorrection.h"
#include "virtualBillboard.h"

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

    auto homographyBookButton = new QPushButton{ tr("Homography book"), this };
    layout->addWidget(homographyBookButton);
    connect(homographyBookButton, &QPushButton::clicked, this, &Starter::homographyBook);

    auto perspectiveCorrectionButton = new QPushButton{ tr("Perspective correction"), this };
    layout->addWidget(perspectiveCorrectionButton);
    connect(perspectiveCorrectionButton, &QPushButton::clicked, this, &Starter::perspectiveCorrection);

    auto virtualBillboardButton = new QPushButton{ tr("Virtual billboard"), this };
    layout->addWidget(virtualBillboardButton);
    connect(virtualBillboardButton, &QPushButton::clicked, this, &Starter::virtualBillboard);

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

void Starter::homographyBook()
{
    const auto dir = QFileDialog::getExistingDirectory(this, tr("Select dir"));
    if (!dir.isEmpty())
    {
        HomographyBook::test(dir.toStdString());
    }
}

void Starter::perspectiveCorrection()
{
    const auto path = QFileDialog::getOpenFileName(this, tr("Open image"));
    if (!path.isEmpty())
    {
        PerspectiveCorrection::test(path.toStdString());
    }
}

void Starter::virtualBillboard()
{
    const auto dir = QFileDialog::getExistingDirectory(this, tr("Select dir"));
    if (!dir.isEmpty())
    {
        VirtualBillboard::test(dir.toStdString());
    }
}
