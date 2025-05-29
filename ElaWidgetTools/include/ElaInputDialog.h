#ifndef ELAINPUTDIALOG_H
#define ELAINPUTDIALOG_H
#include <QAbstractNativeEventFilter>
#include <QDialog>
#include <QLineEdit>

#include "stdafx.h"

class ElaInputDialogPrivate;
class ELA_EXPORT ElaInputDialog : public QDialog {
	Q_OBJECT
		Q_Q_CREATE(ElaInputDialog)
		QDOC_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode)
		QDOC_PROPERTY(QString textValue READ textValue WRITE setTextValue NOTIFY textValueChanged)
		QDOC_PROPERTY(int intValue READ intValue WRITE setIntValue NOTIFY intValueChanged)
		QDOC_PROPERTY(int doubleValue READ doubleValue WRITE setDoubleValue NOTIFY doubleValueChanged)
		QDOC_PROPERTY(QLineEdit::EchoMode textEchoMode READ textEchoMode WRITE setTextEchoMode)
		QDOC_PROPERTY(int intMinimum READ intMinimum WRITE setIntMinimum)
		QDOC_PROPERTY(int intMaximum READ intMaximum WRITE setIntMaximum)
		QDOC_PROPERTY(int intStep READ intStep WRITE setIntStep)
		QDOC_PROPERTY(double doubleMinimum READ doubleMinimum WRITE setDoubleMinimum)
		QDOC_PROPERTY(double doubleMaximum READ doubleMaximum WRITE setDoubleMaximum)
		QDOC_PROPERTY(int doubleDecimals READ doubleDecimals WRITE setDoubleDecimals)
		QDOC_PROPERTY(double doubleStep READ doubleStep WRITE setDoubleStep)
public:
	enum InputMode {
		TextInput,
		IntInput,
		DoubleInput
	};

	explicit ElaInputDialog(QWidget* parent);
	~ElaInputDialog() override;
	void setCentralWidget(QWidget* centralWidget);
	Q_SLOT virtual void onLeftButtonClicked();
	Q_SLOT virtual void onRightButtonClicked();

	void setInputMode(InputMode mode);
	InputMode inputMode() const;

	void setLeftButtonVisible(bool visible);
	void setRightButtonVisible(bool visible);

	void setLeftButtonText(const QString& text);
	void setRightButtonText(const QString& text);

	void setTitleText(const QString& text);
	void setSubTitleText(const QString& text);

	void setTextValue(const QString& text);
	QString textValue() const;

	void setIntValue(int value);
	int intValue() const;

	void setDoubleValue(double value);
	double doubleValue() const;

	void setTextEchoMode(QLineEdit::EchoMode mode);
	QLineEdit::EchoMode textEchoMode() const;

	void setIntMinimum(int min);
	int intMinimum() const;

	void setIntMaximum(int max);
	int intMaximum() const;

	void setIntRange(int min, int max);

	void setIntStep(int step);
	int intStep() const;

	void setDoubleMinimum(double min);
	double doubleMinimum() const;

	void setDoubleMaximum(double max);
	double doubleMaximum() const;

	void setDoubleRange(double min, double max);

	void setDoubleDecimals(int decimals);
	int doubleDecimals() const;

	void setDoubleStep(double step);
	double doubleStep() const;

	void close();

	static QString getText(QWidget* parent, const QString& title, const QString& subTitle,
		const QString& leftText = "cancel", const QString& rightText = "confirm",
		QLineEdit::EchoMode echo = QLineEdit::Normal,
		const QString& text = QString(), bool* ok = nullptr,
		Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

	static int getInt(QWidget* parent, const QString& title, const QString& subTitle,
		const QString& leftText = "cancel", const QString& rightText = "confirm",
		int value = 0, int minValue = -2147483647, int maxValue = 2147483647,
		int step = 1, bool* ok = nullptr);

	static double getDouble(QWidget* parent, const QString& title, const QString& subTitle,
		const QString& leftText = "cancel", const QString& rightText = "confirm",
		double value = 0, double minValue = -2147483647, double maxValue = 2147483647,
		int decimals = 1, bool* ok = nullptr, double step = 1);

Q_SIGNALS:
	Q_SIGNAL void leftButtonClicked();
	Q_SIGNAL void rightButtonClicked();
	Q_SIGNAL void textValueChanged(const QString& text);
	Q_SIGNAL void intValueChanged(int value);
	Q_SIGNAL void doubleValueChanged(double value);

protected:
	virtual void showEvent(QShowEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override;
#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	virtual bool nativeEvent(const QByteArray& eventType, void* message,
		qintptr* result) override;
#else
	virtual bool nativeEvent(const QByteArray& eventType, void* message,
		long* result) override;
#endif
#endif
};

#endif  // ELAINPUTDIALOG_H
