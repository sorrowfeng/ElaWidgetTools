#include "ElaTreeView.h"

#include "ElaScrollBar.h"
#include "ElaTreeViewPrivate.h"
#include "ElaTreeViewStyle.h"
ElaTreeView::ElaTreeView(QWidget* parent)
    : QTreeView(parent), d_ptr(new ElaTreeViewPrivate())
{
    Q_D(ElaTreeView);
    d->q_ptr = this;
    setObjectName("ElaTreeView");
    setStyleSheet(
        "#ElaTreeView{background-color:transparent;}"
        "QHeaderView{background-color:transparent;border:0px;}");

    setAnimated(true);
    setMouseTracking(true);

    ElaScrollBar* hScrollBar = new ElaScrollBar(this);
    hScrollBar->setIsAnimation(true);
    connect(hScrollBar, &ElaScrollBar::rangeAnimationFinished, this, [=]() {
        doItemsLayout();
    });
    setHorizontalScrollBar(hScrollBar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ElaScrollBar* vScrollBar = new ElaScrollBar(this);
    vScrollBar->setIsAnimation(true);
    connect(vScrollBar, &ElaScrollBar::rangeAnimationFinished, this, [=]() {
        doItemsLayout();
    });
    setVerticalScrollBar(vScrollBar);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    d->_treeViewStyle = new ElaTreeViewStyle(style());
    setStyle(d->_treeViewStyle);
}

ElaTreeView::~ElaTreeView()
{
    Q_D(ElaTreeView);
    // 本控件自持样式,而应用/父级带样式表时 QWidget::setStyle 会用 QStyleSheetStyle
    // 代理包装它,并把本样式作为代理的 baseStyle 引用;~QWidget 期间的 clearFocus()
    // 仍会经由该代理访问样式对象,若在此处直接 delete 即访问已释放内存而崩溃,
    // 因此延后到事件循环、待代理释放后再销毁。
    if (d->_treeViewStyle)
    {
        d->_treeViewStyle->deleteLater();
        d->_treeViewStyle = nullptr;
    }
}

void ElaTreeView::setItemHeight(int itemHeight)
{
    Q_D(ElaTreeView);
    if (itemHeight > 0)
    {
        d->_treeViewStyle->setItemHeight(itemHeight);
        doItemsLayout();
    }
}

int ElaTreeView::getItemHeight() const
{
    Q_D(const ElaTreeView);
    return d->_treeViewStyle->getItemHeight();
}

void ElaTreeView::setHeaderMargin(int headerMargin)
{
    Q_D(ElaTreeView);
    if (headerMargin >= 0)
    {
        d->_treeViewStyle->setHeaderMargin(headerMargin);
        doItemsLayout();
    }
}

int ElaTreeView::getHeaderMargin() const
{
    Q_D(const ElaTreeView);
    return d->_treeViewStyle->getHeaderMargin();
}