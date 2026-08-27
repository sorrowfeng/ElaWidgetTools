#include "T_RibbonBar.h"

#include <QVBoxLayout>

#include "ElaComboBox.h"
#include "ElaMessageBar.h"
#include "ElaRibbonBar.h"
#include "ElaTabBar.h"
T_RibbonBar::T_RibbonBar(QWidget* parent)
    : T_BasePage(parent)
{
    // 预览窗口标题
    setWindowTitle("ElaRibbonBar");

    // 顶部元素
    createCustomWidget("ElaRibbonBar是一个仿Office风格的功能区组件，支持多页面、分组、图标动作和自定义控件，可在此界面体验其效果");

    // Ribbon页签切换栏 与RibbonBar联动
    _ribbonTabBar = new ElaTabBar(this);
    _ribbonTabBar->addTab("主页");
    _ribbonTabBar->addTab("插入");
    _ribbonTabBar->addTab("视图");

    _ribbonBar = new ElaRibbonBar(this);
    _ribbonBar->setRibbonTabBar(_ribbonTabBar);

    // 主页
    _ribbonBar->addRibbonAction("主页", "剪贴板", "粘贴", ElaIconType::Paste);
    _ribbonBar->addRibbonAction("主页", "剪贴板", "复制", ElaIconType::Copy);
    _ribbonBar->addRibbonAction("主页", "剪贴板", "剪切", ElaIconType::Scissors);
    _ribbonBar->addRibbonAction("主页", "编辑", "撤销", ElaIconType::ArrowRotateLeft);
    _ribbonBar->addRibbonAction("主页", "编辑", "重做", ElaIconType::ArrowRotateRight);

    // 插入
    _ribbonBar->addRibbonAction("插入", "媒体", "图片", ElaIconType::Image);
    _ribbonBar->addRibbonAction("插入", "媒体", "表格", ElaIconType::Table);
    _ribbonBar->addRibbonAction("插入", "媒体", "图表", ElaIconType::ChartColumn);
    _ribbonBar->addRibbonAction("插入", "链接", "超链接", ElaIconType::Link);

    // 视图（含自定义控件）
    _ribbonBar->addRibbonAction("视图", "显示", "放大", ElaIconType::MagnifyingGlassPlus);
    _ribbonBar->addRibbonAction("视图", "显示", "缩小", ElaIconType::MagnifyingGlassMinus);
    ElaComboBox* themeComboBox = new ElaComboBox(this);
    themeComboBox->addItem("明亮模式");
    themeComboBox->addItem("暗黑模式");
    _ribbonBar->addRibbonWidget("视图", "主题", themeComboBox);

    // 动作触发反馈
    connect(_ribbonBar, &ElaRibbonBar::ribbonActionTriggered, this, [=](const QString& pageName, const QString& groupName, QAction* action) {
        ElaMessageBar::information(ElaMessageBarType::Top, "RibbonAction", QString("%1/%2/%3 被触发").arg(pageName, groupName, action->text()), 1500);
    });

    _ribbonTabBar->setCurrentIndex(0);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("ElaRibbonBar");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->addWidget(_ribbonTabBar);
    centerLayout->addWidget(_ribbonBar);
    centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
}

T_RibbonBar::~T_RibbonBar()
{
}
