#include "T_TableView.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QButtonGroup>

#include "ElaTableView.h"
#include "ElaRadioButton.h"
#include "ElaText.h"
#include "T_TableViewModel.h"

T_TableView::T_TableView(QWidget* parent)
    : T_BasePage(parent)
{
    // 预览窗口标题
    setWindowTitle("ElaTableView");

    // 顶部元素
    createCustomWidget("表格视图被放置于此，可在此界面体验其效果并按需添加进项目中");

    ElaRadioButton* headerButton = new ElaRadioButton("Header", this);
    ElaRadioButton* fillButton = new ElaRadioButton("Fill", this);
    ElaRadioButton* headerDangerButton =
        new ElaRadioButton("HeaderDanger", this);
    ElaRadioButton* fillDangerButton = new ElaRadioButton("FillDanger", this);
    headerButton->setChecked(true);
    QHBoxLayout* selectModeLayout = new QHBoxLayout();
    ElaText* selectModeText = new ElaText("选择模式切换", this);
    selectModeText->setWordWrap(false);
    selectModeText->setTextPixelSize(15);
    selectModeLayout->addWidget(selectModeText);
    selectModeLayout->addStretch();
    selectModeLayout->addWidget(headerButton);
    selectModeLayout->addWidget(fillButton);
    selectModeLayout->addWidget(headerDangerButton);
    selectModeLayout->addWidget(fillDangerButton);
    QButtonGroup* modeButtonGroup = new QButtonGroup(this);
    modeButtonGroup->addButton(headerButton, 0);
    modeButtonGroup->addButton(fillButton, 1);
    modeButtonGroup->addButton(headerDangerButton, 2);
    modeButtonGroup->addButton(fillDangerButton, 3);
    connect(modeButtonGroup,
            QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled),
            this, [=](QAbstractButton* button, bool isToggled) {
              if (isToggled) {
                auto mode =
                    (ElaViewType::SelectMode)modeButtonGroup->id(button);
                _tableView->setSelectMode(mode);
              }
            });

    //ElaTableView
    ElaText* tableText = new ElaText("ElaTableView", this);
    tableText->setTextPixelSize(18);
    _tableView = new ElaTableView(this);
    // ElaScrollBar* tableViewFloatScrollBar = new ElaScrollBar(_tableView->verticalScrollBar(), _tableView);
    // tableViewFloatScrollBar->setIsAnimation(true);
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(16);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableView->setModel(new T_TableViewModel(this));
    _tableView->setAlternatingRowColors(true);
    _tableView->setIconSize(QSize(38, 38));
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->horizontalHeader()->setMinimumSectionSize(60);
    _tableView->verticalHeader()->setMinimumSectionSize(46);
    _tableView->setFixedHeight(450);
    connect(_tableView, &ElaTableView::tableViewShow, this, [=]() {
        _tableView->setColumnWidth(0, 60);
        _tableView->setColumnWidth(1, 205);
        _tableView->setColumnWidth(2, 170);
        _tableView->setColumnWidth(3, 150);
        _tableView->setColumnWidth(4, 60);
    });
    QHBoxLayout* tableViewLayout = new QHBoxLayout();
    tableViewLayout->setContentsMargins(0, 0, 10, 0);
    tableViewLayout->addWidget(_tableView);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("ElaView");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(tableText);
    centerVLayout->addLayout(selectModeLayout);
    centerVLayout->addSpacing(10);
    centerVLayout->addLayout(tableViewLayout);
    centerVLayout->addStretch();
    addCentralWidget(centralWidget, true, false, 0);
}

T_TableView::~T_TableView()
{
}
