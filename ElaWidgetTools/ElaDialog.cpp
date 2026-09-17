#include "ElaDialog.h"

#include "ElaApplication.h"
#include "ElaTheme.h"
#include "private/ElaDialogPrivate.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QRegion>
#include <QResizeEvent>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>
Q_TAKEOVER_NATIVEEVENT_CPP(ElaDialog, d_func()->_appBar);
ElaDialog::ElaDialog(QWidget* parent)
    : QDialog{parent}, d_ptr(new ElaDialogPrivate())
{
    Q_D(ElaDialog);
    d->q_ptr = this;
    resize(500, 500); // 默认宽高
    setWindowTitle("ElaDialog");
    setObjectName("ElaDialog");
#ifndef Q_OS_WIN
    setAttribute(Qt::WA_Hover);
#endif
#if (QT_VERSION < QT_VERSION_CHECK(6, 5, 3) || QT_VERSION > QT_VERSION_CHECK(6, 6, 1))
    setStyleSheet("#ElaDialog{background-color:transparent;}");
#endif
    // 自定义AppBar
    d->_appBar = new ElaAppBar(this);
    d->_appBar->setIsStayTop(true);
    d->_appBar->setWindowButtonFlags(ElaAppBarType::StayTopButtonHint | ElaAppBarType::MinimizeButtonHint | ElaAppBarType::MaximizeButtonHint | ElaAppBarType::CloseButtonHint);
    connect(d->_appBar, &ElaAppBar::routeBackButtonClicked, this, &ElaDialog::routeBackButtonClicked);
    connect(d->_appBar, &ElaAppBar::navigationButtonClicked, this, &ElaDialog::navigationButtonClicked);
    connect(d->_appBar, &ElaAppBar::themeChangeButtonClicked, this, &ElaDialog::themeChangeButtonClicked);
    connect(d->_appBar, &ElaAppBar::closeButtonClicked, this, &ElaDialog::closeButtonClicked);
#ifdef Q_OS_MACOS
    // macOS:该弹窗使用自绘圆角无边框(见 paintEvent/resizeEvent),
    // 不采用系统原生标题栏。
    d->_appBar->setUseNativeTitleBar(false);
    setAttribute(Qt::WA_TranslucentBackground);
#endif

    // 创建主容器，用户可以在其中设置自己的布局
    d->_mainContainer = new QWidget(this);
    d->_mainContainer->setObjectName("ElaDialogMainContainer");
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(d->_mainContainer);

    // 主题
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
        update();
    });

    d->_windowDisplayMode = eApp->getWindowDisplayMode();
    connect(eApp, &ElaApplication::pWindowDisplayModeChanged, this, [=]() {
        d->_windowDisplayMode = eApp->getWindowDisplayMode();
        update();
    });
    eApp->syncWindowDisplayMode(this);
}

ElaDialog::~ElaDialog()
{
    eApp->syncWindowDisplayMode(this, false);
}

void ElaDialog::setIsStayTop(bool isStayTop)
{
    Q_D(ElaDialog);
    d->_appBar->setIsStayTop(isStayTop);
}

bool ElaDialog::getIsStayTop() const
{
    return d_ptr->_appBar->getIsStayTop();
}

void ElaDialog::setIsFixedSize(bool isFixedSize)
{
    Q_D(ElaDialog);
    d->_appBar->setIsFixedSize(isFixedSize);
}

bool ElaDialog::getIsFixedSize() const
{
    return d_ptr->_appBar->getIsFixedSize();
}

void ElaDialog::setIsDefaultClosed(bool isDefaultClosed)
{
    Q_D(ElaDialog);
    d->_appBar->setIsDefaultClosed(isDefaultClosed);
    Q_EMIT pIsDefaultClosedChanged();
}

bool ElaDialog::getIsDefaultClosed() const
{
    Q_D(const ElaDialog);
    return d->_appBar->getIsDefaultClosed();
}

void ElaDialog::setAppBarHeight(int appBarHeight)
{
    Q_D(ElaDialog);
    d->_appBar->setAppBarHeight(appBarHeight);
    Q_EMIT pAppBarHeightChanged();
}

int ElaDialog::getAppBarHeight() const
{
    Q_D(const ElaDialog);
    return d->_appBar->getAppBarHeight();
}

void ElaDialog::moveToCenter()
{
    if (isMaximized() || isFullScreen())
    {
        return;
    }
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    auto geometry = screen()->availableGeometry();
#else
    auto geometry = qApp->screenAt(this->geometry().center())->geometry();
#endif
    setGeometry((geometry.left() + geometry.right() - width()) / 2, (geometry.top() + geometry.bottom() - height()) / 2, width(), height());
}

void ElaDialog::setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable)
{
    Q_D(ElaDialog);
    d->_appBar->setWindowButtonFlag(buttonFlag, isEnable);
}

void ElaDialog::setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)
{
    Q_D(ElaDialog);
    d->_appBar->setWindowButtonFlags(buttonFlags);
}

ElaAppBarType::ButtonFlags ElaDialog::getWindowButtonFlags() const
{
    return d_ptr->_appBar->getWindowButtonFlags();
}

QWidget* ElaDialog::centralWidget() const
{
    Q_D(const ElaDialog);
    return d->_mainContainer;
}

void ElaDialog::paintEvent(QPaintEvent* event)
{
    Q_D(ElaDialog);
#if (QT_VERSION >= QT_VERSION_CHECK(6, 5, 3) && QT_VERSION <= QT_VERSION_CHECK(6, 6, 1))
    if (d->_windowDisplayMode != ElaApplicationType::WindowDisplayMode::ElaMica)
#else
    if (d->_windowDisplayMode == ElaApplicationType::WindowDisplayMode::Normal)
#endif
    {
        QPainter painter(this);
        painter.save();
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(ElaThemeColor(d->_themeMode, DialogBase));
#ifdef Q_OS_MACOS
        // macOS:无边框弹窗绘制圆角,配合 WA_TranslucentBackground 透出四角
        painter.drawRoundedRect(QRectF(rect()), 10, 10);
#else
        painter.drawRect(rect());
#endif
        painter.restore();
    }
    QWidget::paintEvent(event);
}

void ElaDialog::resizeEvent(QResizeEvent* event)
{
#ifdef Q_OS_MACOS
    // 用圆角区域裁剪窗口,避免四角出现直角残影
    QPainterPath path;
    path.addRoundedRect(QRectF(rect()), 10, 10);
    setMask(QRegion(path.toFillPolygon().toPolygon()));
#endif
    QDialog::resizeEvent(event);
}
