#include "ElaListView.h"

#include <QMouseEvent>

#include "ElaListViewPrivate.h"
#include "ElaListViewStyle.h"
#include "ElaScrollBar.h"
ElaListView::ElaListView(QWidget* parent)
    : QListView(parent), d_ptr(new ElaListViewPrivate())
{
    Q_D(ElaListView);
    d->q_ptr = this;
    setObjectName("ElaListView");
    setStyleSheet("#ElaListView{background-color:transparent;}");
    d->_listViewStyle = new ElaListViewStyle(style());
    setStyle(d->_listViewStyle);
    setMouseTracking(true);
    setVerticalScrollBar(new ElaScrollBar(this));
    setHorizontalScrollBar(new ElaScrollBar(this));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

ElaListView::~ElaListView()
{
    Q_D(ElaListView);
    // 本控件自持样式,而应用/父级带样式表时 QWidget::setStyle 会用 QStyleSheetStyle
    // 代理包装它,并把本样式作为代理的 baseStyle 引用;~QWidget 期间的 clearFocus()
    // 仍会经由该代理访问样式对象,若在此处直接 delete 即访问已释放内存而崩溃,
    // 因此延后到事件循环、待代理释放后再销毁。
    if (d->_listViewStyle)
    {
        d->_listViewStyle->deleteLater();
        d->_listViewStyle = nullptr;
    }
}

void ElaListView::setItemHeight(int itemHeight)
{
    Q_D(ElaListView);
    if (itemHeight > 0)
    {
        d->_listViewStyle->setItemHeight(itemHeight);
        doItemsLayout();
    }
}

int ElaListView::getItemHeight() const
{
    Q_D(const ElaListView);
    return d->_listViewStyle->getItemHeight();
}

void ElaListView::setIsTransparent(bool isTransparent)
{
    Q_D(ElaListView);
    d->_listViewStyle->setIsTransparent(isTransparent);
    update();
}

bool ElaListView::getIsTransparent() const
{
    Q_D(const ElaListView);
    return d->_listViewStyle->getIsTransparent();
}

void ElaListView::setSelectMode(ElaViewType::SelectMode mode) 
{
    Q_D(ElaListView);
    d->_listViewStyle->setSelectMode(mode);
}

ElaViewType::SelectMode ElaListView::getSelectMode() const
{
    Q_D(const ElaListView);
    return d->_listViewStyle->getSelectMode();
}