#ifndef ELADIALOG_H
#define ELADIALOG_H

#include <QDialog>

#include "ElaAppBar.h"
#include "stdafx.h"
class ElaDialogPrivate;
class ELA_EXPORT ElaDialog : public QDialog
{
    Q_OBJECT
    Q_Q_CREATE(ElaDialog)
    Q_TAKEOVER_NATIVEEVENT_H
public:
    explicit ElaDialog(QWidget* parent = nullptr);
    ~ElaDialog() override;

    void setWindowButtonFlags(ElaAppBarType::ButtonFlags flags);
    void setIsDefaultClosed(bool isDefaultClosed);
    
    // 获取主容器，用户可以在其上设置任何类型的布局
    QWidget* centralWidget() const;

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // ELADIALOG_H