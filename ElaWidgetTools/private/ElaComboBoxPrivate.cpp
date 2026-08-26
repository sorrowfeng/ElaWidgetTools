#include "ElaComboBoxPrivate.h"
#include "ElaComboBox.h"
#include "ElaTheme.h"
#include <QLineEdit>
ElaComboBoxPrivate::ElaComboBoxPrivate(QObject* parent)
    : QObject{parent}
{
}

ElaComboBoxPrivate::~ElaComboBoxPrivate()
{
}

void ElaComboBoxPrivate::onThemeChanged(ElaThemeType::ThemeMode themeMode)
{
    Q_Q(ElaComboBox);
    _themeMode = themeMode;
    auto lineEdit = q->lineEdit();
    if (lineEdit)
    {
        QPalette palette = lineEdit->palette();
        palette.setColor(QPalette::Text, ElaThemeColor(_themeMode, BasicText));
        palette.setColor(QPalette::PlaceholderText, ElaTheme::isDarkTheme(_themeMode) ? QColor(0xBA, 0xBA, 0xBA) : QColor(0x00, 0x00, 0x00, 128));
        lineEdit->setPalette(palette);
    }
}
