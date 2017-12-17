#include "historylog.h"

Historylog::Historylog(QObject *parent) : QObject(parent)
{
    mem = "None";

}

int Historylog::setlog(QString str,QString str_face_token)
{
    mem = str;
    face_str = str_face_token;
    return 0;
}

void Historylog::loglocal()
{
    QFile file("G:\\log.txt");
    QDateTime dt;
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString currentDate = dt.toString("yyyy:MM:dd:hh:mm:ss");
    qDebug()<<currentDate<<"-=-=-=-=-=-=-=-";
    QString d = currentDate + " \r\n >> " + mem + " [" + face_str + "] \r\n";
    file.write(d.toLatin1());
}
