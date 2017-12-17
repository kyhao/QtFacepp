#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    camera=new QCamera(this);
    viewfinder=new QCameraViewfinder(this);
    imagecapture=new QCameraImageCapture(camera);
    reg = new Recface();  //connect to Ser
    search = new Facesearch();
    ui->horizontalLayout_show->addWidget(viewfinder);
    ui->picShow->setScaledContents(true);
    camera->setViewfinder(viewfinder);
    camera->start();
    connect(imagecapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(displayImage(int,QImage)));     //display pic
    connect(ui->ButtonGet, SIGNAL(clicked()), this, SLOT(captureImage()));                              //capture
    connect(reg, SIGNAL(face_ready()), this, SLOT(showfaceattr()));                                     //等待人脸检测成功信号
    connect(search, SIGNAL(search_ready()), this, SLOT(showname()));                                    //等待人脸识别信号
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawfacerect()
{
    qint32 w = face.facerect.width;
    qint32 h = face.facerect.height;
    qint32 t = face.facerect.top;
    qint32 l = face.facerect.left;
    for(int i = l;i < (l+w) ;i++)
    {
        detect_image.setPixel(QPoint(i,t), qRgb(255,0,0));
        detect_image.setPixel(QPoint(i,t-1), qRgb(255,0,0));
    }
    for(int i = l;i < (l+w) ;i++)
    {
        detect_image.setPixel(QPoint(i,(t+h)), qRgb(255,0,0));
        detect_image.setPixel(QPoint(i,(t+h+1)), qRgb(255,0,0));
    }
    for(int i = t;i < (t+h) ;i++)
    {
        detect_image.setPixel(QPoint(l,i), qRgb(255,0,00));
        detect_image.setPixel(QPoint(l-1,i), qRgb(255,0,0));
    }
    for(int i = t;i < (t+h) ;i++)
    {
        detect_image.setPixel(QPoint((l+w),i), qRgb(255,0,0));
        detect_image.setPixel(QPoint((l+w+1),i), qRgb(255,0,0));
    }
}

void Widget::showfaceattr()
{
    face = reg->getInfo();
    ui->lineEdit_gender->setText(face.attributes.gender);
    ui->lineEdit_age->setText(QString::number(face.attributes.age));
    ui->lineEdit_emotion->setText("face.attributes.emotion");
    ui->lineEdit_ethnicity->setText(face.attributes.ethnicty);
    ui->lineEdit_skinstatus->setText("face.attributes.skinstatus");
    ui->lineEdit_beauty->setText(QString::number(face.attributes.beauty));
    ui->lineEdit_name->setText("Denied");
    ui->lineEdit_name->setStyleSheet("background:red");
    //qDebug() << face.token;
    search->setsearch(face.token);
    //draw rect face
    drawfacerect();
    ui->picShow->setPixmap(QPixmap::fromImage(detect_image));
}

void Widget::showname()
{
    QString id = search->getuserid();
    ui->lineEdit_name->setText(id);
    log.setlog(id, face.token);
    log.loglocal();
    ui->lineEdit_name->setStyleSheet("background:green");
}

void Widget::captureImage()
{
    imagecapture->capture();
}

void Widget::displayImage(int, QImage image)
{
    ui->picShow->setPixmap(QPixmap::fromImage(image));
    reg->setImage(&image);
    detect_image = image;
}
