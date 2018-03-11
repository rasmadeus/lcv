#ifndef STARTER_H
#define STARTER_H

class Starter : public QWidget
{
    Q_OBJECT
public:
    explicit Starter(QWidget* parent = nullptr);

private:
    void readWriteDisplay();
    void cropAndResize();
    void rotate();

    void drawShape();
    void highguiMouse();
    void videoRead();
    void videoWrite();
};

#endif // STARTER_H
