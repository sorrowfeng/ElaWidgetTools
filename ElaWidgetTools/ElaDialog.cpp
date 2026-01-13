#include "ElaDialog.h"

#include <QPainter>
#include <QVBoxLayout>

#include "ElaDialogPrivate.h"
#include "ElaTheme.h"
Q_TAKEOVER_NATIVEEVENT_CPP(ElaDialog, d_func()->_appBar);
ElaDialog::ElaDialog(QWidget* parent)
    : QDialog{parent}, d_ptr(new ElaDialogPrivate())
{
    Q_D(ElaDialog);
    d->q_ptr = this;
    setObjectName("ElaDialog");
    setWindowTitle("ElaDialog");
    setWindowModality(Qt::ApplicationModal);
    // 设置默认尺寸
    resize(400, 300);

    // 自定义AppBar
    d->_appBar = new ElaAppBar(this);
    d->_appBar->setAppBarHeight(30);
    d->_appBar->setIsFixedSize(true);
    d->_appBar->setIsStayTop(true);
    d->_appBar->setWindowButtonFlags(ElaAppBarType::CloseButtonHint);
    d->_appBar->setIsDefaultClosed(false);
    connect(d->_appBar, &ElaAppBar::closeButtonClicked, this, [=]() {
        close();
    });

    // 创建主容器
    d->_mainContainer = new QWidget(this);
    d->_mainContainer->setObjectName("ElaDialogMainContainer");
    
    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    // 添加主容器，用户可以在其中设置自己的布局
    mainLayout->addWidget(d->_mainContainer);

    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

ElaDialog::~ElaDialog()
{
}

void ElaDialog::setWindowButtonFlags(ElaAppBarType::ButtonFlags flags)
{
    Q_D(ElaDialog);
    if (d->_appBar)
    {
        d->_appBar->setWindowButtonFlags(flags);
    }
}

void ElaDialog::setIsDefaultClosed(bool isDefaultClosed)
{
    Q_D(ElaDialog);
    if (d->_appBar)
    {
        d->_appBar->setIsDefaultClosed(isDefaultClosed);
    }
}

void ElaDialog::paintEvent(QPaintEvent* event)
{
    Q_D(ElaDialog);
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    // 背景绘制
    painter.setBrush(ElaThemeColor(d->_themeMode, DialogBase));
    painter.drawRect(rect());
    painter.restore();
    QDialog::paintEvent(event);
}

QWidget* ElaDialog::centralWidget() const
{
    Q_D(const ElaDialog);
    return d->_mainContainer;
}
