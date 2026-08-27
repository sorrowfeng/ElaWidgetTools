#ifndef ELAWORKSPACE_ELAWIDGETTOOLS_ELATOOLBUTTON_H_
#define ELAWORKSPACE_ELAWIDGETTOOLS_ELATOOLBUTTON_H_

#include <QToolButton>

#include "ElaWidgetToolsDef.h"
class ElaMenu;
class ElaToolButtonPrivate;
class ELA_EXPORT ElaToolButton : public QToolButton
{
    Q_OBJECT
    Q_Q_CREATE(ElaToolButton)
    Q_PROPERTY_CREATE_Q_H(int, BorderRadius);
    Q_PROPERTY_CREATE_Q_H(bool, IsSelected);

public:
    explicit ElaToolButton(QWidget* parent = nullptr);
    ~ElaToolButton() override;

    void setIsTransparent(bool isTransparent);
    bool getIsTransparent() const;

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

    void setMenu(ElaMenu* menu);
    void setElaIcon(ElaIconType::IconName icon);
    void setElaIcon(ElaIconType::IconName icon, int rotate);

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // ELAWORKSPACE_ELAWIDGETTOOLS_ELATOOLBUTTON_H_
