#ifndef TILTMENUOPTIONSPARSER_H
#define TILTMENUOPTIONSPARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class TiltMenuModel;

class TiltMenuModelParser
{
public:
    TiltMenuModelParser(TiltMenuModel* model);

    void write();
    void writeSelection();

private:
    TiltMenuModel* m_model;
    QJsonArray m_array;
    QJsonObject m_jsonObject;
};

#endif // TILTMENUOPTIONSPARSER_H
