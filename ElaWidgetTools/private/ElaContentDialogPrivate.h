#ifndef ELAWORKSPACE_ELAWIDGETTOOLS_PRIVATE_ELACONTENTDIALOGPRIVATE_H_
#define ELAWORKSPACE_ELAWIDGETTOOLS_PRIVATE_ELACONTENTDIALOGPRIVATE_H_

#include <QObject>

#include "ElaWidgetToolsDef.h"
class QVBoxLayout;
class ElaPushButton;
class ElaContentDialog;
class ElaMaskWidget;
class ElaText;
class ElaAppBar;
class ElaContentDialogPrivate : public QObject
{
    Q_OBJECT
    Q_D_CREATE(ElaContentDialog)
public:
    explicit ElaContentDialogPrivate(QObject* parent = nullptr);
    ~ElaContentDialogPrivate() override;

private:
    qint64 _currentWinID{0};
    ElaAppBar* _appBar{nullptr};
    ElaThemeType::ThemeMode _themeMode;
    ElaMaskWidget* _maskWidget{nullptr};
    QWidget* _centralWidget{nullptr};
    QWidget* _buttonWidget{nullptr};
    QVBoxLayout* _mainLayout{nullptr};
    QString _leftButtonText{"cancel"};
    QString _middleButtonText{"minimum"};
    QString _rightButtonText{"exit"};
    ElaPushButton* _leftButton{nullptr};
    ElaPushButton* _middleButton{nullptr};
    ElaPushButton* _rightButton{nullptr};
    ElaText* _title{nullptr};
    ElaText* _subTitle{nullptr};
    void _doCloseAnimation(bool isAccept);
    void _moveToCenter();
};

#endif // ELAWORKSPACE_ELAWIDGETTOOLS_PRIVATE_ELACONTENTDIALOGPRIVATE_H_

