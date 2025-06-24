#include "T_ListView.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>

#include "ElaListView.h"
#include "ElaScrollBar.h"
#include "ElaText.h"
#include "T_ListViewModel.h"
#include "ElaRadioButton.h"

T_ListView::T_ListView(QWidget* parent)
    : T_BasePage(parent)
{
    // 预览窗口标题
    setWindowTitle("ElaListView");

    // 顶部元素
    createCustomWidget("列表视图被放置于此，可在此界面体验其效果并按需添加进项目中");

    
    ElaRadioButton* headerButton = new ElaRadioButton("Header", this);
    ElaRadioButton* fillButton = new ElaRadioButton("Fill", this);
    ElaRadioButton* headerDangerButton = new ElaRadioButton("HeaderDanger", this);
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
    connect(modeButtonGroup, QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled), this, [=](QAbstractButton* button, bool isToggled) {
        if (isToggled)
        {
            auto mode = (ElaViewType::SelectMode)modeButtonGroup->id(button);
            _listView->setSelectMode(mode);
        }
    });

    //ElaListView
    ElaText* listText = new ElaText("ElaListView", this);
    listText->setTextPixelSize(18);
    _listView = new ElaListView(this);
    _listView->setFixedHeight(450);
    // _listView->setAlternatingRowColors(true);
    _listView->setModel(new T_ListViewModel(this));
    ElaScrollBar* listViewFloatScrollBar = new ElaScrollBar(_listView->verticalScrollBar(), _listView);
    listViewFloatScrollBar->setIsAnimation(true);
    QHBoxLayout* listViewLayout = new QHBoxLayout();
    listViewLayout->setContentsMargins(0, 0, 10, 0);
    listViewLayout->addWidget(_listView);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("ElaView");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(listText);
    centerVLayout->addLayout(selectModeLayout);
    centerVLayout->addSpacing(10);
    centerVLayout->addLayout(listViewLayout);
    centerVLayout->addStretch();
    addCentralWidget(centralWidget, true, false, 0);
}

T_ListView::~T_ListView()
{
}
