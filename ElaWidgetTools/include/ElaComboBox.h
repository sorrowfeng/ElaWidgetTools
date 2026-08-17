#ifndef ELACOMBOBOX_H
#define ELACOMBOBOX_H

#include <QComboBox>

#include "stdafx.h"

class ElaComboBoxPrivate;
class ELA_EXPORT ElaComboBox : public QComboBox
{
    Q_OBJECT
    Q_Q_CREATE(ElaComboBox);
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius)
public:
    explicit ElaComboBox(QWidget* parent = nullptr);
    ~ElaComboBox() override;

    void setEditable(bool editable);

    // 实例级自定义框体背景色(默认无效值=跟随主题;设置后任意主题下优先生效)
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

    // 下拉箭头颜色(默认无效值=跟随主题文字色)
    void setExpandIconColor(const QColor& color);
    QColor getExpandIconColor() const;

protected:
    virtual void showPopup() override;
    virtual void hidePopup() override;
};

#endif // ELACOMBOBOX_H
