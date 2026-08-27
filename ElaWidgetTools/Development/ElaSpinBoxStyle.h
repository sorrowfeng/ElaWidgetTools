#ifndef ELAWORKSPACE_ELAWIDGETTOOLS_DEVELOPERCOMPONENTS_ELASPINBOXSTYLE_H_
#define ELAWORKSPACE_ELAWIDGETTOOLS_DEVELOPERCOMPONENTS_ELASPINBOXSTYLE_H_

#include <QColor>
#include <QProxyStyle>

#include "ElaWidgetToolsDef.h"
class ElaSpinBoxStyle : public QProxyStyle
{
    Q_OBJECT
    Q_PRIVATE_CREATE(ElaSpinBoxType::ButtonMode, ButtonMode)
    // 实例级自定义背景色(默认无效值=跟随主题;设置后优先生效)
    Q_PRIVATE_CREATE(QColor, LightDefaultColor)
    Q_PRIVATE_CREATE(QColor, LightHoverColor)
    Q_PRIVATE_CREATE(QColor, LightPressColor)
    Q_PRIVATE_CREATE(QColor, DarkDefaultColor)
    Q_PRIVATE_CREATE(QColor, DarkHoverColor)
    Q_PRIVATE_CREATE(QColor, DarkPressColor)
public:
    explicit ElaSpinBoxStyle(QStyle* style = nullptr);
    ~ElaSpinBoxStyle() override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex* opt, SubControl sc, const QWidget* widget) const override;

private:
    ElaThemeType::ThemeMode _themeMode;
};

#endif // ELAWORKSPACE_ELAWIDGETTOOLS_DEVELOPERCOMPONENTS_ELASPINBOXSTYLE_H_

