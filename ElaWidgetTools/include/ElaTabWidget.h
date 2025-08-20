#ifndef ELATABWIDGET_H
#define ELATABWIDGET_H

#include <QTabWidget>

#include "stdafx.h"

class ElaTabBar;
class ElaTabWidgetPrivate;
class ELA_EXPORT ElaTabWidget : public QTabWidget
{
    Q_OBJECT
    Q_Q_CREATE(ElaTabWidget)
    Q_PROPERTY_CREATE(bool, IsTabTransparent);

  public:
    explicit ElaTabWidget(QWidget* parent = nullptr);
    ~ElaTabWidget();
    void setTabPosition(TabPosition position);
    void setTabsClosable(bool value);
    void setTabsDragCreated(bool enabled);
    void setTabsDragDroped(bool enabled);
    void setTabsWidth(int width);
    void setTabsHeight(int height);

  protected:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;
};

#endif// ELATABWIDGET_H
