#include "ElaMenu.h"

#include <QApplication>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QVBoxLayout>

#include "ElaMenuStyle.h"
#include "private/ElaMenuPrivate.h"
ElaMenu::ElaMenu(QWidget* parent)
    : QMenu(parent), d_ptr(new ElaMenuPrivate())
{
    Q_D(ElaMenu);
    d->q_ptr = this;
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("ElaMenu");
    d->_menuStyle = new ElaMenuStyle(style());
    setStyle(d->_menuStyle);
    d->_pAnimationImagePosY = 0;
}

ElaMenu::ElaMenu(const QString& title, QWidget* parent)
    : ElaMenu(parent)
{
    setTitle(title);
}

ElaMenu::~ElaMenu()
{
    Q_D(ElaMenu);
    delete d->_menuStyle;
}

void ElaMenu::setMenuItemHeight(int menuItemHeight)
{
    Q_D(ElaMenu);
    d->_menuStyle->setMenuItemHeight(menuItemHeight);
}

int ElaMenu::getMenuItemHeight() const
{
    Q_D(const ElaMenu);
    return d->_menuStyle->getMenuItemHeight();
}

QAction* ElaMenu::addMenu(QMenu* menu)
{
    return QMenu::addMenu(menu);
}

ElaMenu* ElaMenu::addMenu(const QString& title)
{
    ElaMenu* menu = new ElaMenu(title, this);
    QMenu::addAction(menu->menuAction());
    return menu;
}

ElaMenu* ElaMenu::addMenu(const QIcon& icon, const QString& title)
{
    ElaMenu* menu = new ElaMenu(title, this);
    menu->setIcon(icon);
    QMenu::addAction(menu->menuAction());
    return menu;
}

ElaMenu* ElaMenu::addMenu(ElaIconType::IconName icon, const QString& title)
{
    ElaMenu* menu = new ElaMenu(title, this);
    QMenu::addAction(menu->menuAction());
    menu->menuAction()->setProperty("ElaIconType", QChar((unsigned short)icon));
    return menu;
}

QAction* ElaMenu::addElaIconAction(ElaIconType::IconName icon, const QString& text)
{
    QAction* action = new QAction(text, this);
    action->setProperty("ElaIconType", QChar((unsigned short)icon));
    QMenu::addAction(action);
    return action;
}

QAction* ElaMenu::addElaIconAction(ElaIconType::IconName icon, const QString& text, const QKeySequence& shortcut)
{
    QAction* action = new QAction(text, this);
    action->setShortcut(shortcut);
    action->setProperty("ElaIconType", QChar((unsigned short)icon));
    QMenu::addAction(action);
    return action;
}

bool ElaMenu::isHasChildMenu() const
{
    QList<QAction*> actionList = this->actions();
    for (auto action: actionList)
    {
        if (action->isSeparator())
        {
            continue;
        }
        if (action->menu())
        {
            return true;
        }
    }
    return false;
}

bool ElaMenu::isHasIcon() const
{
    QList<QAction*> actionList = this->actions();
    for (auto action: actionList)
    {
        if (action->isSeparator())
        {
            continue;
        }
        QMenu* menu = action->menu();
        if (menu && (!menu->icon().isNull() || !menu->property("ElaIconType").toString().isEmpty()))
        {
            return true;
        }
        if (!action->icon().isNull() || !action->property("ElaIconType").toString().isEmpty())
        {
            return true;
        }
    }
    return false;
}

void ElaMenu::showEvent(QShowEvent* event)
{
    Q_EMIT menuShow();
    Q_D(ElaMenu);
#ifdef Q_OS_MACOS
    // macOS:Qt::Popup 窗口通常不支持 windowOpacity,淡入看不到效果;
    // 改为弹出时从下方轻微上滑(动画窗口位置),保证有可见的弹出动画。
    d->_animationPix = QPixmap();
    QMenu::showEvent(event);
    const QPoint finalPos = pos();
    const int offsetY = 10;
    move(finalPos.x(), finalPos.y() + offsetY);
    QPropertyAnimation* slideAnimation = new QPropertyAnimation(this, "pos");
    slideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    slideAnimation->setDuration(150);
    slideAnimation->setStartValue(QPoint(finalPos.x(), finalPos.y() + offsetY));
    slideAnimation->setEndValue(finalPos);
    slideAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    return;
#endif
    //消除阴影偏移
    move(this->pos().x() - 6, this->pos().y());
    updateGeometry();
    if (!d->_animationPix.isNull())
    {
        d->_animationPix = QPixmap();
    }
    d->_animationPix = this->grab(this->rect());
    QPropertyAnimation* posAnimation = new QPropertyAnimation(d, "pAnimationImagePosY");
    connect(posAnimation, &QPropertyAnimation::finished, this, [=]() {
        d->_animationPix = QPixmap();
        update();
    });
    connect(posAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        update();
    });
    posAnimation->setEasingCurve(QEasingCurve::OutCubic);
    posAnimation->setDuration(400);
    int targetPosY = height();
    if (targetPosY > 160)
    {
        if (targetPosY < 320)
        {
            targetPosY = 160;
        }
        else
        {
            targetPosY /= 2;
        }
    }

    if (pos().y() + d->_menuStyle->getMenuItemHeight() + 9 >= QCursor::pos().y())
    {
        posAnimation->setStartValue(-targetPosY);
    }
    else
    {
        posAnimation->setStartValue(targetPosY);
    }

    posAnimation->setEndValue(0);
    posAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    QMenu::showEvent(event);
}

void ElaMenu::paintEvent(QPaintEvent* event)
{
    Q_D(ElaMenu);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    if (!d->_animationPix.isNull())
    {
#ifdef Q_OS_MACOS
        // 动画期间只画了滑动的抓帧图,空隙会透出后面的窗口(表现为大片空白)。
        // 先铺满菜单背景,再绘制抓帧图。
        QStyleOption opt;
        opt.initFrom(this);
        style()->drawPrimitive(QStyle::PE_PanelMenu, &opt, &painter, this);
#endif
        painter.drawPixmap(QRect(0, d->_pAnimationImagePosY, width(), height()), d->_animationPix);
    }
    else
    {
        QMenu::paintEvent(event);
    }
}
