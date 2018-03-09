#include "starter.h"

#include "readWriteDisplay.h"
#include "cropAndResize.h"
#include "rotate.h"

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
