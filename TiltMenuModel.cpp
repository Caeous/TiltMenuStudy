#include "TiltMenuModel.h"
#include "TiltMenuOptionsItem.h"
#include "TiltMenuModelParser.h"

TiltMenuModel::TiltMenuModel(QObject *parent) :
    QObject(parent),
    m_tiltMenuModelParser(this)
{
    connect(this, &TiltMenuModel::xRotationChanged, this, &TiltMenuModel::hasSelectedItem);
    connect(this, &TiltMenuModel::yRotationChanged, this, &TiltMenuModel::hasSelectedItem);
    connect(this, &TiltMenuModel::selectedItem, this, &TiltMenuModel::handleSelectedMenuOption);
}

void TiltMenuModel::endTrial()
{
    m_tiltMenuModelParser.write();
}

void TiltMenuModel::startNewTrial()
{
    setLikert(0);

    populateTargetList();

    m_startTimeUtc = QDateTime::currentDateTimeUtc();
    m_endTimeUtc = QDateTime();

    startNewMenuSearch();

}

void TiltMenuModel::startNewMenuSearch()
{
    resetNavigation();

    m_xRotationList.clear();
    m_yRotationList.clear();

    m_timer.restart();

    // Go to Home
    if (m_tiltMenuOptionsModel != nullptr)
    {
        selectItem(m_tiltMenuOptionsModel->getRootItem());
    }
}

void TiltMenuModel::resetNavigation()
{
    m_x = m_xCenter;
    m_y = m_yCenter;

    emit xChanged(m_x);
    emit yChanged(m_y);
}

void TiltMenuModel::setLikert(int likert)
{
    if (m_likert == likert)
        return;

    m_likert = likert;
    emit likertChanged(m_likert);
}

void TiltMenuModel::populateTargetList()
{
    m_targetList.clear();

    // Create the target menu options and then randomize the menu options
    m_targetList << "Pulse" << "Text" << "Do not disturb" << "Sleep" << "Today" << "Tomorrow" << "Pulse" << "Calories";
    std::random_shuffle(m_targetList.begin(), m_targetList.end());

    m_tiltMenuOptionsModel->populateTargetList(m_isTwoZone);
    emit targetChanged(m_targetList.back());
    emit targetsRemainingChanged(m_targetList.count());
}

bool TiltMenuModel::isTwoZone() const
{
    return m_isTwoZone;
}

QString TiltMenuModel::getId() const
{
    return m_id;
}

void TiltMenuModel::setXRotation(double xRotation)
{
    m_xRotationList.push_back(xRotation);

    double xStep = xRotation;

    if (xStep < 1 && xStep > 0)
    {
        xStep = 0;
    }
    else if (xStep > -1 && xStep < 0)
    {
        xStep = 0;
    }

    emit xRotationChanged(xStep);

    setY(static_cast<int>(getY() + xStep));
}

void TiltMenuModel::setYRotation(double yRotation)
{
    m_yRotationList.push_back(yRotation);

    double yStep = yRotation;

    if (yStep < 1 && yStep > 0)
    {
        yStep = 0;
    }
    else if (yStep > -1 && yStep < 0)
    {
        yStep = 0;
    }

    emit yRotationChanged(yStep);

    setX(static_cast<int>(getX() + yStep));
}

void TiltMenuModel::setIsTwoZone(bool isTwoZone)
{
    if (m_isTwoZone == isTwoZone)
        return;

    m_isTwoZone = isTwoZone;
    emit isTwoZoneChanged(m_isTwoZone);
}

void TiltMenuModel::setBorderWidth(int borderWidth)
{
    if (m_borderWidth == borderWidth)
        return;

    m_borderWidth = borderWidth;
    emit borderWidthChanged(m_borderWidth);
}

void TiltMenuModel::setWidth(int width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged(m_width);
}

void TiltMenuModel::setX(int x)
{
    if (m_x == x)
        return;

    // Set this value as the center if it's the first entry
    if (m_x == 0)
    {
        m_xCenter = x;
    }

    m_x = x;
    emit xChanged(m_x);
}

void TiltMenuModel::setY(int y)
{
    if (m_y == y)
        return;

    // Set this value as the center if it's the first entry
    if (m_y == 0)
    {
        m_yCenter = y;
    }

    m_y = y;
    emit yChanged(m_y);
}

void TiltMenuModel::hasSelectedItem()
{
    if (m_tiltMenuOptionsModel)
    {
        auto selectedItem = m_tiltMenuOptionsModel->getSelectedItem();
        if (selectedItem != nullptr && selectedItem->childCount() > 0)
        {
            if (m_isTwoZone)
            {
                QLineF line(m_xCenter, m_yCenter, m_x, m_y);
                if (line.length() > m_width/2)
                {
                    if (m_y < m_yCenter)
                    {
                        selectItem(selectedItem->child(0));
                    }
                    else
                    {
                        selectItem(selectedItem->child(1));
                    }
                }
            }
            else
            {
                if ((m_y - m_borderWidth) < m_yCenter - m_width/2)
                {
                    selectItem(selectedItem->child(0));
                }
                else if (m_x > m_xCenter + m_width/2)
                {
                    selectItem(selectedItem->child(1));
                }
                else if (m_y > m_yCenter + m_width/2)
                {
                    selectItem(selectedItem->child(2));
                }
                else if ((m_x - m_borderWidth) < m_xCenter - m_width/2)
                {
                    selectItem(selectedItem->child(3));
                }
            }
        }
        else
        {
            selectItem(m_tiltMenuOptionsModel->getRootItem());
        }
    }
}

void TiltMenuModel::selectItem(TiltMenuOptionsItem* item)
{
    if (item != nullptr)
    {
        m_tiltMenuOptionsModel->selectItem(item);
        emit selectedItem(item);
    }
}

void TiltMenuModel::handleSelectedMenuOption()
{
    resetNavigation();

    // Confirm to see if the item we just selected is the last item
    auto selectedItem = m_tiltMenuOptionsModel->getSelectedItem();
    if (selectedItem != nullptr && selectedItem->childCount() == 0)
    {
        // Remove the target from the list
        m_targetList.pop_back();

        if (m_targetList.count() == 0)
        {
            // We've reached the end of the trial
            m_endTimeUtc = QDateTime::currentDateTimeUtc();
            m_tiltMenuModelParser.writeSelection();
            emit targetsRemainingChanged(m_targetList.count());
        }
        else
        {
            emit targetChanged(m_targetList.back());
            emit targetsRemainingChanged(m_targetList.count());

            m_tiltMenuModelParser.writeSelection();

            startNewMenuSearch();
        }
    }
}

void TiltMenuModel::setIntervalMs(int intervalMs)
{
    if (m_intervalMs == intervalMs)
        return;

    m_intervalMs = intervalMs;
    emit intervalChanged(m_intervalMs);
}

void TiltMenuModel::setTiltMenuOptionsModel(QObject *model)
{
    auto tiltMenuOptionsModel = qobject_cast<TiltMenuOptionsModel*>(model);
    if (m_tiltMenuOptionsModel == tiltMenuOptionsModel)
        return;

    m_tiltMenuOptionsModel = tiltMenuOptionsModel;
    emit tiltMenuOptionsModelChanged(m_tiltMenuOptionsModel);
}

void TiltMenuModel::setId(QString id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

int TiltMenuModel::getBorderWidth() const
{
    return m_borderWidth;
}

int TiltMenuModel::getWidth() const
{
    return m_width;
}

int TiltMenuModel::getX() const
{
    return m_x;
}

int TiltMenuModel::getY() const
{
    return m_y;
}

int TiltMenuModel::getIntervalMs() const
{
    return m_intervalMs;
}

QString TiltMenuModel::getTarget() const
{
    return m_targetList.count() > 0 ? m_targetList.back() : "";
}

QObject *TiltMenuModel::getTiltMenuOptionsModel() const
{
    return m_tiltMenuOptionsModel;
}

QList<double> TiltMenuModel::getXRotationList() const
{
    return m_xRotationList;
}

QList<double> TiltMenuModel::getYRotationList() const
{
    return m_yRotationList;
}

QDateTime TiltMenuModel::getStartDateTime() const
{
    return m_startTimeUtc;
}

QDateTime TiltMenuModel::getEndDateTime() const
{
    return m_endTimeUtc;
}

int TiltMenuModel::targetsRemaining() const
{
    return m_targetList.count();
}

int TiltMenuModel::getLikert() const
{
    return m_likert;
}

qint64 TiltMenuModel::getElapsedTimeMs() const
{
    return m_timer.elapsed();
}
