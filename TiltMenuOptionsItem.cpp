#include "TiltMenuOptionsItem.h"
#include <QStringList>

TiltMenuOptionsItem::TiltMenuOptionsItem(const QVariant &data, TiltMenuOptionsItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

TiltMenuOptionsItem::~TiltMenuOptionsItem()
{
    qDeleteAll(m_childItems);
}

void TiltMenuOptionsItem::appendChild(TiltMenuOptionsItem *item)
{
    m_childItems.append(item);
}

TiltMenuOptionsItem *TiltMenuOptionsItem::child(int row)
{
    return m_childItems.value(row);
}

int TiltMenuOptionsItem::childCount() const
{
    return m_childItems.count();
}

QVariant TiltMenuOptionsItem::data() const
{
    return m_itemData;
}

TiltMenuOptionsItem *TiltMenuOptionsItem::parentItem()
{
    return m_parentItem;
}

int TiltMenuOptionsItem::row() const
{
    return m_parentItem ? m_parentItem->m_childItems.indexOf(const_cast<TiltMenuOptionsItem*>(this)) : 0;
}
