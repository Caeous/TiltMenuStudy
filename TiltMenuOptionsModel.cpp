#include "TiltMenuOptionsModel.h"
#include "TiltMenuOptionsItem.h"
#include <QStringList>

TiltMenuOptionsModel::TiltMenuOptionsModel(QObject *parent)
{
}

TiltMenuOptionsModel::~TiltMenuOptionsModel()
{
    delete m_rootItem;
}

void TiltMenuOptionsModel::populateTargetList(bool isTwoZone)
{
    if (m_rootItem)
    {
        delete m_rootItem;
    }

    m_rootItem = new TiltMenuOptionsItem(QString(""));

    if (isTwoZone)
    {
        auto actionsItem = new TiltMenuOptionsItem(QString("Actions"));
        m_rootItem->appendChild(actionsItem);

        auto sendItem = new TiltMenuOptionsItem(QString("Send"));
        actionsItem->appendChild(sendItem);
        {
            auto statsItem = new TiltMenuOptionsItem(QString("Stats"));
            sendItem->appendChild(statsItem);
            {
                auto locationItem = new TiltMenuOptionsItem(QString("Location"));
                auto pulseItem = new TiltMenuOptionsItem(QString("Pulse"));
                statsItem->appendChild(locationItem);
                statsItem->appendChild(pulseItem);
            }

            auto communicationItem = new TiltMenuOptionsItem(QString("Communication"));
            sendItem->appendChild(communicationItem);
            {
                auto waveItem = new TiltMenuOptionsItem(QString("Wave"));
                auto textItem = new TiltMenuOptionsItem(QString("Text"));
                communicationItem->appendChild(waveItem);
                communicationItem->appendChild(textItem);
            }
        }

        auto settingsItem = new TiltMenuOptionsItem(QString("Settings"));
        actionsItem->appendChild(settingsItem);
        {
            auto systemsItem = new TiltMenuOptionsItem(QString("Systems"));
            settingsItem->appendChild(systemsItem);
            {
                auto bluetoothItem = new TiltMenuOptionsItem(QString("Bluetooth"));
                auto gpsItem = new TiltMenuOptionsItem(QString("GPS"));
                systemsItem->appendChild(bluetoothItem);
                systemsItem->appendChild(gpsItem);
            }

            auto modesItem = new TiltMenuOptionsItem(QString("Modes"));
            settingsItem->appendChild(modesItem);
            {
                auto doNotDisturbItem = new TiltMenuOptionsItem(QString("Do not disturb"));
                auto sleepItem = new TiltMenuOptionsItem(QString("Sleep"));
                modesItem->appendChild(doNotDisturbItem);
                modesItem->appendChild(sleepItem);
            }
        }

        auto infoItem = new TiltMenuOptionsItem(QString("Info"));
        m_rootItem->appendChild(infoItem);

        auto calendarItem = new TiltMenuOptionsItem(QString("Calendar"));
        infoItem->appendChild(calendarItem);
        {
            auto viewItem = new TiltMenuOptionsItem(QString("View"));
            calendarItem->appendChild(viewItem);
            {
                auto todayItem = new TiltMenuOptionsItem(QString("Today"));
                auto tomorrowItem = new TiltMenuOptionsItem(QString("Tomorrow"));
                viewItem->appendChild(todayItem);
                viewItem->appendChild(tomorrowItem);
            }

            auto changeItem = new TiltMenuOptionsItem(QString("Change"));
            calendarItem->appendChild(changeItem);
            {
                auto addEventItem = new TiltMenuOptionsItem(QString("Add Event"));
                auto cancelEventItem = new TiltMenuOptionsItem(QString("Cancel Event"));
                changeItem->appendChild(addEventItem);
                changeItem->appendChild(cancelEventItem);
            }
        }

        auto healthItem = new TiltMenuOptionsItem(QString("Health"));
        infoItem->appendChild(healthItem);
        {
            auto systemsItem = new TiltMenuOptionsItem(QString("Cardiac"));
            healthItem->appendChild(systemsItem);
            {
                auto bluetoothItem = new TiltMenuOptionsItem(QString("Pulse"));
                auto gpsItem = new TiltMenuOptionsItem(QString("O2"));
                systemsItem->appendChild(bluetoothItem);
                systemsItem->appendChild(gpsItem);
            }

            auto energyItem = new TiltMenuOptionsItem(QString("Energy"));
            healthItem->appendChild(energyItem);
            {
                auto caloriesItem = new TiltMenuOptionsItem(QString("Calories"));
                auto stepsItem = new TiltMenuOptionsItem(QString("Steps"));
                energyItem->appendChild(caloriesItem);
                energyItem->appendChild(stepsItem);
            }
        }
    }
    else
    {
        auto sendItem = new TiltMenuOptionsItem(QString("Send"));
        m_rootItem->appendChild(sendItem);
        {
            auto locationItem = new TiltMenuOptionsItem(QString("Location"));
            auto pulseItem = new TiltMenuOptionsItem(QString("Pulse"));
            sendItem->appendChild(locationItem);
            sendItem->appendChild(pulseItem);

            auto waveItem = new TiltMenuOptionsItem(QString("Wave"));
            auto textItem = new TiltMenuOptionsItem(QString("Text"));
            sendItem->appendChild(waveItem);
            sendItem->appendChild(textItem);
        }

        auto settingsItem = new TiltMenuOptionsItem(QString("Settings"));
        m_rootItem->appendChild(settingsItem);
        {
            auto bluetoothItem = new TiltMenuOptionsItem(QString("Bluetooth"));
            auto gpsItem = new TiltMenuOptionsItem(QString("GPS"));
            settingsItem->appendChild(bluetoothItem);
            settingsItem->appendChild(gpsItem);

            auto doNotDisturbItem = new TiltMenuOptionsItem(QString("Do not disturb"));
            auto sleepItem = new TiltMenuOptionsItem(QString("Sleep"));
            settingsItem->appendChild(doNotDisturbItem);
            settingsItem->appendChild(sleepItem);
        }

        auto calendarItem = new TiltMenuOptionsItem(QString("Calendar"));
        m_rootItem->appendChild(calendarItem);
        {
            auto todayItem = new TiltMenuOptionsItem(QString("Today"));
            auto tomorrowItem = new TiltMenuOptionsItem(QString("Tomorrow"));
            calendarItem->appendChild(todayItem);
            calendarItem->appendChild(tomorrowItem);

            auto addEventItem = new TiltMenuOptionsItem(QString("Add Event"));
            auto cancelEventItem = new TiltMenuOptionsItem(QString("Cancel Event"));
            calendarItem->appendChild(addEventItem);
            calendarItem->appendChild(cancelEventItem);
        }

        auto healthItem = new TiltMenuOptionsItem(QString("Health"));
        m_rootItem->appendChild(healthItem);
        {
            auto bluetoothItem = new TiltMenuOptionsItem(QString("Pulse"));
            auto gpsItem = new TiltMenuOptionsItem(QString("O2"));
            healthItem->appendChild(bluetoothItem);
            healthItem->appendChild(gpsItem);

            auto caloriesItem = new TiltMenuOptionsItem(QString("Calories"));
            auto stepsItem = new TiltMenuOptionsItem(QString("Steps"));
            healthItem->appendChild(caloriesItem);
            healthItem->appendChild(stepsItem);
        }
    }

    selectItem(m_rootItem);
}

TiltMenuOptionsItem *TiltMenuOptionsModel::getRootItem() const
{
    return m_rootItem;
}

TiltMenuOptionsItem *TiltMenuOptionsModel::getSelectedItem() const
{
    return m_selectedItem;
}

void TiltMenuOptionsModel::selectItem(TiltMenuOptionsItem *item)
{
    if (item != nullptr)
    {
        m_selectedItem = item;

        auto count = item->childCount();
        if (count > 0)
        {
            setTextA(item->child(0)->data().toString());
        }
        if (count > 1)
        {
            setTextB(item->child(1)->data().toString());
        }
        if (count > 2)
        {
            setTextC(item->child(2)->data().toString());
        }
        if (count > 3)
        {
            setTextD(item->child(3)->data().toString());
        }
    }
}

QString TiltMenuOptionsModel::getTextA() const
{
    return m_textA;
}

QString TiltMenuOptionsModel::getTextB() const
{
    return m_textB;
}

QString TiltMenuOptionsModel::getTextC() const
{
    return m_textC;
}

QString TiltMenuOptionsModel::getTextD() const
{
    return m_textD;
}

void TiltMenuOptionsModel::setTextA(QString textA)
{
    if (m_textA == textA)
        return;

    m_textA = textA;
    emit textAChanged(m_textA);
}

void TiltMenuOptionsModel::setTextB(QString textB)
{
    if (m_textB == textB)
        return;

    m_textB = textB;
    emit textBChanged(m_textB);
}

void TiltMenuOptionsModel::setTextC(QString textC)
{
    if (m_textC == textC)
        return;

    m_textC = textC;
    emit textCChanged(m_textC);
}

void TiltMenuOptionsModel::setTextD(QString textD)
{
    if (m_textD == textD)
        return;

    m_textD = textD;
    emit textDChanged(m_textD);
}

