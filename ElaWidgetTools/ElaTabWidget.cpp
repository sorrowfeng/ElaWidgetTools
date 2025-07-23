#include "ElaTabWidget.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QPainter>

#include "ElaTabBar.h"
#include "ElaTabWidgetPrivate.h"
ElaTabWidget::ElaTabWidget(QWidget* parent)
    : QTabWidget(parent), d_ptr(new ElaTabWidgetPrivate())
{
    Q_D(ElaTabWidget);
    d->q_ptr = this;
    _pIsTabTransparent = false;
    setObjectName("ElaTabWidget");
    setAcceptDrops(true);
    d->_tabBar = new ElaTabBar(this);
    setTabBar(d->_tabBar);
    connect(d->_tabBar, &ElaTabBar::tabBarPress, d, &ElaTabWidgetPrivate::onTabBarPress);
    d->_tabDragCreateConnection = connect(d->_tabBar, &ElaTabBar::tabDragCreate, d, &ElaTabWidgetPrivate::onTabDragCreate);
    d->_tabDragDropConnection = connect(d->_tabBar, &ElaTabBar::tabDragDrop, d, &ElaTabWidgetPrivate::onTabDragDrop);
    connect(d->_tabBar, &ElaTabBar::tabCloseRequested, d, &ElaTabWidgetPrivate::onTabCloseRequested);
}

ElaTabWidget::~ElaTabWidget()
{
}

void ElaTabWidget::setTabPosition(TabPosition position)
{
    if (position == QTabWidget::North || position == QTabWidget::South)
    {
        QTabWidget::setTabPosition(position);
    }
}

void ElaTabWidget::setTabsClosable(bool value)
{
    Q_D(const ElaTabWidget);
    if (!d->_tabBar)
        return;
    d->_tabBar->setTabsClosable(value);
}

void ElaTabWidget::setTabsDragCreated(bool enabled)
{
    Q_D(ElaTabWidget);
    if (!d->_tabBar)
        return;

    if (d->_isTabDragCreateEnabled == enabled)
        return;

    d->_isTabDragCreateEnabled = enabled;

    if (enabled)
    {
        d->_tabDragCreateConnection = connect(d->_tabBar, &ElaTabBar::tabDragCreate, d, &ElaTabWidgetPrivate::onTabDragCreate);
    }
    else
    {
        disconnect(d->_tabDragCreateConnection);
    }
}

void ElaTabWidget::setTabsDragDroped(bool enabled)
{
    Q_D(ElaTabWidget);
    if (!d->_tabBar)
        return;

    if (d->_isTabDragDropEnabled == enabled)
        return;

    d->_isTabDragDropEnabled = enabled;

    if (enabled)
    {
        d->_tabDragDropConnection = connect(d->_tabBar, &ElaTabBar::tabDragDrop, d, &ElaTabWidgetPrivate::onTabDragDrop);
    }
    else
    {
        disconnect(d->_tabDragDropConnection);
    }
}

void ElaTabWidget::paintEvent(QPaintEvent* event)
{
    if (!_pIsTabTransparent)
    {
        QTabWidget::paintEvent(event);
    }
}

void ElaTabWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->property("DragType").toString() == "ElaTabBarDrag")
    {
        event->acceptProposedAction();
    }
    QTabWidget::dragEnterEvent(event);
}

void ElaTabWidget::dropEvent(QDropEvent* event)
{
    Q_D(ElaTabWidget);
    if (event->mimeData()->property("ElaTabWidgetObject").value<ElaTabWidget*>() != this)
    {
        QMimeData* data = const_cast<QMimeData*>(event->mimeData());
        data->setProperty("TabDropIndex", count());
        d->onTabDragDrop(event->mimeData());
        event->accept();
    }
    QTabWidget::dropEvent(event);
}
