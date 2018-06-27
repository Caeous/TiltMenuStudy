#ifndef TILTMENUOPTIONSMODEL_H
#define TILTMENUOPTIONSMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TiltMenuOptionsItem;

class TiltMenuOptionsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString textA READ getTextA WRITE setTextA NOTIFY textAChanged)
    Q_PROPERTY(QString textB READ getTextB WRITE setTextB NOTIFY textBChanged)
    Q_PROPERTY(QString textC READ getTextC WRITE setTextC NOTIFY textCChanged)
    Q_PROPERTY(QString textD READ getTextD WRITE setTextD NOTIFY textDChanged)

public:
    explicit TiltMenuOptionsModel(QObject *parent = 0);
    ~TiltMenuOptionsModel();

    TiltMenuOptionsItem* getRootItem() const;
    TiltMenuOptionsItem* getSelectedItem() const;
    void selectItem(TiltMenuOptionsItem*);
    void populateTargetList(bool isTwoZone);

    QString getTextA() const;
    QString getTextB() const;
    QString getTextC() const;
    QString getTextD() const;

signals:
    void textAChanged(QString textA);
    void textBChanged(QString textB);
    void textCChanged(QString textC);
    void textDChanged(QString textD);

public slots:
    void setTextA(QString textA);
    void setTextB(QString textB);
    void setTextC(QString textC);
    void setTextD(QString textD);

private:
    TiltMenuOptionsItem *m_rootItem = nullptr;
    TiltMenuOptionsItem *m_selectedItem = nullptr;

    QString m_textA;
    QString m_textB;
    QString m_textC;
    QString m_textD;
};
#endif // TILTMENUOPTIONSMODEL_H
