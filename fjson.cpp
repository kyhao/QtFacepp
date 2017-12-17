#include "fjson.h"
//#include <QDebug>

FJson::FJson(QObject *parent) : QObject(parent)
{

}

void FJson::splitJson(QString &str)
{
    QJsonParseError complex_json_error;
    QJsonDocument complex_parse_doucment = QJsonDocument::fromJson(str.toUtf8(), &complex_json_error);
    if (complex_json_error.error == QJsonParseError::NoError)
    {
        //开始解析json对象
        if (complex_parse_doucment.isObject())
        {
            QJsonObject jsonObject = complex_parse_doucment.object();
            if (jsonObject.contains("faces"))
            {
                //qDebug() << "-1-";
                QJsonValue faces_value = jsonObject.take("faces");
                if (faces_value.isArray())//判断他是不是json数组
                {
                    //qDebug() << "-2-";
                    QJsonArray faces_array = faces_value.toArray();
                    faces_value = faces_array.at(0);
                    if (faces_value.isObject())
                    {
                        //qDebug() << "-3-";
                        QJsonObject faces_object = faces_value.toObject();
                        /*********************************start 1****************************************/
                        /******faces: attributes, face_rectangle, face_token******/
                        if(faces_object.contains("attributes"))
                        {
                            //qDebug() << "-4-";
                            QJsonValue attributes_value = faces_object.take("attributes");
                            if(attributes_value.isObject()){
                                //qDebug() << "-5-";
                                QJsonObject attributes_object = attributes_value.toObject();
                                /*********************************start 2****************************************/
                                /******attributes: gender, age, emotion, ethnicity, beauty, skinstatus******/
                                if(attributes_object.contains("gender"))
                                {
                                    QJsonValue attributes_value1 = attributes_object.take("gender");
                                    if(attributes_value1.isObject())
                                    {
                                        //qDebug() << "-6-";
                                        QJsonObject attributes_gender = attributes_value1.toObject();
                                        if(attributes_gender.contains("value"))
                                        {
                                            //qDebug() << "-7-gender";
                                            QJsonValue gender = attributes_gender.take("value");
                                            face.attributes.gender = gender.toString();
                                            sex = gender.toString();
                                        }
                                    }
                                }

                                if(attributes_object.contains("age"))
                                {
                                    QJsonValue attributes_value1 = attributes_object.take("age");
                                    if(attributes_value1.isObject())
                                    {
                                        //qDebug() << "-6-";
                                        QJsonObject attributes_age = attributes_value1.toObject();
                                        if(attributes_age.contains("value"))
                                        {
                                            //qDebug() << "-7-age";
                                            QJsonValue gender = attributes_age.take("value");
                                            face.attributes.age = gender.toInt();
                                        }
                                    }
                                }

                                if(attributes_object.contains("emotion"))
                                {
                                    QJsonValue attributes_value1 = attributes_object.take("emotion");
                                    if(attributes_value1.isObject())
                                    {
                                        //qDebug() << "-6-";//0anger：愤怒 1disgust：厌恶 2fear：恐惧 3happiness：高兴 4neutral：平静 5sadness：伤心 6surprise：惊讶
                                        QJsonObject attributes_emotion = attributes_value1.toObject();
                                        if(attributes_emotion.contains("anger"))
                                        {
                                            //qDebug() << "-7-0";
                                            QJsonValue v1 = attributes_emotion.take("anger");
                                            face.attributes.emotion[0] = v1.toDouble();
                                        }
                                        if(attributes_emotion.contains("disgust"))
                                        {
                                            //qDebug() << "-7-1";
                                            QJsonValue v1 = attributes_emotion.take("disgust");
                                            face.attributes.emotion[1] = v1.toDouble();

                                        }
                                        if(attributes_emotion.contains("fear"))
                                        {
                                            //qDebug() << "-7-2";
                                            QJsonValue v1 = attributes_emotion.take("fear");
                                            face.attributes.emotion[2] = v1.toDouble();
                                        }
                                        if(attributes_emotion.contains("happiness"))
                                        {
                                            //qDebug() << "-7-3";
                                            QJsonValue v1 = attributes_emotion.take("happiness");
                                            face.attributes.emotion[3] = v1.toDouble();
                                        }
                                        if(attributes_emotion.contains("neutral"))
                                        {
                                            //qDebug() << "-7-4";
                                            QJsonValue v1 = attributes_emotion.take("neutral");
                                            face.attributes.emotion[4] = v1.toDouble();
                                        }
                                        if(attributes_emotion.contains("sadness"))
                                        {
                                            //qDebug() << "-7-5";
                                            QJsonValue v1 = attributes_emotion.take("sadness");
                                            face.attributes.emotion[5] = v1.toDouble();
                                        }
                                        if(attributes_emotion.contains("surprise"))
                                        {
                                            //qDebug() << "-7-6";
                                            QJsonValue v1 = attributes_emotion.take("surprise");
                                            face.attributes.emotion[6] = v1.toDouble();
                                        }
                                    }
                                }

                                if(attributes_object.contains("ethnicity"))
                                {
                                    QJsonValue attributes_value1 = attributes_object.take("ethnicity");
                                    if(attributes_value1.isObject())
                                    {
                                        //qDebug() << "-6-";
                                        QJsonObject attributes_gender = attributes_value1.toObject();
                                        if(attributes_gender.contains("value"))
                                        {
                                            //qDebug() << "-7-ethnicty";
                                            QJsonValue gender = attributes_gender.take("value");
                                            face.attributes.ethnicty = gender.toString();
                                        }
                                    }
                                }

                                if(attributes_object.contains("beauty"))
                                {
                                    QJsonValue attributes_value1 = attributes_object.take("beauty");
                                    if(attributes_value1.isObject())
                                    {
                                        //qDebug() << "-6-";
                                        QJsonObject attributes_gender = attributes_value1.toObject();
                                        if(attributes_gender.contains(sex.toLower() + "_score"))
                                        {
                                            //qDebug() << "-7-beauty";
                                            QJsonValue gender = attributes_gender.take(sex.toLower() + "_score");
                                            face.attributes.beauty = gender.toDouble();
                                        }
                                    }
                                }

                                if(attributes_object.contains("skinstatus"))
                                {
                                    QJsonValue attributes_value1 = attributes_object.take("skinstatus");
                                    if(attributes_value1.isObject())
                                    {
                                        //qDebug() << "-6-";
                                        //health：健康 stain：色斑  acne：青春痘 dark_circle：黑眼圈
                                        QJsonObject attributes_skinstatus = attributes_value1.toObject();
                                        if(attributes_skinstatus.contains("health"))
                                        {
                                            //qDebug() << "-7-00";
                                            QJsonValue v1 = attributes_skinstatus.take("health");
                                            face.attributes.skinstatus[0] = v1.toDouble();
                                        }
                                        if(attributes_skinstatus.contains("stain"))
                                        {
                                            //qDebug() << "-7-01";
                                            QJsonValue v1 = attributes_skinstatus.take("stain");
                                            face.attributes.skinstatus[1] = v1.toDouble();
                                        }
                                        if(attributes_skinstatus.contains("acne"))
                                        {
                                            //qDebug() << "-7-02";
                                            QJsonValue v1 = attributes_skinstatus.take("acne");
                                            face.attributes.skinstatus[2] = v1.toDouble();
                                        }
                                        if(attributes_skinstatus.contains("dark_circle"))
                                        {
                                            //qDebug() << "-7-03";
                                            QJsonValue v1 = attributes_skinstatus.take("dark_circle");
                                            face.attributes.skinstatus[3] = v1.toDouble();
                                        }
                                    }
                                }
                                /*********************************end 2****************************************/
                            }
                        }
                        if(faces_object.contains("face_rectangle"))
                        {
                            //qDebug() << "--4--";
                            QJsonValue face_rectangle_value = faces_object.take("face_rectangle");
                            if(face_rectangle_value.isObject())
                            {
                                //qDebug() << "--5--";
                                QJsonObject face_rectangle_object = face_rectangle_value.toObject();
                                if(face_rectangle_object.contains("width")){
                                    QJsonValue face_rectangle_width = face_rectangle_object.take("width");
                                    face.facerect.width = face_rectangle_width.toInt();
                                }
                                if(face_rectangle_object.contains("height")){
                                    QJsonValue face_rectangle_height = face_rectangle_object.take("height");
                                    face.facerect.height = face_rectangle_height.toInt();
                                }
                                if(face_rectangle_object.contains("top")){
                                    QJsonValue face_rectangle_top = face_rectangle_object.take("top");
                                    face.facerect.top = face_rectangle_top.toInt();
                                }
                                if(face_rectangle_object.contains("left")){
                                    QJsonValue face_rectangle_left = face_rectangle_object.take("left");
                                    face.facerect.left = face_rectangle_left.toInt();
                                }
                            }
                        }
                        if(faces_object.contains("face_token"))
                        {
                            //qDebug() << "---4---";
                            QJsonValue face_token = faces_object.take("face_token");
                            face.token = face_token.toString();
                            //qDebug() << face_token.toString();
                        }
                        /*********************************end 1****************************************/
                    }
                }
            }
        }
    }
}

Face FJson::getfaceinfo()
{
    return face;
}
