#include "TiltMenuModelParser.h"
#include "TiltMenuModel.h"
#include "TiltMenuOptionsModel.h"
#include "TiltMenuOptionsItem.h"
#include <QJsonValue>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

TiltMenuModelParser::TiltMenuModelParser(TiltMenuModel* model) :
    m_model(model)
{
}

void TiltMenuModelParser::write()
{
    m_jsonObject["Id"] = m_model->getId();
    m_jsonObject["Width"] = m_model->getWidth();
    m_jsonObject["BorderWidth"] = m_model->getBorderWidth();
    m_jsonObject["IntervalMs"] = m_model->getIntervalMs();
    m_jsonObject["StartDateTimeUtc"] = m_model->getStartDateTime().toString();
    m_jsonObject["EndDateTimeUtc"] = m_model->getEndDateTime().toString();
    m_jsonObject["isTwoZone"] = m_model->isTwoZone();
    m_jsonObject["Selections"] = m_array;

    QJsonDocument jsonDocument(m_jsonObject);

    auto dir = QDir(QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
                                    QDir::separator() +
                                    "TiltMenu"));
    if (!dir.exists())
    {
        dir.mkpath(dir.absolutePath());
    }

    QFile jsonFile(QDir::cleanPath(dir.absolutePath() + QDir::separator() + QString("%1-%2-%3.json").arg(m_model->getId()).arg(m_model->isTwoZone() ? "2" : "4").arg(m_model->getStartDateTime().toString())));
    jsonFile.open(QFile::WriteOnly | QIODevice::Text);
    jsonFile.write(jsonDocument.toJson());
}

void TiltMenuModelParser::writeSelection()
{

    // Get the selected menu option
    auto tiltMenuOptionsModel = qobject_cast<TiltMenuOptionsModel*>(m_model->getTiltMenuOptionsModel());
    if (tiltMenuOptionsModel != nullptr)
    {
        auto selectedItem = tiltMenuOptionsModel->getSelectedItem();
        if (selectedItem != nullptr)
        {
            QJsonObject json;

            json["SelectionNo"] = (8 - m_model->targetsRemaining());
            json["TargetMenuOption"] = m_model->getTarget();
            json["ElapsedTimeMs"] = m_model->getElapsedTimeMs();
            json["SelectedMenuOption"] = selectedItem->data().toString();
            json["Success"] = selectedItem->data().toString() == m_model->getTarget();

            QJsonArray xRotationArray;
            for (double xRotation : m_model->getXRotationList())
            {
                QJsonValue value(xRotation);
                xRotationArray.append(value);
            }
            json["XRotationList"] = xRotationArray;

            QJsonArray yRotationArray;
            for (double yRotation : m_model->getYRotationList())
            {
                QJsonValue value(yRotation);
                yRotationArray.append(value);
            }
            json["YRotationList"] = yRotationArray;
            m_array.append(json);
        }
    }
}
