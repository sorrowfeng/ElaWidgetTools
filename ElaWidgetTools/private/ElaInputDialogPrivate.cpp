#include "ElaInputDialogPrivate.h"

#include <QVBoxLayout>

#include "ElaInputDialog.h"
#include "ElaMaskWidget.h"
#include "ElaLineEdit.h"
#include "ElaSpinBox.h"
#include "ElaDoubleSpinBox.h"

ElaInputDialogPrivate::ElaInputDialogPrivate(QObject* parent)
	: QObject{ parent }
{
}

ElaInputDialogPrivate::~ElaInputDialogPrivate()
{
}

void ElaInputDialogPrivate::ensureLineEdit()
{
	Q_Q(ElaInputDialog);
	if (!_lineEdit) {
		_lineEdit = new ElaLineEdit(q);
		_lineEdit->hide();
		QObject::connect(_lineEdit, &ElaLineEdit::textChanged,
			q, &ElaInputDialog::textValueChanged);
	}
}

void ElaInputDialogPrivate::ensureIntSpinBox()
{
	Q_Q(ElaInputDialog);
	if (!_intSpinBox) {
		_intSpinBox = new ElaSpinBox(q);
		_intSpinBox->hide();
		QObject::connect(_intSpinBox, &ElaSpinBox::valueChanged,
			q, &ElaInputDialog::intValueChanged);
	}
}

void ElaInputDialogPrivate::ensureDoubleSpinBox()
{
	Q_Q(ElaInputDialog);
	if (!_doubleSpinBox) {
		_doubleSpinBox = new ElaDoubleSpinBox(q);
		_doubleSpinBox->hide();
		QObject::connect(_doubleSpinBox, &ElaDoubleSpinBox::valueChanged,
			q, &ElaInputDialog::doubleValueChanged);
	}
}

void ElaInputDialogPrivate::setInputWidget(QWidget* widget)
{
	Q_ASSERT(widget);
	if (_inputWidget == widget)
		return;

	if (_centralWidget) {
		Q_ASSERT(_inputWidget);
		auto vboxLayout = static_cast<QVBoxLayout*>(_centralWidget->layout());
		Q_ASSERT(vboxLayout);

		vboxLayout->removeWidget(_inputWidget);
		_inputWidget->hide();
		vboxLayout->insertWidget(3, widget);
		widget->show();
	}

	_inputWidget = widget;
}

void ElaInputDialogPrivate::_doCloseAnimation()
{
	Q_Q(ElaInputDialog);
	_maskWidget->doMaskAnimation(0);
	q->QDialog::close();
}