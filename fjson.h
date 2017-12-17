#ifndef FJSON_H
#define FJSON_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

struct Attributes{
    QString gender;
    qint32 age;
    double emotion[7];
    QString ethnicty;
    double beauty;
    double skinstatus[4];
};

struct Facerect{
    qint32 width;
    qint32 height;
    qint32 top;
    qint32 left;
};

struct Face{
    QString token;
    Attributes attributes;
    Facerect facerect;
};

class FJson : public QObject
{
    Q_OBJECT
public:
    explicit FJson(QObject *parent = nullptr);
    void splitJson(QString &str);
    Face getfaceinfo();
signals:

public slots:

private:
    Face face;
    QString sex;
};

#endif // FJSON_H
