#ifndef ELADIALOGPRIVATE_H
#define ELADIALOGPRIVATE_H

#include <QObject>
#include <QWidget>

#include "Def.h"
#include "stdafx.h"
class ElaAppBar;
class ElaDialog;
class ElaDialogPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaDialog)
public:
    explicit ElaDialogPrivate(QObject* parent = nullptr);
    ~ElaDialogPrivate();

private:
    ElaThemeType::ThemeMode _themeMode;
    ElaAppBar* _appBar{nullptr};
    QWidget* _mainContainer{nullptr};
};

#endif // ELADIALOGPRIVATE_H