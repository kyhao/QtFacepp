#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QImage>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

#include "recface.h"
#include "facesearch.h"
#include "historylog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void drawfacerect();

private slots:
    //CameraUse
    void captureImage();
    void displayImage(int, QImage image);
    //showfacesttr
    void showfaceattr();
    void showname();

private:
    Ui::Widget *ui;
    //camera
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imagecapture;
    Recface *reg;
    Face face;
    Facesearch *search;
    QImage detect_image;
    Historylog log;
    //
};

#endif // WIDGET_H
