#include "ElaProgressBar.h"

#include <QPropertyAnimation>
#include <QStyleOption>

#include "ElaProgressBarPrivate.h"
#include "ElaProgressBarStyle.h"
ElaProgressBar::ElaProgressBar(QWidget* parent)
    : QProgressBar(parent), d_ptr(new ElaProgressBarPrivate())
{
    Q_D(ElaProgressBar);
    setObjectName("ElaProgressBar");
    setStyleSheet("#ElaProgressBar{background-color:transparent;}");
    d->q_ptr = this;
    d->_style = new ElaProgressBarStyle(style());
    setStyle(d->_style);
    d->_busyAnimation = new QPropertyAnimation(d->_style, "busyStartValue");
    connect(d->_busyAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        d->_style->setProperty("busyEndValue", value.toInt() + 75);
        update();
    });
    d->_busyAnimation->setDuration(2000);
    d->_busyAnimation->setLoopCount(-1);
}

ElaProgressBar::~ElaProgressBar()
{
    Q_D(ElaProgressBar);
    // 本控件自持样式,而应用/父级带样式表时 QWidget::setStyle 会用 QStyleSheetStyle
    // 代理包装它,并把本样式作为代理的 baseStyle 引用;~QWidget 期间的 clearFocus()
    // 仍会经由该代理访问样式对象,若在此处直接 delete 即访问已释放内存而崩溃,
    // 因此延后到事件循环、待代理释放后再销毁。
    if (d->_style)
    {
        d->_style->deleteLater();
        d->_style = nullptr;
    }
}

void ElaProgressBar::setMinimum(int minimum)
{
    Q_D(ElaProgressBar);
    if (d->_isBusyAnimation && !(maximum() == 0 && minimum == 0))
    {
        d->_isBusyAnimation = false;
        d->_busyAnimation->stop();
    }
    QProgressBar::setMinimum(minimum);
}

void ElaProgressBar::setMaximum(int maximum)
{
    Q_D(ElaProgressBar);
    if (d->_isBusyAnimation && !(minimum() == 0 && maximum == 0))
    {
        d->_isBusyAnimation = false;
        d->_busyAnimation->stop();
    }
    QProgressBar::setMaximum(maximum);
}

void ElaProgressBar::paintEvent(QPaintEvent* event)
{
    Q_D(ElaProgressBar);
    if (!d->_isBusyAnimation && minimum() == 0 && maximum() == 0)
    {
        QStyleOptionProgressBar option;
        option.initFrom(this);
        d->_isBusyAnimation = true;
        d->_busyAnimation->setStartValue(-75);
        if (orientation() == Qt::Horizontal)
        {
            d->_busyAnimation->setEndValue(this->width());
        }
        else
        {
            d->_busyAnimation->setEndValue(this->height());
        }
        d->_busyAnimation->start();
    }
    QProgressBar::paintEvent(event);
}

void ElaProgressBar::resizeEvent(QResizeEvent* event)
{
    Q_D(ElaProgressBar);
    if (orientation() == Qt::Horizontal)
    {
        d->_busyAnimation->setEndValue(this->width());
    }
    else
    {
        d->_busyAnimation->setEndValue(this->height());
    }
    QProgressBar::resizeEvent(event);
}
