#ifndef TILTMENUOPTIONSITEM_H
#define TILTMENUOPTIONSITEM_H

#include <QObject>
#include <QVariant>

class TiltMenuOptionsItem
{
public:
    explicit TiltMenuOptionsItem(const QVariant &data, TiltMenuOptionsItem *parentItem = 0);
    virtual ~TiltMenuOptionsItem();

    void appendChild(TiltMenuOptionsItem *child);

    TiltMenuOptionsItem *child(int row);
    int childCount() const;
    QVariant data() const;
    int row() const;
    TiltMenuOptionsItem *parentItem();

private:
    TiltMenuOptionsItem *m_parentItem;
    QList<TiltMenuOptionsItem*> m_childItems;
    QVariant m_itemData;
};

#endif // TILTMENUOPTIONSITEM_H
