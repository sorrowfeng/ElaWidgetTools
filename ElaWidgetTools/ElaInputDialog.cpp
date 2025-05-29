#include "ElaInputDialog.h"

#include <QApplication>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>
#include <QScopedPointer>

#include "ElaMaskWidget.h"
#include "ElaPushButton.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaWinShadowHelper.h"
#include "ElaLineEdit.h"
#include "ElaSpinBox.h"
#include "ElaDoubleSpinBox.h"

#include "private/ElaInputDialogPrivate.h"

ElaInputDialog::ElaInputDialog(QWidget* parent)
	: QDialog{ parent }, d_ptr(new ElaInputDialogPrivate()) {
	Q_D(ElaInputDialog);
	d->q_ptr = this;

	d->_maskWidget = new ElaMaskWidget(parent);
	d->_maskWidget->move(0, 0);
	d->_maskWidget->setFixedSize(parent->size());
	d->_maskWidget->setVisible(false);

	resize(400, height());
	setWindowModality(Qt::ApplicationModal);
#ifdef Q_OS_WIN
	createWinId();
#if (QT_VERSION >= QT_VERSION_CHECK(6, 5, 3) && \
     QT_VERSION <= QT_VERSION_CHECK(6, 6, 1))
	window()->setWindowFlags((window()->windowFlags()) |
		Qt::WindowMinimizeButtonHint |
		Qt::FramelessWindowHint);
#endif
#else
	window()->setWindowFlags((window()->windowFlags()) | Qt::FramelessWindowHint);
#endif
	d->_leftButton = new ElaPushButton("cancel", this);
	connect(d->_leftButton, &ElaPushButton::clicked, this, [=]() {
		Q_EMIT leftButtonClicked();
		onLeftButtonClicked();
		d->_doCloseAnimation();
		});
	d->_leftButton->setMinimumSize(0, 0);
	d->_leftButton->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
	d->_leftButton->setFixedHeight(38);
	d->_leftButton->setBorderRadius(6);
	d->_rightButton = new ElaPushButton("confirm", this);
	connect(d->_rightButton, &ElaPushButton::clicked, this, [=]() {
		Q_EMIT rightButtonClicked();
		onRightButtonClicked();
		d->_doCloseAnimation();
		});
	d->_rightButton->setLightDefaultColor(
		ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
	d->_rightButton->setLightHoverColor(
		ElaThemeColor(ElaThemeType::Light, PrimaryHover));
	d->_rightButton->setLightPressColor(
		ElaThemeColor(ElaThemeType::Light, PrimaryPress));
	d->_rightButton->setLightTextColor(Qt::white);
	d->_rightButton->setDarkDefaultColor(
		ElaThemeColor(ElaThemeType::Dark, PrimaryNormal));
	d->_rightButton->setDarkHoverColor(
		ElaThemeColor(ElaThemeType::Dark, PrimaryHover));
	d->_rightButton->setDarkPressColor(
		ElaThemeColor(ElaThemeType::Dark, PrimaryPress));
	d->_rightButton->setDarkTextColor(Qt::black);
	d->_rightButton->setMinimumSize(0, 0);
	d->_rightButton->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
	d->_rightButton->setFixedHeight(38);
	d->_rightButton->setBorderRadius(6);

	d->_centralWidget = new QWidget(this);
	QVBoxLayout* centralVLayout = new QVBoxLayout(d->_centralWidget);
	centralVLayout->setContentsMargins(15, 25, 15, 10);
	d->_title = new ElaText("输入", this);
	d->_title->setTextStyle(ElaTextType::Title);
	d->_subTitle = new ElaText("请输入值", this);
	d->_subTitle->setTextStyle(ElaTextType::Body);
	d->_lineEdit = new ElaLineEdit(this);
	d->_inputWidget = d->_lineEdit;
	centralVLayout->addWidget(d->_title);
	centralVLayout->addSpacing(2);
	centralVLayout->addWidget(d->_subTitle);
	centralVLayout->addSpacing(2);
	centralVLayout->addWidget(d->_inputWidget);
	centralVLayout->addStretch();

	d->_mainLayout = new QVBoxLayout(this);
	d->_mainLayout->setContentsMargins(0, 0, 0, 0);
	d->_buttonWidget = new QWidget(this);
	d->_buttonWidget->setFixedHeight(60);
	QHBoxLayout* buttonLayout = new QHBoxLayout(d->_buttonWidget);
	buttonLayout->addWidget(d->_leftButton);
	buttonLayout->addWidget(d->_rightButton);
	d->_mainLayout->addWidget(d->_centralWidget);
	d->_mainLayout->addWidget(d->_buttonWidget);

	d->_themeMode = eTheme->getThemeMode();
	connect(
		eTheme, &ElaTheme::themeModeChanged, this,
		[=](ElaThemeType::ThemeMode themeMode) { d->_themeMode = themeMode; });
}

ElaInputDialog::~ElaInputDialog() {
	Q_D(ElaInputDialog);
	d->_maskWidget->deleteLater();
}

void ElaInputDialog::onLeftButtonClicked() {}

void ElaInputDialog::onRightButtonClicked() {}

void ElaInputDialog::setCentralWidget(QWidget* centralWidget) {
	Q_D(ElaInputDialog);
	d->_mainLayout->takeAt(0);
	d->_mainLayout->takeAt(0);
	delete d->_centralWidget;
	d->_mainLayout->addWidget(centralWidget);
	d->_mainLayout->addWidget(d->_buttonWidget);
}

void ElaInputDialog::setInputMode(InputMode mode)
{
	Q_D(ElaInputDialog);

	QWidget* widget;

	switch (mode) {
	case IntInput:
		d->ensureIntSpinBox();
		widget = d->_intSpinBox;
		break;
	case DoubleInput:
		d->ensureDoubleSpinBox();
		widget = d->_doubleSpinBox;
		break;
	case TextInput:
		d->ensureLineEdit();
		widget = d->_lineEdit;
		break;
	default:
		Q_ASSERT(mode == TextInput);
		break;
	}

	d->setInputWidget(widget);
}

ElaInputDialog::InputMode ElaInputDialog::inputMode() const
{
	Q_D(const ElaInputDialog);

	if (d->_inputWidget) {
		if (d->_inputWidget == d->_intSpinBox) {
			return IntInput;
		}
		else if (d->_inputWidget == d->_doubleSpinBox) {
			return DoubleInput;
		}
	}

	return TextInput;
}

void ElaInputDialog::setLeftButtonVisible(bool visible) {
	Q_D(ElaInputDialog);
	d->_leftButton->setVisible(visible);
}

void ElaInputDialog::setRightButtonVisible(bool visible) {
	Q_D(ElaInputDialog);
	d->_rightButton->setVisible(visible);
}

void ElaInputDialog::setLeftButtonText(const QString& text) {
	Q_D(ElaInputDialog);
	d->_leftButton->setText(text);
}

void ElaInputDialog::setRightButtonText(const QString& text) {
	Q_D(ElaInputDialog);
	d->_rightButton->setText(text);
}

void ElaInputDialog::setTitleText(const QString& text) {
	Q_D(ElaInputDialog);
	d->_title->setText(text);
}

void ElaInputDialog::setSubTitleText(const QString& text) {
	Q_D(ElaInputDialog);
	d->_subTitle->setText(text);
}

void ElaInputDialog::setTextValue(const QString& text)
{
	Q_D(ElaInputDialog);

	setInputMode(TextInput);
	d->_lineEdit->setText(text);
}

QString ElaInputDialog::textValue() const
{
	Q_D(const ElaInputDialog);
	return d->_lineEdit->text();
}

void ElaInputDialog::setIntValue(int value)
{
	Q_D(ElaInputDialog);
	setInputMode(IntInput);
	d->_intSpinBox->setValue(value);
}

int ElaInputDialog::intValue() const
{
	Q_D(const ElaInputDialog);
	if (d->_intSpinBox) {
		return d->_intSpinBox->value();
	}
	else {
		return 0;
	}
}

void ElaInputDialog::setDoubleValue(double value)
{
	Q_D(ElaInputDialog);
	setInputMode(DoubleInput);
	d->_doubleSpinBox->setValue(value);
}

double ElaInputDialog::doubleValue() const
{
	Q_D(const ElaInputDialog);
	if (d->_doubleSpinBox) {
		return d->_doubleSpinBox->value();
	}
	else {
		return 0.0;
	}
}

void ElaInputDialog::setTextEchoMode(QLineEdit::EchoMode mode)
{
	Q_D(ElaInputDialog);
	d->ensureLineEdit();
	d->_lineEdit->setEchoMode(mode);
}

QLineEdit::EchoMode ElaInputDialog::textEchoMode() const
{
	Q_D(const ElaInputDialog);
	if (d->_lineEdit) {
		return d->_lineEdit->echoMode();
	}
	else {
		return QLineEdit::Normal;
	}
}

void ElaInputDialog::setIntMinimum(int min)
{
	Q_D(ElaInputDialog);
	d->ensureIntSpinBox();
	d->_intSpinBox->setMinimum(min);
}

int ElaInputDialog::intMinimum() const
{
	Q_D(const ElaInputDialog);
	if (d->_intSpinBox) {
		return d->_intSpinBox->minimum();
	}
	else {
		return 0;
	}
}

void ElaInputDialog::setIntMaximum(int max)
{
	Q_D(ElaInputDialog);
	d->ensureIntSpinBox();
	d->_intSpinBox->setMaximum(max);
}

int ElaInputDialog::intMaximum() const
{
	Q_D(const ElaInputDialog);
	if (d->_intSpinBox) {
		return d->_intSpinBox->maximum();
	}
	else {
		return 99;
	}
}

void ElaInputDialog::setIntRange(int min, int max)
{
	Q_D(ElaInputDialog);
	d->ensureIntSpinBox();
	d->_intSpinBox->setRange(min, max);
}

void ElaInputDialog::setIntStep(int step)
{
	Q_D(ElaInputDialog);
	d->ensureIntSpinBox();
	d->_intSpinBox->setSingleStep(step);
}

int ElaInputDialog::intStep() const
{
	Q_D(const ElaInputDialog);
	if (d->_intSpinBox) {
		return d->_intSpinBox->singleStep();
	}
	else {
		return 1;
	}
}

/*!
	\property ElaInputDialog::doubleMinimum
	\brief the minimum double precision floating point value accepted as input

	This property is only relevant when the input dialog is used in
	DoubleInput mode.
*/
void ElaInputDialog::setDoubleMinimum(double min)
{
	Q_D(ElaInputDialog);
	d->ensureDoubleSpinBox();
	d->_doubleSpinBox->setMinimum(min);
}

double ElaInputDialog::doubleMinimum() const
{
	Q_D(const ElaInputDialog);
	if (d->_doubleSpinBox) {
		return d->_doubleSpinBox->minimum();
	}
	else {
		return 0.0;
	}
}

/*!
	\property ElaInputDialog::doubleMaximum
	\brief the maximum double precision floating point value accepted as input

	This property is only relevant when the input dialog is used in
	DoubleInput mode.
*/
void ElaInputDialog::setDoubleMaximum(double max)
{
	Q_D(ElaInputDialog);
	d->ensureDoubleSpinBox();
	d->_doubleSpinBox->setMaximum(max);
}

double ElaInputDialog::doubleMaximum() const
{
	Q_D(const ElaInputDialog);
	if (d->_doubleSpinBox) {
		return d->_doubleSpinBox->maximum();
	}
	else {
		return 99.99;
	}
}

void ElaInputDialog::setDoubleRange(double min, double max)
{
	Q_D(ElaInputDialog);
	d->ensureDoubleSpinBox();
	d->_doubleSpinBox->setRange(min, max);
}

void ElaInputDialog::setDoubleDecimals(int decimals)
{
	Q_D(ElaInputDialog);
	d->ensureDoubleSpinBox();
	d->_doubleSpinBox->setDecimals(decimals);
}

int ElaInputDialog::doubleDecimals() const
{
	Q_D(const ElaInputDialog);
	if (d->_doubleSpinBox) {
		return d->_doubleSpinBox->decimals();
	}
	else {
		return 2;
	}
}

void ElaInputDialog::setDoubleStep(double step)
{
	Q_D(ElaInputDialog);
	d->ensureDoubleSpinBox();
	d->_doubleSpinBox->setSingleStep(step);
}

double ElaInputDialog::doubleStep() const
{
	Q_D(const ElaInputDialog);
	if (d->_doubleSpinBox)
		return d->_doubleSpinBox->singleStep();
	else
		return 1.0;
}

void ElaInputDialog::close() {
	Q_D(ElaInputDialog);
	d->_doCloseAnimation();
}

QString ElaInputDialog::getText(QWidget* parent, const QString& title, const QString& subTitle,
	const QString& leftText, const QString& rightText,
	QLineEdit::EchoMode echo, const QString& text,
	bool* ok, Qt::InputMethodHints inputMethodHints)
{
	QScopedPointer<ElaInputDialog> dialog(new ElaInputDialog(parent));
	dialog->setTitleText(title);
	dialog->setSubTitleText(subTitle);
	dialog->setLeftButtonText(leftText);
	dialog->setRightButtonText(rightText);
	dialog->setTextValue(text);
	dialog->setTextEchoMode(echo);
	dialog->setInputMethodHints(inputMethodHints);

	int ret = 0;
	connect(dialog.get(), &ElaInputDialog::rightButtonClicked, [&]() {
		ret = 1;
		});
	dialog->exec();
	if (ok)
		*ok = !!ret;
	if (bool(dialog) && ret) {
		return dialog->textValue();
	}
	else {
		return QString();
	}
}

int ElaInputDialog::getInt(QWidget* parent, const QString& title, const QString& subTitle,
	const QString& leftText, const QString& rightText,
	int value, int minValue, int maxValue,
	int step, bool* ok)
{
	QScopedPointer<ElaInputDialog> dialog(new ElaInputDialog(parent));
	dialog->setTitleText(title);
	dialog->setSubTitleText(subTitle);
	dialog->setLeftButtonText(leftText);
	dialog->setRightButtonText(rightText);
	dialog->setIntRange(minValue, maxValue);
	dialog->setIntValue(value);
	dialog->setIntStep(step);

	int ret = 0;
	connect(dialog.get(), &ElaInputDialog::rightButtonClicked, [&]() {
		ret = 1;
		});
	dialog->exec();
	if (ok)
		*ok = !!ret;
	if (bool(dialog) && ret) {
		return dialog->intValue();
	}
	else {
		return value;
	}
}

double ElaInputDialog::getDouble(QWidget* parent, const QString& title, const QString& subTitle,
	const QString& leftText, const QString& rightText,
	double value, double minValue, double maxValue,
	int decimals, bool* ok, double step)
{
	QScopedPointer<ElaInputDialog> dialog(new ElaInputDialog(parent));
	dialog->setTitleText(title);
	dialog->setSubTitleText(subTitle);
	dialog->setLeftButtonText(leftText);
	dialog->setRightButtonText(rightText);
	dialog->setDoubleDecimals(decimals);
	dialog->setDoubleRange(minValue, maxValue);
	dialog->setDoubleValue(value);
	dialog->setDoubleStep(step);

	int ret = 0;
	connect(dialog.get(), &ElaInputDialog::rightButtonClicked, [&]() {
		ret = 1;
		});
	dialog->exec();
	if (ok)
		*ok = !!ret;
	if (bool(dialog) && ret) {
		return dialog->doubleValue();
	}
	else {
		return value;
	}
}

void ElaInputDialog::showEvent(QShowEvent* event) {
	Q_D(ElaInputDialog);
	d->_maskWidget->setVisible(true);
	d->_maskWidget->raise();
	d->_maskWidget->setFixedSize(parentWidget()->size());
	d->_maskWidget->doMaskAnimation(90);
#ifdef Q_OS_WIN
#if (QT_VERSION >= QT_VERSION_CHECK(6, 5, 3) && \
     QT_VERSION <= QT_VERSION_CHECK(6, 6, 1))
	HWND hwnd = (HWND)d->_currentWinID;
	ElaWinShadowHelper::getInstance()->setWindowShadow(d->_currentWinID);
	DWORD style = ::GetWindowLongPtr(hwnd, GWL_STYLE);
	bool hasCaption = (style & WS_CAPTION) == WS_CAPTION;
	if (!hasCaption) {
		::SetWindowLongPtr(hwnd, GWL_STYLE, style | WS_CAPTION);
	}
#endif
#endif
	QDialog::showEvent(event);
}

void ElaInputDialog::paintEvent(QPaintEvent* event) {
	Q_D(ElaInputDialog);
	QPainter painter(this);
	painter.save();
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	painter.setPen(Qt::NoPen);
	painter.setBrush(ElaThemeColor(d->_themeMode, DialogBase));
	// 背景绘制
	painter.drawRect(rect());
	// 按钮栏背景绘制
	painter.setBrush(ElaThemeColor(d->_themeMode, DialogLayoutArea));
	painter.drawRoundedRect(QRectF(0, height() - 60, width(), 60), 8, 8);
	painter.restore();
}

void ElaInputDialog::keyPressEvent(QKeyEvent* event) { event->accept(); }

#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool ElaInputDialog::nativeEvent(const QByteArray& eventType, void* message,
	qintptr* result)
#else
bool ElaInputDialog::nativeEvent(const QByteArray& eventType, void* message,
	long* result)
#endif
{
	Q_D(ElaInputDialog);
	if ((eventType != "windows_generic_MSG") || !message) {
		return false;
	}
	const auto msg = static_cast<const MSG*>(message);
	const HWND hwnd = msg->hwnd;
	if (!hwnd || !msg) {
		return false;
	}
	d->_currentWinID = (qint64)hwnd;
	const UINT uMsg = msg->message;
	const WPARAM wParam = msg->wParam;
	const LPARAM lParam = msg->lParam;
	switch (uMsg) {
	case WM_WINDOWPOSCHANGING: {
		WINDOWPOS* wp = reinterpret_cast<WINDOWPOS*>(lParam);
		if (wp != nullptr && (wp->flags & SWP_NOSIZE) == 0) {
			wp->flags |= SWP_NOCOPYBITS;
			*result = ::DefWindowProcW(hwnd, uMsg, wParam, lParam);
			return true;
		}
		return false;
	}
	case WM_NCACTIVATE: {
		*result = TRUE;
		return true;
	}
	case WM_NCCALCSIZE: {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 5, 3) && \
     QT_VERSION <= QT_VERSION_CHECK(6, 6, 1))
		if (wParam == FALSE) {
			return false;
		}
		if (::IsZoomed(hwnd)) {
			setContentsMargins(8, 8, 8, 8);
		}
		else {
			setContentsMargins(0, 0, 0, 0);
		}
		*result = 0;
		return true;
#else
		if (wParam == FALSE) {
			return false;
		}
		RECT* clientRect = &((NCCALCSIZE_PARAMS*)(lParam))->rgrc[0];
		if (!::IsZoomed(hwnd)) {
			clientRect->top -= 1;
			clientRect->bottom -= 1;
		}
		*result = WVR_REDRAW;
		return true;
#endif
	}
	}
	return QDialog::nativeEvent(eventType, message, result);
}
#endif