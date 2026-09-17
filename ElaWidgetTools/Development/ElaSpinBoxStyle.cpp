#include "ElaSpinBoxStyle.h"

#include "ElaApplication.h"
#include "ElaTheme.h"
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionSpinBox>
#include <cmath>
ElaSpinBoxStyle::ElaSpinBoxStyle(QStyle* style)
{
    _pButtonMode = ElaSpinBoxType::Inline;
    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}

ElaSpinBoxStyle::~ElaSpinBoxStyle()
{
}

void ElaSpinBoxStyle::drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const
{
    switch (control)
    {
    case QStyle::CC_SpinBox:
    {
        const QStyleOptionSpinBox* sopt = qstyleoption_cast<const QStyleOptionSpinBox*>(option);
        if (!sopt)
        {
            break;
        }
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        //背景
        QRect spinBoxRect = sopt->rect.adjusted(1, 1, -1, -1);
        painter->setPen(ElaThemeColor(_themeMode, BasicBorder));
        bool isEnable = sopt->state.testFlag(QStyle::State_Enabled);
        // Blue 主题:输入框背景沿用 Light 配色(不变蓝);实例自定义色优先
        const bool isLightTheme = !ElaTheme::isDarkTheme(_themeMode);
        const QColor& customDefault = isLightTheme ? _pLightDefaultColor : _pDarkDefaultColor;
        const QColor& customHover = isLightTheme ? _pLightHoverColor : _pDarkHoverColor;
        const QColor& customPress = isLightTheme ? _pLightPressColor : _pDarkPressColor;
        const ElaThemeType::ThemeMode boxThemeMode = _themeMode == ElaThemeType::Blue ? ElaThemeType::Light : _themeMode;
        if (isEnable)
        {
            if (sopt->state & QStyle::State_MouseOver)
            {
                painter->setBrush(eTheme->getThemeColor(boxThemeMode, ElaThemeType::BasicHover));
            }
            else
            {
                painter->setBrush(customDefault.isValid() ? customDefault : eTheme->getThemeColor(boxThemeMode, ElaThemeType::BasicBase));
            }
        }
        else
        {
            painter->setBrush(ElaThemeColor(_themeMode, BasicDisable));
        }
        painter->drawRoundedRect(spinBoxRect, 4, 4);
        if (_pButtonMode != ElaSpinBoxType::NoButtons)
        {
            //添加按钮
            QRect addLineRect = subControlRect(control, sopt, SC_ScrollBarAddLine, widget);
            //减少按钮
            QRect subLineRect = subControlRect(control, sopt, SC_ScrollBarSubLine, widget);
            if (isEnable)
            {
                //添加按钮
                if (sopt->activeSubControls == SC_ScrollBarAddLine)
                {
                    painter->setPen(Qt::NoPen);
                    if (sopt->state & QStyle::State_Sunken && sopt->state & QStyle::State_MouseOver)
                    {
                        painter->setBrush(customPress.isValid() ? customPress : ElaThemeColor(_themeMode, BasicPressAlpha));
                    }
                    else
                    {
                        if (sopt->state & QStyle::State_MouseOver)
                        {
                            painter->setBrush(customHover.isValid() ? customHover : ElaThemeColor(_themeMode, BasicHoverAlpha));
                        }
                    }
                    painter->drawRoundedRect(addLineRect, 4, 4);
                }
                //减少按钮
                if (sopt->activeSubControls == SC_ScrollBarSubLine)
                {
                    painter->setPen(Qt::NoPen);
                    if (sopt->state & QStyle::State_Sunken && sopt->state & QStyle::State_MouseOver)
                    {
                        painter->setBrush(customPress.isValid() ? customPress : ElaThemeColor(_themeMode, BasicPressAlpha));
                    }
                    else
                    {
                        if (sopt->state & QStyle::State_MouseOver)
                        {
                            painter->setBrush(customHover.isValid() ? customHover : ElaThemeColor(_themeMode, BasicHoverAlpha));
                        }
                    }
                    painter->drawRoundedRect(subLineRect, 4, 4);
                }
            }
            //添加图标
            QFont iconFont = QFont("ElaAwesome");
            iconFont.setPixelSize(eApp->getFontPixelSize() + 4);
            painter->setFont(iconFont);
            painter->setPen(isEnable ? ElaThemeColor(_themeMode, BasicText) : ElaThemeColor(_themeMode, BasicTextDisable));
            painter->drawText(addLineRect, Qt::AlignCenter, _pButtonMode == ElaSpinBoxType::PMSide ? QChar((unsigned short)ElaIconType::Plus) : QChar((unsigned short)ElaIconType::AngleUp));
            //减小图标
            painter->drawText(subLineRect, Qt::AlignCenter, _pButtonMode == ElaSpinBoxType::PMSide ? QChar((unsigned short)ElaIconType::Minus) : QChar((unsigned short)ElaIconType::AngleDown));
        }
        //底边线
        painter->setPen(Qt::NoPen);
        painter->setBrush(ElaThemeColor(_themeMode, BasicHemline));
        QPainterPath path;
        path.moveTo(4, spinBoxRect.y() + spinBoxRect.height());
        path.lineTo(spinBoxRect.width() - 4, spinBoxRect.y() + spinBoxRect.height());
        path.arcTo(QRectF(spinBoxRect.width() - 8, spinBoxRect.y() + spinBoxRect.height() - 8, 8, 8), -90, 45);
        path.lineTo(4 - 2 * std::sqrt(2), spinBoxRect.y() + spinBoxRect.height() - (4 - 2 * std::sqrt(2)));
        path.arcTo(QRectF(0, spinBoxRect.y() + spinBoxRect.height() - 8, 8, 8), 225, 45);
        path.closeSubpath();
        painter->drawPath(path);
        painter->restore();
        return;
    }
    default:
    {
        break;
    }
    }
    QProxyStyle::drawComplexControl(control, option, painter, widget);
}

QRect ElaSpinBoxStyle::subControlRect(ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget) const
{
    QRect rect = QProxyStyle::subControlRect(cc, opt, sc, widget);
    switch (cc)
    {
    case CC_SpinBox:
    {
        // macOS 的 QMacStyle 对 SC_SpinBoxFrame 的度量与 Windows/Linux 不同,
        // 直接用控件矩形作为基准,保证各平台按钮位置一致。
#ifdef Q_OS_MACOS
        const QRect baseFrame = opt->rect;
#else
        const QRect baseFrame = QProxyStyle::subControlRect(cc, opt, SC_SpinBoxFrame, widget);
#endif
        switch (sc)
        {
        case SC_ScrollBarAddLine:
        {
            //增加按钮
            QRect spinBoxRect = baseFrame.adjusted(1, 1, -1, -1);
            switch (_pButtonMode)
            {
            case ElaSpinBoxType::Inline:
            {
                return QRect(spinBoxRect.width() - spinBoxRect.height(), spinBoxRect.y(), spinBoxRect.height(), spinBoxRect.height()).adjusted(3, 4, -3, -5);
            }
            case ElaSpinBoxType::Compact:
            {
                return QRect(spinBoxRect.width() - spinBoxRect.height(), spinBoxRect.y(), spinBoxRect.height(), spinBoxRect.height() / 2).adjusted(3, 4, -3, 0);
            }
            case ElaSpinBoxType::Side:
            case ElaSpinBoxType::PMSide:
            {
                return QRect(spinBoxRect.width() - spinBoxRect.height(), spinBoxRect.y(), spinBoxRect.height(), spinBoxRect.height()).adjusted(3, 4, -3, -5);
            }
            case ElaSpinBoxType::NoButtons:
            {
                return QRect();
            }
            }
        }
        case SC_ScrollBarSubLine:
        {
            //减少按钮
            QRect spinBoxRect = baseFrame.adjusted(1, 1, -1, -1);
            switch (_pButtonMode)
            {
            case ElaSpinBoxType::Inline:
            {
                return QRect(spinBoxRect.width() - 2 * spinBoxRect.height(), spinBoxRect.y(), spinBoxRect.height(), spinBoxRect.height()).adjusted(6, 4, 0, -5);
            }
            case ElaSpinBoxType::Compact:
            {
                return QRect(spinBoxRect.width() - spinBoxRect.height(), spinBoxRect.center().y(), spinBoxRect.height(), spinBoxRect.height() / 2).adjusted(3, 0, -3, -5);
            }
            case ElaSpinBoxType::Side:
            case ElaSpinBoxType::PMSide:
            {
                return QRect(spinBoxRect.x(), spinBoxRect.y(), spinBoxRect.height(), spinBoxRect.height()).adjusted(3, 4, -3, -5);
            }
            case ElaSpinBoxType::NoButtons:
            {
                return QRect();
            }
            }
        }
        case SC_SpinBoxEditField:
        {
            QRect spinBoxRect = baseFrame;
            switch (_pButtonMode)
            {
            case ElaSpinBoxType::Inline:
            {
                return {spinBoxRect.x(), spinBoxRect.y(), spinBoxRect.width() - 2 * spinBoxRect.height() + 6, spinBoxRect.height()};
            }
            case ElaSpinBoxType::Compact:
            {
                return {spinBoxRect.x(), spinBoxRect.y(), spinBoxRect.width() - spinBoxRect.height() + 3, spinBoxRect.height()};
            }
            case ElaSpinBoxType::Side:
            case ElaSpinBoxType::PMSide:
            {
                return {spinBoxRect.height(), spinBoxRect.y(), spinBoxRect.width() - 2 * spinBoxRect.height(), spinBoxRect.height()};
            }
            case ElaSpinBoxType::NoButtons:
            {
                return spinBoxRect;
            }
            }
        }
        default:
        {
            break;
        }
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return rect;
}
