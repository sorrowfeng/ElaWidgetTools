#include "T_Card.h"

#include <QVBoxLayout>

#include "ElaExponentialBlur.h"
#include "ElaImageCard.h"
#include "ElaInteractiveCard.h"
#include "ElaLCDNumber.h"
#include "ElaMessageBar.h"
#include "ElaPromotionCard.h"
#include "ElaPromotionView.h"
#include "ElaReminderCard.h"
T_Card::T_Card(QWidget* parent)
    : T_BasePage(parent)
{
    // 预览窗口标题
    setWindowTitle("ElaCard");

    // 顶部元素
    createCustomWidget("一些常用的卡片组件被放置于此，可在此界面体验其效果并按需添加进项目中");

    _lcdNumber = new ElaLCDNumber(this);
    _lcdNumber->setIsUseAutoClock(true);
    _lcdNumber->setIsTransparent(false);
    //    _lcdNumber->setAutoClockFormat("hh:mm:ss");
    _lcdNumber->setFixedHeight(100);

    _promotionCard = new ElaPromotionCard(this);
    _promotionCard->setFixedSize(600, 300);
    _promotionCard->setCardPixmap(QPixmap(":/Resource/Image/Card/miku.png"));
    _promotionCard->setCardTitle("MiKu");
    _promotionCard->setPromotionTitle("SONG~");
    _promotionCard->setTitle("STYX HELIX");
    _promotionCard->setSubTitle("Never close your eyes, Searching for a true fate");

    _promotionView = new ElaPromotionView(this);

    ElaPromotionCard* exampleCard1 = new ElaPromotionCard(this);
    exampleCard1->setCardPixmap(QPixmap(":/Resource/Image/Card/miku.png"));
    exampleCard1->setCardTitle("MiKu");
    exampleCard1->setPromotionTitle("SONG~");
    exampleCard1->setTitle("STYX HELIX");
    exampleCard1->setSubTitle("Never close your eyes, Searching for a true fate");

    ElaPromotionCard* exampleCard2 = new ElaPromotionCard(this);
    exampleCard2->setCardPixmap(QPixmap(":/Resource/Image/Card/beach.png"));
    exampleCard2->setCardTitle("Beach");
    exampleCard2->setPromotionTitle("SONG~");
    exampleCard2->setTitle("STYX HELIX");
    exampleCard2->setSubTitle("Never close your eyes, Searching for a true fate");

    ElaPromotionCard* exampleCard3 = new ElaPromotionCard(this);
    exampleCard3->setCardPixmap(QPixmap(":/Resource/Image/Card/dream.png"));
    exampleCard3->setCardTitle("Dream");
    exampleCard3->setPromotionTitle("SONG~");
    exampleCard3->setTitle("STYX HELIX");
    exampleCard3->setSubTitle("Never close your eyes, Searching for a true fate");

    ElaPromotionCard* exampleCard4 = new ElaPromotionCard(this);
    exampleCard4->setCardPixmap(QPixmap(":/Resource/Image/Card/classroom.png"));
    exampleCard4->setCardTitle("Classroom");
    exampleCard4->setPromotionTitle("SONG~");
    exampleCard4->setTitle("STYX HELIX");
    exampleCard4->setSubTitle("Never close your eyes, Searching for a true fate");

    _promotionView->appendPromotionCard(exampleCard1);
    _promotionView->appendPromotionCard(exampleCard2);
    _promotionView->appendPromotionCard(exampleCard3);
    _promotionView->appendPromotionCard(exampleCard4);
    _promotionView->setIsAutoScroll(true);

    // ElaInteractiveCard
    ElaInteractiveCard* interactiveCard = new ElaInteractiveCard(this);
    interactiveCard->setFixedSize(300, 200);
    interactiveCard->setCardPixmap(QPixmap(":/Resource/Image/Card/miku.png"));
    interactiveCard->setCardPixmapSize(80, 80);
    interactiveCard->setTitle("ElaInteractiveCard");
    interactiveCard->setSubTitle("带图片的交互式透明卡片");
    connect(interactiveCard, &ElaInteractiveCard::clicked, this, [=]() {
        ElaMessageBar::information(ElaMessageBarType::Top, "ElaInteractiveCard", "卡片被点击", 1500);
    });

    // ElaReminderCard
    ElaReminderCard* reminderCard = new ElaReminderCard(this);
    reminderCard->setFixedSize(300, 200);
    reminderCard->setCardPixmap(QPixmap(":/Resource/Image/Card/dream.png"));
    reminderCard->setCardPixmapSize(80, 80);
    reminderCard->setTitle("ElaReminderCard");
    reminderCard->setSubTitle("带图片的提醒卡片");
    connect(reminderCard, &ElaReminderCard::clicked, this, [=]() {
        ElaMessageBar::information(ElaMessageBarType::Top, "ElaReminderCard", "卡片被点击", 1500);
    });

    // ElaExponentialBlur 指数模糊
    ElaImageCard* blurCard = new ElaImageCard(this);
    blurCard->setBorderRadius(10);
    blurCard->setFixedHeight(200);
    blurCard->setCardImage(ElaExponentialBlur::doExponentialBlur(QImage(":/Resource/Image/Card/beach.png"), 25).toImage());

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("ElaCard");
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->addWidget(_lcdNumber);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(_promotionCard);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(_promotionView);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(interactiveCard);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(reminderCard);
    centerLayout->addSpacing(20);
    centerLayout->addWidget(blurCard);
    centerLayout->addSpacing(100);
    centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
}

T_Card::~T_Card()
{
}
