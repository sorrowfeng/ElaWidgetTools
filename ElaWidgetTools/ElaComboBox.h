#ifndef ELAWORKSPACE_ELAWIDGETTOOLS_ELACOMBOBOX_H_
#define ELAWORKSPACE_ELAWIDGETTOOLS_ELACOMBOBOX_H_

#include <QComboBox>

#include "ElaWidgetToolsExport.h"
#include "ElaPropertyMacro.h"

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

protected:
    virtual void showPopup() override;
    virtual void hidePopup() override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // ELAWORKSPACE_ELAWIDGETTOOLS_ELACOMBOBOX_H_
