#include "T_Navigation.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "ElaBreadcrumbBar.h"
#include "ElaNavigationBar.h"
#include "ElaPivot.h"
#include "ElaPlainTextEdit.h"
#include "ElaPushButton.h"
#include "ElaScrollPageArea.h"
#include "ElaTabWidget.h"
#include "ElaText.h"
#include "ElaWidget.h"

T_Navigation::T_Navigation(QWidget* parent)
    : T_BasePage(parent)
{
    // 预览窗口标题
    setWindowTitle("ElaNavigation");

    // 顶部元素
    createCustomWidget("一些导航组件被放置于此，可在此界面体验其效果并按需添加进项目中");

    //ElaBreadcrumbBar
    ElaText* breadcrumbBarText = new ElaText("ElaBreadcrumbBar", this);
    breadcrumbBarText->setTextPixelSize(18);
    _breadcrumbBar = new ElaBreadcrumbBar(this);
    QStringList breadcrumbBarList;
    for (int i = 0; i < 20; i++)
    {
        breadcrumbBarList << QString("Item%1").arg(i + 1);
    }
    _breadcrumbBar->setBreadcrumbList(breadcrumbBarList);

    ElaPushButton* resetButton = new ElaPushButton("还原", this);
    resetButton->setFixedSize(60, 32);
    connect(resetButton, &ElaPushButton::clicked, this, [=]()
            { _breadcrumbBar->setBreadcrumbList(breadcrumbBarList); });

    QHBoxLayout* breadcrumbBarTextLayout = new QHBoxLayout();
    breadcrumbBarTextLayout->addWidget(breadcrumbBarText);
    breadcrumbBarTextLayout->addSpacing(15);
    breadcrumbBarTextLayout->addWidget(resetButton);
    breadcrumbBarTextLayout->addStretch();

    ElaScrollPageArea* breadcrumbBarArea = new ElaScrollPageArea(this);
    QVBoxLayout* breadcrumbBarLayout = new QVBoxLayout(breadcrumbBarArea);
    breadcrumbBarLayout->addWidget(_breadcrumbBar);

    // ElaPivot
    ElaText* pivotText = new ElaText("ElaPivot", this);
    pivotText->setTextPixelSize(18);
    _pivot = new ElaPivot(this);
    _pivot->setPivotSpacing(8);
    _pivot->setMarkWidth(75);
    _pivot->appendPivot("本地歌曲");
    _pivot->appendPivot("下载歌曲");
    _pivot->appendPivot("下载视频");
    _pivot->appendPivot("正在下载");
    _pivot->appendPivot("本地歌曲");
    _pivot->appendPivot("下载歌曲");
    _pivot->appendPivot("下载视频");
    _pivot->appendPivot("正在下载");
    _pivot->appendPivot("本地歌曲");
    _pivot->appendPivot("下载歌曲");
    _pivot->appendPivot("下载视频");
    _pivot->appendPivot("正在下载");
    _pivot->setCurrentIndex(0);

    ElaScrollPageArea* pivotArea = new ElaScrollPageArea(this);
    QVBoxLayout* pivotLayout = new QVBoxLayout(pivotArea);
    pivotLayout->addWidget(_pivot);

    // ElaTabWidget
    ElaText* tabWidgetText = new ElaText("ElaTabWidget", this);
    tabWidgetText->setTextPixelSize(18);
    _tabWidget = new ElaTabWidget(this);
    _tabWidget->setFixedHeight(600);
    _tabWidget->setIsTabTransparent(true);
    _tabWidget->setTabsClosable(false);
    _tabWidget->setTabSize(QSize(120, 35));
    ElaText* page1 = new ElaText("新标签页", this);
    page1->setTextPixelSize(32);
    page1->setAlignment(Qt::AlignCenter);
    _tabWidget->addTab(page1, QIcon(":/Resource/Image/Cirno.jpg"), "新标签页");
    for (int i = 0; i < 5; i++)
    {
        ElaText* page = new ElaText(QString("新标签页%1").arg(i), this);
        page->setTextPixelSize(32);
        page->setAlignment(Qt::AlignCenter);
        _tabWidget->addTab(page, QString("新标签页%1").arg(i));
    }
    // ElaNavigationBar
    ElaText* navigationBarText = new ElaText("ElaNavigationBar", this);
    navigationBarText->setTextPixelSize(18);
    ElaNavigationBar* navigationBar = new ElaNavigationBar(this);
    navigationBar->setFixedWidth(260);
    QStackedWidget* navigationStack = new QStackedWidget(this);
    for (int i = 0; i < 3; i++)
    {
        ElaText* page = new ElaText(QString("导航页面%1").arg(i + 1), this);
        page->setTextPixelSize(28);
        page->setAlignment(Qt::AlignCenter);
        navigationStack->addWidget(page);
        navigationBar->addPageNode(QString("导航页面%1").arg(i + 1), page, ElaIconType::House);
    }
    // 页面切换：导航节点被点击后，根据其 ElaPageKey 切换堆栈页
    connect(navigationBar, &ElaNavigationBar::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey, bool isRouteBack) {
        for (int i = 0; i < navigationStack->count(); i++)
        {
            if (navigationStack->widget(i)->property("ElaPageKey").toString() == nodeKey)
            {
                navigationStack->setCurrentIndex(i);
                break;
            }
        }
    });
    ElaScrollPageArea* navigationBarArea = new ElaScrollPageArea(this);
    navigationBarArea->setFixedHeight(350);
    QHBoxLayout* navigationBarLayout = new QHBoxLayout(navigationBarArea);
    navigationBarLayout->setContentsMargins(0, 0, 0, 0);
    navigationBarLayout->addWidget(navigationBar);
    navigationBarLayout->addWidget(navigationStack);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("ElaNavigation");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addLayout(breadcrumbBarTextLayout);
    centerVLayout->addSpacing(10);
    centerVLayout->addWidget(breadcrumbBarArea);
    centerVLayout->addSpacing(15);
    centerVLayout->addWidget(pivotText);
    centerVLayout->addSpacing(10);
    centerVLayout->addWidget(pivotArea);
    centerVLayout->addSpacing(15);
    centerVLayout->addWidget(navigationBarText);
    centerVLayout->addSpacing(10);
    centerVLayout->addWidget(navigationBarArea);
    centerVLayout->addSpacing(15);
    centerVLayout->addWidget(tabWidgetText);
    centerVLayout->addSpacing(10);
    centerVLayout->addWidget(_tabWidget);
    centerVLayout->addStretch();
    addCentralWidget(centralWidget, true, false, 0);
}

T_Navigation::~T_Navigation()
{
}
