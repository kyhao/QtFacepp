#include "recface.h"
#include <QDebug>

Recface::Recface(QObject *parent) : QObject(parent)
{
    network_manager = new QNetworkAccessManager;
    boundary = "----------0x1603a66d9b2L";
    startboundary = "--" + boundary;
    endboundary = "------------0x1603a66d9b2L--";
    contenttype = "multipart/form-data; boundary=" + boundary;
    connect(network_manager, &QNetworkAccessManager::finished, this, on_seccess_slot);  //inorder to get message
}

Face Recface::getInfo()
{
    return face;
}

//image through aliyun connect to face++
int Recface::setImage(QImage *image)
{
    QNetworkRequest network_request;
    QByteArray post_data;
    //change image
    QByteArray arr;
    QBuffer buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    image->save(&buffer, "jpg");

    //set post url
    network_request.setUrl(QUrl(DETECT_API));
    //set post header
    network_request.setHeader(QNetworkRequest::ContentTypeHeader,contenttype.toLatin1());
    //set post data
    QString temp_data = startboundary;
    temp_data += "\r\nContent-Disposition: form-data; name=\"api_key\"\r\n\r\n";
    temp_data += KEY;
    temp_data += "\r\n";
    temp_data += startboundary;
    temp_data += "\r\nContent-Disposition: form-data; name=\"api_secret\"\r\n\r\n";
    temp_data += SECRET;
    temp_data += "\r\n";
    temp_data += startboundary;
    temp_data += "\r\nContent-Disposition: form-data; name=\"image_file\"; filename=\" \" \r\n";
    temp_data += "Content-Type: application/octet-stream\r\n\r\n";
    post_data.append(temp_data.toLatin1());     //add first info
    post_data.append(arr);                      //add image info
    //temp_data += arr;
    temp_data = "\r\n";
    temp_data += startboundary;
    temp_data += "\r\nContent-Disposition: form-data; name=\"return_attributes\"\r\n\r\n";
    temp_data += "gender,age,smiling,headpose,facequality,blur,emotion,ethnicity,beauty,skinstatus";
    temp_data += "\r\n";
    temp_data += endboundary;
    temp_data += "\r\n";
    //qDebug(temp_data.toLatin1());
    post_data.append(temp_data.toLatin1());     //add second info

    network_manager->post(network_request,post_data);

    return OK;
}

void Recface::on_seccess_slot(QNetworkReply *reply)
{
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    //error check
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  //get bytearray
        QString result(bytes);  //change to str
        FJson json;
        json.splitJson(result);
        face = json.getfaceinfo();
        emit face_ready();
        qDebug() << result;
    }
    else
    {
        //pross erro
    };
}
