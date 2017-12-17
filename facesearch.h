#ifndef FACESEARCH_H
#define FACESEARCH_H

#include <QObject>
#include <QString>
//#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define SEARCH_API "https://api-cn.faceplusplus.com/facepp/v3/search"
#define KEY "hi use your own key"
#define SECRET "hi use yur own secret"
#define OUTER_ID "myfaceset"
#define FACESET_TOKEN "560fa910f1db44d40de52bd89703af5c"

class Facesearch : public QObject
{
    Q_OBJECT
public:
    explicit Facesearch(QObject *parent = nullptr);
    //void search(QImage &image);
    int setsearch(QString face_token);
    QString getuserid();

signals:
    void search_ready();

public slots:
    void on_ready_slot(QNetworkReply *reply);

private:
    QNetworkAccessManager *network_manager_search;
    QString boundary;
    QString startboundary;
    QString endboundary;
    QString contenttype;
    QString face_token_result;
};

#endif // FACESEARCH_H
