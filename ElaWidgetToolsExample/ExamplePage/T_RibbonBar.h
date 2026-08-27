#ifndef T_RIBBONBAR_H
#define T_RIBBONBAR_H

#include "T_BasePage.h"

class ElaTabBar;
class ElaRibbonBar;
class T_RibbonBar : public T_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit T_RibbonBar(QWidget* parent = nullptr);
    ~T_RibbonBar();

private:
    ElaTabBar* _ribbonTabBar{nullptr};
    ElaRibbonBar* _ribbonBar{nullptr};
};

#endif // T_RIBBONBAR_H
