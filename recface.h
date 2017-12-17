#ifndef RECFACE_H
#define RECFACE_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QBuffer>
#include "fjson.h"

#define OK 0
#define FAILL 1
#define TPATH "./temp.jpg"
#define DETECT_API "https://api-cn.faceplusplus.com/facepp/v3/detect"
#define SEARCH_API "https://api-cn.faceplusplus.com/facepp/v3/search"
#define KEY "NJQdCeNOP9wBVowR2QassVqnXk95G933"
#define SECRET "iWDX7orR0IQfjYGlleHi_4LQfmyPzzgf"

class Recface : public QObject
{
    Q_OBJECT
public:
    explicit Recface(QObject *parent = nullptr);
    Face getInfo();
    int setImage(QImage *image);

signals:
    void face_ready();

public slots:
    void on_seccess_slot(QNetworkReply *reply);

private:
    QNetworkAccessManager *network_manager;
    QString boundary;
    QString startboundary;
    QString endboundary;
    QString contenttype;
    Face face;
};

#endif // RECFACE_H
