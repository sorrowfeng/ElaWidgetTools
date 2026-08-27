#include "ElaIconButton.h"

#include "ElaApplication.h"
#include <QEvent>
#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>

#include "ElaTheme.h"
#include "private/ElaIconButtonPrivate.h"
Q_PROPERTY_CREATE_Q_CPP(ElaIconButton, int, BorderRadius)
Q_PROPERTY_CREATE_Q_CPP(ElaIconButton, qreal, Opacity);
Q_PROPERTY_REF_CREATE_Q_CPP(ElaIconButton, QColor, LightHoverColor);
Q_PROPERTY_REF_CREATE_Q_CPP(ElaIconButton, QColor, DarkHoverColor);
Q_PROPERTY_REF_CREATE_Q_CPP(ElaIconButton, QColor, LightIconColor);
Q_PROPERTY_REF_CREATE_Q_CPP(ElaIconButton, QColor, DarkIconColor);
Q_PROPERTY_REF_CREATE_Q_CPP(ElaIconButton, QColor, LightHoverIconColor);
Q_PROPERTY_REF_CREATE_Q_CPP(ElaIconButton, QColor, DarkHoverIconColor);
Q_PROPERTY_CREATE_Q_CPP(ElaIconButton, bool, IsSelected);
ElaIconButton::ElaIconButton(const QPixmap& pix, QWidget* parent)
    : QPushButton(parent), d_ptr(new ElaIconButtonPrivate())
{
    Q_D(ElaIconButton);
    d->q_ptr = this;
    d->_iconPix = pix.copy();
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = ElaThemeColor(ElaThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = ElaThemeColor(ElaThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = eTheme->getThemeMode();
    connect(this, &ElaIconButton::pIsSelectedChanged, this, [=]() {
        update();
    });
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

ElaIconButton::ElaIconButton(ElaIconType::IconName awesome, QWidget* parent)
    : QPushButton(parent), d_ptr(new ElaIconButtonPrivate())
{
    Q_D(ElaIconButton);
    d->q_ptr = this;
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = ElaThemeColor(ElaThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = ElaThemeColor(ElaThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = eTheme->getThemeMode();
    QFont iconFont = QFont("ElaAwesome");
    iconFont.setPixelSize(eApp->getFontPixelSize() + 2);
    this->setFont(iconFont);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
    connect(this, &ElaIconButton::pIsSelectedChanged, this, [=]() {
        update();
    });
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

ElaIconButton::ElaIconButton(ElaIconType::IconName awesome, int pixelSize, QWidget* parent)
    : QPushButton(parent), d_ptr(new ElaIconButtonPrivate())
{
    Q_D(ElaIconButton);
    d->q_ptr = this;
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = ElaThemeColor(ElaThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = ElaThemeColor(ElaThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = eTheme->getThemeMode();
    QFont iconFont = QFont("ElaAwesome");
    iconFont.setPixelSize(pixelSize);
    this->setFont(iconFont);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
    connect(this, &ElaIconButton::pIsSelectedChanged, this, [=]() {
        update();
    });
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

ElaIconButton::ElaIconButton(ElaIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QWidget* parent)
    : QPushButton(parent), d_ptr(new ElaIconButtonPrivate())
{
    Q_D(ElaIconButton);
    d->q_ptr = this;
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = ElaThemeColor(ElaThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = ElaThemeColor(ElaThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = ElaThemeColor(ElaThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = ElaThemeColor(ElaThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = eTheme->getThemeMode();
    QFont iconFont = QFont("ElaAwesome");
    iconFont.setPixelSize(pixelSize);
    this->setFont(iconFont);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
    this->setFixedSize(fixedWidth, fixedHeight);
    connect(this, &ElaIconButton::pIsSelectedChanged, this, [=]() {
        update();
    });
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

ElaIconButton::~ElaIconButton()
{
}

void ElaIconButton::setAwesome(ElaIconType::IconName awesome)
{
    Q_D(ElaIconButton);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
}

ElaIconType::IconName ElaIconButton::getAwesome() const
{
    return this->d_ptr->_pAwesome;
}

void ElaIconButton::setPixmap(const QPixmap& pix)
{
    Q_D(ElaIconButton);
    d->_iconPix = pix.copy();
}

bool ElaIconButton::event(QEvent* event)
{
    Q_D(ElaIconButton);
    switch (event->type())
    {
    case QEvent::Enter:
    {
        if (isEnabled() && !d->_pIsSelected)
        {
            d->_isAlphaAnimationFinished = false;
            QPropertyAnimation* alphaAnimation = new QPropertyAnimation(d, "pHoverAlpha");
            connect(alphaAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            connect(alphaAnimation, &QPropertyAnimation::finished, this, [=]() {
                d->_isAlphaAnimationFinished = true;
            });
            alphaAnimation->setDuration(175);
            alphaAnimation->setStartValue(d->_pHoverAlpha);
            // Blue 主题:默认悬停为蓝色调;显式设置了自定义悬停色
            // (如关闭按钮的红色)时优先使用自定义色
            const QColor lightHoverColor =
                (d->_themeMode == ElaThemeType::Blue &&
                 d->_pLightHoverColor == ElaThemeColor(ElaThemeType::Light, BasicHoverAlpha))
                    ? ElaThemeColor(d->_themeMode, BasicHoverAlpha)
                    : d->_pLightHoverColor;
            alphaAnimation->setEndValue(!ElaTheme::isDarkTheme(d->_themeMode) ? lightHoverColor.alpha() : d->_pDarkHoverColor.alpha());
            alphaAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    }
    case QEvent::Leave:
    {
        if (isEnabled() && !d->_pIsSelected)
        {
            d->_isAlphaAnimationFinished = false;
            QPropertyAnimation* alphaAnimation = new QPropertyAnimation(d, "pHoverAlpha");
            connect(alphaAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            connect(alphaAnimation, &QPropertyAnimation::finished, this, [=]() {
                d->_isAlphaAnimationFinished = true;
            });
            alphaAnimation->setDuration(175);
            alphaAnimation->setStartValue(d->_pHoverAlpha);
            alphaAnimation->setEndValue(0);
            alphaAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return QPushButton::event(event);
}

void ElaIconButton::paintEvent(QPaintEvent* event)
{
    Q_D(ElaIconButton);
    QPainter painter(this);
    painter.save();
    painter.setOpacity(d->_pOpacity);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);
    const auto lightStyleHoverColor = [=]() {
        // Blue 主题:默认悬停为蓝色调;显式设置了自定义悬停色
        // (如关闭按钮的红色)时优先使用自定义色
        if (d->_themeMode == ElaThemeType::Blue &&
            d->_pLightHoverColor == ElaThemeColor(ElaThemeType::Light, BasicHoverAlpha)) {
            return ElaThemeColor(d->_themeMode, BasicHoverAlpha);
        }
        return d->_pLightHoverColor;
    };
    if (d->_isAlphaAnimationFinished || d->_pIsSelected)
    {
        painter.setBrush(d->_pIsSelected   ? !ElaTheme::isDarkTheme(d->_themeMode) ? lightStyleHoverColor() : d->_pDarkHoverColor
                             : isEnabled() ? underMouse() ? !ElaTheme::isDarkTheme(d->_themeMode) ? lightStyleHoverColor() : d->_pDarkHoverColor : Qt::transparent
                                           : Qt::transparent);
    }
    else
    {
        QColor hoverColor = !ElaTheme::isDarkTheme(d->_themeMode) ? lightStyleHoverColor() : d->_pDarkHoverColor;
        hoverColor.setAlpha(d->_pHoverAlpha);
        painter.setBrush(hoverColor);
    }
    painter.drawRoundedRect(rect(), d->_pBorderRadius, d->_pBorderRadius);
    // 图标绘制
    if (!d->_iconPix.isNull())
    {
        QPainterPath path;
        path.addEllipse(rect());
        painter.setClipPath(path);
        painter.drawPixmap(rect(), d->_iconPix);
    }
    else
    {
        painter.setPen(isEnabled() ? !ElaTheme::isDarkTheme(d->_themeMode) ? underMouse() ? d->_pLightHoverIconColor : d->_pLightIconColor : underMouse() ? d->_pDarkHoverIconColor
                                                                                                                                                         : d->_pDarkIconColor
                                   : ElaThemeColor(d->_themeMode, BasicTextDisable));
        painter.drawText(rect(), Qt::AlignCenter, QChar((unsigned short)d->_pAwesome));
    }
    painter.restore();
}
