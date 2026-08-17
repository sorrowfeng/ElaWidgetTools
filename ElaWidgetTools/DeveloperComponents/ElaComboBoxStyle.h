#ifndef ELACOMBOBOXSTYLE_H
#define ELACOMBOBOXSTYLE_H

#include <QColor>
#include <QProxyStyle>

#include "Def.h"
class ElaComboBoxStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PROPERTY_CREATE(qreal, ExpandIconRotate)
    Q_PROPERTY_CREATE(qreal, ExpandMarkWidth)
    // 实例级自定义框体背景色(默认无效值=跟随主题;设置后优先生效)
    Q_PRIVATE_CREATE(QColor, LightDefaultColor)
    Q_PRIVATE_CREATE(QColor, LightHoverColor)
    Q_PRIVATE_CREATE(QColor, LightPressColor)
    Q_PRIVATE_CREATE(QColor, DarkDefaultColor)
    Q_PRIVATE_CREATE(QColor, DarkHoverColor)
    Q_PRIVATE_CREATE(QColor, DarkPressColor)
    // 下拉箭头颜色(默认无效值=跟随主题文字色 BasicText)
    Q_PRIVATE_CREATE(QColor, ExpandIconColor)
public:
    explicit ElaComboBoxStyle(QStyle* style = nullptr);
    ~ElaComboBoxStyle() override;
    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget = nullptr) const override;

    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

private:
    ElaThemeType::ThemeMode _themeMode;
    int _shadowBorderWidth{6};
};

#endif // ELACOMBOBOXSTYLE_H
