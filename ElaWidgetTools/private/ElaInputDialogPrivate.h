#ifndef ELAINPUTDIALOGPRIVATE_H
#define ELAINPUTDIALOGPRIVATE_H

#include <QObject>

#include "Def.h"
#include "stdafx.h"
class QVBoxLayout;
class ElaPushButton;
class ElaInputDialog;
class ElaMaskWidget;
class ElaText;
class ElaLineEdit;
class ElaSpinBox;
class ElaDoubleSpinBox;
class ElaInputDialogPrivate : public QObject {
	Q_OBJECT
		Q_D_CREATE(ElaInputDialog)
public:
	explicit ElaInputDialogPrivate(QObject* parent = nullptr);
	~ElaInputDialogPrivate();

	void ensureLineEdit();
	void ensureIntSpinBox();
	void ensureDoubleSpinBox();
	void setInputWidget(QWidget* widget);

private:
	qint64 _currentWinID{ 0 };
	ElaThemeType::ThemeMode _themeMode;
	ElaMaskWidget* _maskWidget{ nullptr };
	QWidget* _centralWidget{ nullptr };
	QWidget* _buttonWidget{ nullptr };
	QVBoxLayout* _mainLayout{ nullptr };
	QString _leftButtonText{ "cancel" };
	QString _rightButtonText{ "confirm" };
	ElaPushButton* _leftButton{ nullptr };
	ElaPushButton* _rightButton{ nullptr };
	ElaText* _title{ nullptr };
	ElaText* _subTitle{ nullptr };
	QWidget* _inputWidget{ nullptr };
	ElaLineEdit* _lineEdit{ nullptr };
	ElaSpinBox* _intSpinBox{ nullptr };
	ElaDoubleSpinBox* _doubleSpinBox{ nullptr };
	void _doCloseAnimation();
};

#endif  // ELAINPUTDIALOGPRIVATE_H
