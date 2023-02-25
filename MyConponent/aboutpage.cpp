#include "aboutpage.h"

AboutPage::AboutPage(QWidget *parent) : PageWidget(parent)
{
    contentWidget->setMouseTracking(true);

    //Construct title layout
    titleLayout =new QVBoxLayout(contentWidget);
    titleLayout->setContentsMargins(28,46,28,28);
    titleLayout->setSpacing(18);
    titleLayout->setAlignment(Qt::AlignTop |Qt::AlignLeft);
    contentWidget->setLayout(titleLayout);

    //Construct title
    titleLabel=new QLabel("ABOUT",contentWidget);
    titleLabel->setFont(titleFont);
    titleLayout->addWidget(titleLabel);
    titleLabel->show();

    //Construct main layout
    mainWidget=new QWidget(contentWidget);
    mainWidget->setObjectName("mainWidget");
    mainWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    mainWidget->setStyleSheet("QWidget#mainWidget{background-color:#efefef;border-radius:8px;}");

    mainLayout=new QVBoxLayout(mainWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,8,0,8);
    mainLayout->setSpacing(8);
    mainWidget->setLayout(mainLayout);
    titleLayout->addWidget(mainWidget);
    mainWidget->show();

    //Construct contents
    authorLabel=new LineEditWidget(mainWidget);
    authorLabel->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    authorLabel->getMainLayout()->insertSpacing(1,8);
    authorLabel->setBackgroundColor(QColor(0,0,0,0));
    authorLabel->setHoverColor(QColor(0,0,0,10));
    authorLabel->setPressedColor(QColor(0,0,0,20));
    authorLabel->setText("Linloir \u2665");
//    authorLabel->setEnable(false);
    mainLayout->addWidget(authorLabel);
    authorLabel->show();

    versionLabel=new LineEditWidget(mainWidget);
    versionLabel->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    versionLabel->getMainLayout()->insertSpacing(1,8);
    versionLabel->setBackgroundColor(QColor(0,0,0,0));
    versionLabel->setHoverColor(QColor(0,0,0,10));
    versionLabel->setPressedColor(QColor(0,0,0,20));
    versionLabel->setText("Linloir \u2665");
//    versionLabel->setEnable(false);
    mainLayout->addWidget(versionLabel);
    versionLabel->show();

    dateLabel=new LineEditWidget(mainWidget);
    dateLabel->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    dateLabel->getMainLayout()->insertSpacing(1,8);
    dateLabel->setBackgroundColor(QColor(0,0,0,0));
    dateLabel->setHoverColor(QColor(0,0,0,10));
    dateLabel->setPressedColor(QColor(0,0,0,20));
    dateLabel->setText("Linloir \u2665");
    dateLabel->setEnable(false);
    mainLayout->addWidget(dateLabel);
    dateLabel->show();

    //insert line break
    QWidget * line= new QWidget(mainWidget);
    line->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    line->setFixedHeight(1);
    line->setStyleSheet("background-color:#c2c2c2");
    mainLayout->addWidget(line);
    line->show();

    skyTerLabel=new LineEditWidget(mainWidget);
    skyTerLabel->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    skyTerLabel->getMainLayout()->insertSpacing(1,8);
    skyTerLabel->setBackgroundColor(QColor(0,0,0,0));
    skyTerLabel->setHoverColor(QColor(0,0,0,10));
    skyTerLabel->setPressedColor(QColor(0,0,0,20));
    skyTerLabel->setText("Linloir \u2665");
    skyTerLabel->setEnable(false);
    mainLayout->addWidget(skyTerLabel);
    skyTerLabel->show();

    lightLabel=new LineEditWidget(mainWidget);
    lightLabel->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    lightLabel->getMainLayout()->insertSpacing(1,8);
    lightLabel->setBackgroundColor(QColor(0,0,0,0));
    lightLabel->setHoverColor(QColor(0,0,0,10));
    lightLabel->setPressedColor(QColor(0,0,0,20));
    lightLabel->setText("Linloir \u2665");
    lightLabel->setEnable(false);
    mainLayout->addWidget(lightLabel);
    lightLabel->show();

    coreLabel=new LineEditWidget(mainWidget);
    coreLabel->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    coreLabel->getMainLayout()->insertSpacing(1,8);
    coreLabel->setBackgroundColor(QColor(0,0,0,0));
    coreLabel->setHoverColor(QColor(0,0,0,10));
    coreLabel->setPressedColor(QColor(0,0,0,20));
    coreLabel->setText("Linloir \u2665");
    coreLabel->setEnable(false);
    mainLayout->addWidget(coreLabel);
    coreLabel->show();

    uiDesignerLabel=new LineEditWidget(mainWidget);
    uiDesignerLabel->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    uiDesignerLabel->getMainLayout()->insertSpacing(1,8);
    uiDesignerLabel->setBackgroundColor(QColor(0,0,0,0));
    uiDesignerLabel->setHoverColor(QColor(0,0,0,10));
    uiDesignerLabel->setPressedColor(QColor(0,0,0,20));
    uiDesignerLabel->setText("Linloir \u2665");
    uiDesignerLabel->setEnable(false);
    mainLayout->addWidget(uiDesignerLabel);
    uiDesignerLabel->show();

    //add line break
    line =new QWidget(mainWidget);
    line->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    line->setFixedHeight(1);
    line->setStyleSheet("background-color:#c2c2c2");
    mainLayout->addWidget(line);
    line->show();

    license=new LineEditWidget(mainWidget);
    license->getMainLayout()->insertWidget(0,new QLabel("Authored by"));
    license->getMainLayout()->insertSpacing(1,8);
    license->setBackgroundColor(QColor(0,0,0,0));
    license->setHoverColor(QColor(0,0,0,10));
    license->setPressedColor(QColor(0,0,0,20));
    license->setText("Linloir \u2665");
    license->setEnable(false);
    mainLayout->addWidget(license);
    license->show();
}

PushButton *AboutPage::getPageIconButton(QWidget *context)
{
    if(iconButton !=nullptr)
    {
        return iconButton;
    }
    //Generate new icon button
    iconButton=new PushButton(nullptr,context);
    iconButton->setMargin(20,18,16,18);
    iconButtonLabel=new QLabel(iconButton);
    iconButtonLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    QFont iconButtonFont("Font Awesome 6 Free Regular",12);
    iconButtonFont.setStyleStrategy(QFont::PreferAntialias);
    iconButtonLabel->setFont(iconButtonFont);
    iconButtonLabel->setText("\uf059");
    iconButtonLabel->setAlignment(Qt::AlignLeft);
    iconButton->setChildWidget(iconButtonLabel);

    return iconButton;
}

PushButton *AboutPage::getPageTextButton(QWidget *context)
{
    if(textButton !=nullptr)
    {
        return textButton;
    }

    //Generate new text button
    textButton=new PushButton(nullptr,context);
    textButton->setMargin(20,18,16,18);
    textButtonWidget=new QWidget(textButton);
    textButtonLayout=new QHBoxLayout(textButtonWidget);
    textButtonLayout->setContentsMargins(0,0,0,0);
    textButtonLayout->setSpacing(12);
    textButtonWidget->setLayout(textButtonLayout);

    //Generate text button contents
    textButtonIcon=new QLabel(textButtonWidget);
    QFont textButtonFont("Font Awesome 6 Free Regular",12);
    textButtonFont.setStyleStrategy(QFont::PreferQuality);
    textButtonIcon->setFont(textButtonFont);
    textButtonIcon->setText("\uf059");
    textButtonIcon->setAlignment(Qt::AlignLeft);

    textButtonLabel=new QLabel(textButtonWidget);
    textButtonLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
//    textButtonLabel->setFont(textButtonFont);
    textButtonLabel->setText("About");
    textButtonLabel->setAlignment(Qt::AlignLeft);

    //Add text button contents to layout
    textButtonLayout->addWidget(textButtonIcon);
    textButtonLayout->addWidget(textButtonLabel);
    textButtonIcon->show();
    textButtonLabel->show();

    textButton->setChildWidget(textButtonWidget);
    textButtonWidget->show();

    return textButton;
}
