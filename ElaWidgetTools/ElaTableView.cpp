#include "ElaTableView.h"

#include <QHeaderView>
#include <QMouseEvent>

#include "ElaTableViewStyle.h"
#include "ElaScrollBar.h"
#include "ElaTableViewPrivate.h"
ElaTableView::ElaTableView(QWidget* parent)
    : QTableView(parent), d_ptr(new ElaTableViewPrivate())
{
    Q_D(ElaTableView);
    d->q_ptr = this;
    setMouseTracking(true);
    setObjectName("ElaTableView");
    setStyleSheet(
        "QTableView{background-color:transparent;}"
        "QHeaderView{background-color:transparent;border:0px;}");
    setShowGrid(false);
    setVerticalScrollBar(new ElaScrollBar(this));
    setHorizontalScrollBar(new ElaScrollBar(this));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    d->_tableViewStyle = new ElaTableViewStyle(style());
    setStyle(d->_tableViewStyle);
}

ElaTableView::~ElaTableView()
{
    Q_D(ElaTableView);
    // 本控件自持样式,而应用/父级带样式表时 QWidget::setStyle 会用 QStyleSheetStyle
    // 代理包装它,并把本样式作为代理的 baseStyle 引用;~QWidget 期间的 clearFocus()
    // 仍会经由该代理访问样式对象,若在此处直接 delete 即访问已释放内存而崩溃,
    // 因此延后到事件循环、待代理释放后再销毁。
    if (d->_tableViewStyle)
    {
        d->_tableViewStyle->deleteLater();
        d->_tableViewStyle = nullptr;
    }
}

void ElaTableView::setHeaderMargin(int headerMargin)
{
    Q_D(ElaTableView);
    if (headerMargin >= 0)
    {
        d->_tableViewStyle->setHeaderMargin(headerMargin);
        doItemsLayout();
    }
}

int ElaTableView::getHeaderMargin() const
{
    Q_D(const ElaTableView);
    return d->_tableViewStyle->getHeaderMargin();
}

void ElaTableView::setSelectMode(ElaViewType::SelectMode mode) 
{
    Q_D(ElaTableView);
    d->_tableViewStyle->setSelectMode(mode);
}

ElaViewType::SelectMode ElaTableView::getSelectMode() const
{
    Q_D(const ElaTableView);
    return d->_tableViewStyle->getSelectMode();
}

void ElaTableView::showEvent(QShowEvent* event)
{
    Q_EMIT tableViewShow();
    QTableView::showEvent(event);
}

void ElaTableView::hideEvent(QHideEvent* event)
{
    Q_EMIT tableViewHide();
    QTableView::hideEvent(event);
}

void ElaTableView::mouseMoveEvent(QMouseEvent* event)
{
    Q_D(ElaTableView);
    if (selectionBehavior() == QAbstractItemView::SelectRows)
    {
        d->_tableViewStyle->setCurrentHoverRow(indexAt(event->pos()).row());
        update();
    }
    QTableView::mouseMoveEvent(event);
}

void ElaTableView::leaveEvent(QEvent* event)
{
    Q_D(ElaTableView);
    if (selectionBehavior() == QAbstractItemView::SelectRows)
    {
        d->_tableViewStyle->setCurrentHoverRow(-1);
        update();
    }
    QTableView::leaveEvent(event);
}
