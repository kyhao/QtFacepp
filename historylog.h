#ifndef HISTORYLOG_H
#define HISTORYLOG_H

#include <QObject>
#include <QFile>
#include <QTime>
#include <QDate>
#include <QString>
#include <QDebug>

class Historylog : public QObject
{
    Q_OBJECT
public:
    explicit Historylog(QObject *parent = nullptr);
    int setlog(QString str = "None",QString str_face_token = "None");
    void loglocal();
    //void logyun();

signals:

public slots:

private:
    QString mem;
    QString face_str;
};

#endif // HISTORYLOG_H
