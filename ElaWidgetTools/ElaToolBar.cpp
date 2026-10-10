#include "ElaToolBar.h"

#include <QLayout>
#include <QPainter>
#include <QStyleOption>

#include "ElaIcon.h"
#include "ElaTheme.h"
#include "ElaToolBarPrivate.h"
#include "ElaToolBarStyle.h"
ElaToolBar::ElaToolBar(QWidget* parent)
    : QToolBar(parent), d_ptr(new ElaToolBarPrivate())
{
    Q_D(ElaToolBar);
    d->q_ptr = this;
    setObjectName("ElaToolBar");
    d->_toolBarStyle = new ElaToolBarStyle(style());
    setStyle(d->_toolBarStyle);
    layout()->setSpacing(10);
    layout()->setContentsMargins(3, 3, 3, 3);

    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
        if (this->isFloating())
        {
            update();
        }
    });
    setAttribute(Qt::WA_TranslucentBackground);

    connect(this, &ElaToolBar::topLevelChanged, this, [=](bool topLevel) {
        if (topLevel)
        {
            layout()->setContentsMargins(d->_shadowBorderWidth + 3, d->_shadowBorderWidth + 3, d->_shadowBorderWidth + 3, d->_shadowBorderWidth + 3);
        }
        else
        {
            layout()->setContentsMargins(3, 3, 3, 3);
        }
    });
}

ElaToolBar::ElaToolBar(const QString& title, QWidget* parent)
    : ElaToolBar(parent)
{
    setWindowTitle(title);
}

ElaToolBar::~ElaToolBar()
{
    Q_D(ElaToolBar);
    // 本控件自持样式,而应用/父级带样式表时 QWidget::setStyle 会用 QStyleSheetStyle
    // 代理包装它,并把本样式作为代理的 baseStyle 引用;~QWidget 期间的 clearFocus()
    // 仍会经由该代理访问样式对象,若在此处直接 delete 即访问已释放内存而崩溃,
    // 因此延后到事件循环、待代理释放后再销毁。
    if (d->_toolBarStyle)
    {
        d->_toolBarStyle->deleteLater();
        d->_toolBarStyle = nullptr;
    }
}

void ElaToolBar::setToolBarSpacing(int spacing)
{
    layout()->setSpacing(spacing);
}

int ElaToolBar::getToolBarSpacing() const
{
    return layout()->spacing();
}

void ElaToolBar::setToolButtonSize(const QSize& size)
{
    Q_D(ElaToolBar);
    d->_toolBarStyle->setToolButtonSize(size);
}

const QSize& ElaToolBar::getToolButtonSize() const
{
    Q_D(const ElaToolBar);
    return d->_toolBarStyle->getToolButtonSize();
}

QAction* ElaToolBar::addElaIconAction(ElaIconType::IconName icon, const QString& text)
{
    QAction* action = new QAction(text, this);
    action->setProperty("ElaIconType", QChar((unsigned short)icon));
    action->setIcon(ElaIcon::getInstance()->getElaIcon(ElaIconType::Broom, 1));
    addAction(action);
    return action;
}

QAction* ElaToolBar::addElaIconAction(ElaIconType::IconName icon, const QString& text, const QKeySequence& shortcut)
{
    QAction* action = new QAction(text, this);
    action->setShortcut(shortcut);
    action->setProperty("ElaIconType", QChar((unsigned short)icon));
    action->setIcon(ElaIcon::getInstance()->getElaIcon(ElaIconType::Broom, 1));
    addAction(action);
    return action;
}

void ElaToolBar::paintEvent(QPaintEvent* event)
{
    Q_D(ElaToolBar);
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing);
    if (isFloating())
    {
        // 高性能阴影
        eTheme->drawEffectShadow(&painter, rect(), d->_shadowBorderWidth, 6);
        //背景
        painter.setPen(ElaThemeColor(d->_themeMode, PopupBorder));
        painter.setBrush(ElaThemeColor(d->_themeMode, DialogBase));
        QRect foregroundRect(d->_shadowBorderWidth, d->_shadowBorderWidth, width() - 2 * d->_shadowBorderWidth, height() - 2 * d->_shadowBorderWidth);
        painter.drawRoundedRect(foregroundRect, 5, 5);
        QStyle* style = this->style();
        QStyleOptionToolBar opt;
        initStyleOption(&opt);
        opt.rect = style->subElementRect(QStyle::SE_ToolBarHandle, &opt, this);
        if (opt.rect.isValid())
        {
            style->drawPrimitive(QStyle::PE_IndicatorToolBarHandle, &opt, &painter, this);
        }
    }
    else
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::transparent);
        painter.drawRoundedRect(rect(), 5, 5);
        QToolBar::paintEvent(event);
    }
    painter.restore();
}
