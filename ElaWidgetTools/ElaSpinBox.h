#ifndef ELAWORKSPACE_ELAWIDGETTOOLS_ELASPINBOX_H_
#define ELAWORKSPACE_ELAWIDGETTOOLS_ELASPINBOX_H_

#include <QSpinBox>

#include "ElaWidgetToolsDef.h"

class ElaSpinBoxPrivate;
class ELA_EXPORT ElaSpinBox : public QSpinBox
{
    Q_OBJECT
    Q_Q_CREATE(ElaSpinBox)
    Q_PROPERTY_CREATE_Q_H(ElaSpinBoxType::ButtonMode, ButtonMode)
public:
    explicit ElaSpinBox(QWidget* parent = nullptr);
    ~ElaSpinBox() override;

    // 实例级自定义背景色(默认无效值=跟随主题;设置后任意主题下优先生效)
    void setLightDefaultColor(const QColor& color);
    QColor getLightDefaultColor() const;
    void setLightHoverColor(const QColor& color);
    QColor getLightHoverColor() const;
    void setLightPressColor(const QColor& color);
    QColor getLightPressColor() const;
    void setDarkDefaultColor(const QColor& color);
    QColor getDarkDefaultColor() const;
    void setDarkHoverColor(const QColor& color);
    QColor getDarkHoverColor() const;
    void setDarkPressColor(const QColor& color);
    QColor getDarkPressColor() const;

protected:
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // ELAWORKSPACE_ELAWIDGETTOOLS_ELASPINBOX_H_
