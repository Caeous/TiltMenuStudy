#ifndef TILTMODEL_H
#define TILTMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QDateTime>
#include <QElapsedTimer>
#include "TiltMenuOptionsModel.h"
#include "TiltMenuModelParser.h"

class TiltMenuModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString participantId READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int width READ getWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    Q_PROPERTY(bool isTwoZone READ isTwoZone WRITE setIsTwoZone NOTIFY isTwoZoneChanged)
    Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int intervalMs READ getIntervalMs WRITE setIntervalMs NOTIFY intervalChanged)
    Q_PROPERTY(int targetsRemaining READ targetsRemaining NOTIFY targetsRemainingChanged)
    Q_PROPERTY(QString targetMenuOption READ getTarget NOTIFY targetChanged)
    Q_PROPERTY(QObject* tiltMenuOptionsModel READ getTiltMenuOptionsModel WRITE setTiltMenuOptionsModel NOTIFY tiltMenuOptionsModelChanged)
    Q_PROPERTY(int likert READ getLikert WRITE setLikert NOTIFY likertChanged)

public:
    explicit TiltMenuModel(QObject *parent = nullptr);

    QString getId() const;
    bool isTwoZone() const;
    int getBorderWidth() const;
    int getWidth() const;
    int getX() const;
    int getY() const;
    int getIntervalMs() const;
    QString getTarget() const;
    QObject* getTiltMenuOptionsModel() const;
    QList<double> getXRotationList() const;
    QList<double> getYRotationList() const;
    QDateTime getStartDateTime() const;
    QDateTime getEndDateTime() const;
    int targetsRemaining() const;
    int getLikert() const;
    qint64 getElapsedTimeMs() const;

signals:
    void idChanged(QString id);
    void isTwoZoneChanged(bool isTwoZone);
    void borderWidthChanged(int borderWidth);
    void widthChanged(int width);
    void xChanged(int x);
    void yChanged(int y);
    void xRotationChanged(int xRotation);
    void yRotationChanged(int yRotation);
    void intervalChanged(int interval);
    void targetChanged(QString target);
    void tiltMenuOptionsModelChanged(QObject* tiltMenuOptionsModel);
    void selectedItem(TiltMenuOptionsItem* item);
    void targetsRemainingChanged(int targetsRemaining);
    void likertChanged(int likert);

public slots:
    void resetNavigation();
    void endTrial();
    void startNewTrial();
    void startNewMenuSearch();
    void setId(QString id);
    void setXRotation(double xRotation);
    void setYRotation(double yRotation);
    void setLikert(int likert);
    void setIsTwoZone(bool isTwoZone);

private slots:
    void setBorderWidth(int borderWidth);
    void setWidth(int width);
    void setX(int x);
    void setY(int y);
    void setIntervalMs(int intervalMs);
    void setTiltMenuOptionsModel(QObject* model);
    void selectItem(TiltMenuOptionsItem* item);
    void hasSelectedItem();
    void handleSelectedMenuOption();

private:
    void populateTargetList();

private:
    QString m_id;
    bool m_isTwoZone = false;
    int m_borderWidth = 20;
    int m_width = 300;
    int m_intervalMs = 50;

    QDateTime m_startTimeUtc;
    QDateTime m_endTimeUtc;
    QElapsedTimer m_timer;

    QList<double> m_yRotationList;
    QList<double> m_xRotationList;
    int m_x = 0;
    int m_y = 0;
    int m_xCenter = 0;
    int m_yCenter = 0;
    double m_distanceToCenter = 0.0;
    TiltMenuOptionsModel* m_tiltMenuOptionsModel = nullptr;
    TiltMenuModelParser m_tiltMenuModelParser;
    QList<QString> m_targetList;
    int m_likert = 0;
};

#endif // TILTMODEL_H
