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
    // 控件自身 palette 同步当前文字色,保证关闭态文字在默认绘制路径下也随主题变色
    const QColor textColor = ElaThemeColor(_themeMode, BasicText);
    QPalette widgetPalette = q->palette();
    widgetPalette.setColor(QPalette::Text, textColor);
    widgetPalette.setColor(QPalette::WindowText, textColor);
    q->setPalette(widgetPalette);
    auto lineEdit = q->lineEdit();
    if (lineEdit)
    {
        QPalette palette = lineEdit->palette();
        palette.setColor(QPalette::Text, textColor);
        palette.setColor(QPalette::PlaceholderText, ElaTheme::isDarkTheme(_themeMode) ? QColor(0xBA, 0xBA, 0xBA) : QColor(0x00, 0x00, 0x00, 128));
        lineEdit->setPalette(palette);
    }
}
