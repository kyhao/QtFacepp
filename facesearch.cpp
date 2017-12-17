#include "facesearch.h"

Facesearch::Facesearch(QObject *parent) : QObject(parent)
{
    network_manager_search = new QNetworkAccessManager;
    boundary = "----------0x1603a66d9b2L";
    startboundary = "--" + boundary;
    endboundary = "------------0x1603a66d9b2L--";
    contenttype = "multipart/form-data; boundary=" + boundary;
    face_token_result = "-1";
    connect(network_manager_search, &QNetworkAccessManager::finished, this, on_ready_slot);  //inorder to get message
}

int Facesearch::setsearch(QString face_token)
{
    QNetworkRequest network_request;
    QByteArray post_data;

    //set post url
    network_request.setUrl(QUrl(SEARCH_API));
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
    temp_data += "\r\nContent-Disposition: form-data; name=\"face_token\"\r\n\r\n";
    temp_data += face_token;
    temp_data += "\r\n";
    temp_data += startboundary;
    temp_data += "\r\nContent-Disposition: form-data; name=\"faceset_token\"\r\n\r\n";
    temp_data += FACESET_TOKEN;
    temp_data += "\r\n";
    temp_data += endboundary;
    temp_data += "\r\n";
    //qDebug(temp_data.toLatin1());
    post_data.append(temp_data.toLatin1());     //add info

    network_manager_search->post(network_request,post_data);

    return 0;
}

QString Facesearch::getuserid()
{
    return face_token_result;
}

void Facesearch::on_ready_slot(QNetworkReply *reply)
{
    QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    //error check
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();  //get bytearray
        QString result(bytes);  //change to str
        qDebug() << result;
        //json decode
        QJsonParseError complex_json_error;
        QJsonDocument complex_parse_doucment = QJsonDocument::fromJson(result.toUtf8(), &complex_json_error);
        if (complex_json_error.error == QJsonParseError::NoError)
        {
            //开始解析json对象
            if (complex_parse_doucment.isObject())
            {
                QJsonObject jsonObject = complex_parse_doucment.object();
                if (jsonObject.contains("results"))
                {
                    QJsonValue face_results = jsonObject.take("results");
                    QJsonArray face_array = face_results.toArray();
                    face_results = face_array.at(0);
                    QJsonObject face_object = face_results.toObject();
                    if(face_object.contains("user_id"))
                    {
                        qDebug() << "-1-";
                        QJsonValue value = face_object.take("user_id");
                        face_token_result = value.toString();
                    }
                    if(face_object.contains("confidence"))
                    {
                        qDebug() << "-1-";
                        QJsonValue value = face_object.take("confidence");
                        qDebug() << value.toDouble();
                        if(value.toDouble() > 70)
                        {
                            emit search_ready();
                        }
                    }
                }
            }
        }
        //emit search_ready();

    }
    else
    {
        //pross erro
    };
}
