#ifndef ELALISTVIEW_H
#define ELALISTVIEW_H

#include <QListView>

#include "stdafx.h"
#include "Def.h"

class ElaListViewPrivate;
class ELA_EXPORT ElaListView : public QListView
{
    Q_OBJECT
    Q_Q_CREATE(ElaListView)
    Q_PROPERTY_CREATE_Q_H(int, ItemHeight)
    Q_PROPERTY_CREATE_Q_H(bool, IsTransparent)
    Q_PROPERTY_CREATE_Q_H(ElaViewType::SelectMode, SelectMode)
   public:
    explicit ElaListView(QWidget* parent = nullptr);
    ~ElaListView();
};

#endif // ELALISTVIEW_H
