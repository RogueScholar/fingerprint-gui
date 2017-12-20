/********************************************************************************
** Form generated from reading UI file 'FingerprintGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINGERPRINTGUI_H
#define UI_FINGERPRINTGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QAction *action_Exit;
    QAction *action_About;
    QAction *action_Help;
    QAction *action_Forum_Online;
    QAction *action_Homepage;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *deviceLabel;
    QComboBox *deviceCombo;
    QSpacerItem *horizontalSpacer;
    QPushButton *rescanButton;
    QHBoxLayout *hboxLayout;
    QRadioButton *vendornameButton;
    QRadioButton *drivernameButton;
    QSpacerItem *spacerItem;
    QTabWidget *tabWidget;
    QWidget *devicesTab;
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *label;
    QListWidget *usbDeviceListWidget;
    QWidget *fingerTab;
    QVBoxLayout *vboxLayout2;
    QVBoxLayout *vboxLayout3;
    QLabel *fingerLabel;
    QFrame *frame;
    QLabel *leftHandPictureLabel;
    QLabel *rightHandPictureLabel;
    QRadioButton *lsButton;
    QRadioButton *lrButton;
    QRadioButton *lmButton;
    QRadioButton *lpButton;
    QRadioButton *ltButton;
    QRadioButton *rtButton;
    QRadioButton *rpButton;
    QRadioButton *rmButton;
    QRadioButton *rrButton;
    QRadioButton *rsButton;
    QLabel *leftHandLabel;
    QLabel *rightHandLabel;
    QLabel *currentFingerLabel;
    QWidget *scanTab;
    QLabel *animationLabel;
    QLabel *fingerprintLabel1;
    QLabel *fingerprintLabel2;
    QLabel *fingerprintLabel3;
    QLabel *acquireLabel;
    QLabel *fpStatusLabel1;
    QLabel *fpStatusLabel2;
    QLabel *fpStatusLabel3;
    QLabel *fpResultLabel1;
    QLabel *fpResultLabel2;
    QLabel *fpResultLabel3;
    QLabel *fingerprintLabel4;
    QLabel *fingerprintLabel5;
    QLabel *fpStatusLabel4;
    QLabel *fpStatusLabel5;
    QLabel *fpResultLabel5;
    QLabel *fpResultLabel4;
    QWidget *settingsTab;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *vboxLayout4;
    QLabel *fprintLabel1;
    QLabel *fprintLabel2;
    QLabel *noFingerprintsLabel;
    QSpacerItem *spacerItem1;
    QPushButton *exportButton;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *testLabel;
    QLabel *serviceLabel;
    QVBoxLayout *verticalLayout;
    QRadioButton *gdmButton;
    QRadioButton *kdmButton;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *sudoButton;
    QRadioButton *suButton;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *gnomescreensaverButton;
    QRadioButton *lightdmButton;
    QSpacerItem *spacerItem2;
    QPushButton *testButton;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *promptLabel;
    QLineEdit *resultLabel;
    QFrame *frame_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_9;
    QLabel *testLabel1;
    QLabel *testLabel2;
    QSpacerItem *spacerItem3;
    QFrame *line_3;
    QWidget *passwordTab;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_8;
    QPlainTextEdit *hintText_2;
    QPlainTextEdit *warningText_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *directoryLabel;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *pathEdit;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pathButton;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *passwdLabel1;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *passwdLine1;
    QHBoxLayout *horizontalLayout_7;
    QLabel *passwdLabel2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *passwdLine2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *saveButton;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem4;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QFrame *line;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_About;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QStringLiteral("mainWindow"));
        mainWindow->resize(550, 440);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainWindow->sizePolicy().hasHeightForWidth());
        mainWindow->setSizePolicy(sizePolicy);
        mainWindow->setMinimumSize(QSize(550, 440));
        mainWindow->setMaximumSize(QSize(550, 440));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/res/fingerprint-gui.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainWindow->setWindowIcon(icon);
        action_Exit = new QAction(mainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        action_About = new QAction(mainWindow);
        action_About->setObjectName(QStringLiteral("action_About"));
        action_Help = new QAction(mainWindow);
        action_Help->setObjectName(QStringLiteral("action_Help"));
        action_Forum_Online = new QAction(mainWindow);
        action_Forum_Online->setObjectName(QStringLiteral("action_Forum_Online"));
        action_Homepage = new QAction(mainWindow);
        action_Homepage->setObjectName(QStringLiteral("action_Homepage"));
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_2->setContentsMargins(5, 0, 5, 0);
        deviceLabel = new QLabel(centralwidget);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deviceLabel->sizePolicy().hasHeightForWidth());
        deviceLabel->setSizePolicy(sizePolicy1);
        deviceLabel->setMaximumSize(QSize(177, 16777215));
        deviceLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(deviceLabel);

        deviceCombo = new QComboBox(centralwidget);
        deviceCombo->setObjectName(QStringLiteral("deviceCombo"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(deviceCombo->sizePolicy().hasHeightForWidth());
        deviceCombo->setSizePolicy(sizePolicy2);
        deviceCombo->setMinimumSize(QSize(300, 0));

        horizontalLayout_2->addWidget(deviceCombo);

        horizontalSpacer = new QSpacerItem(1, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        rescanButton = new QPushButton(centralwidget);
        rescanButton->setObjectName(QStringLiteral("rescanButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(rescanButton->sizePolicy().hasHeightForWidth());
        rescanButton->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(rescanButton);


        verticalLayout_6->addLayout(horizontalLayout_2);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setSizeConstraint(QLayout::SetNoConstraint);
        hboxLayout->setContentsMargins(5, 0, 5, 0);
        vendornameButton = new QRadioButton(centralwidget);
        vendornameButton->setObjectName(QStringLiteral("vendornameButton"));
        vendornameButton->setChecked(true);

        hboxLayout->addWidget(vendornameButton);

        drivernameButton = new QRadioButton(centralwidget);
        drivernameButton->setObjectName(QStringLiteral("drivernameButton"));

        hboxLayout->addWidget(drivernameButton);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        verticalLayout_6->addLayout(hboxLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy4);
        tabWidget->setMaximumSize(QSize(530, 265));
        devicesTab = new QWidget();
        devicesTab->setObjectName(QStringLiteral("devicesTab"));
        vboxLayout = new QVBoxLayout(devicesTab);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        label = new QLabel(devicesTab);
        label->setObjectName(QStringLiteral("label"));

        vboxLayout1->addWidget(label);

        usbDeviceListWidget = new QListWidget(devicesTab);
        usbDeviceListWidget->setObjectName(QStringLiteral("usbDeviceListWidget"));

        vboxLayout1->addWidget(usbDeviceListWidget);


        vboxLayout->addLayout(vboxLayout1);

        tabWidget->addTab(devicesTab, QString());
        fingerTab = new QWidget();
        fingerTab->setObjectName(QStringLiteral("fingerTab"));
        vboxLayout2 = new QVBoxLayout(fingerTab);
        vboxLayout2->setObjectName(QStringLiteral("vboxLayout2"));
        vboxLayout3 = new QVBoxLayout();
        vboxLayout3->setObjectName(QStringLiteral("vboxLayout3"));
        fingerLabel = new QLabel(fingerTab);
        fingerLabel->setObjectName(QStringLiteral("fingerLabel"));
        fingerLabel->setMaximumSize(QSize(16777215, 20));

        vboxLayout3->addWidget(fingerLabel);

        frame = new QFrame(fingerTab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setEnabled(true);
        sizePolicy4.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy4);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        leftHandPictureLabel = new QLabel(frame);
        leftHandPictureLabel->setObjectName(QStringLiteral("leftHandPictureLabel"));
        leftHandPictureLabel->setGeometry(QRect(20, 20, 131, 154));
        leftHandPictureLabel->setStyleSheet(QStringLiteral("background-color:rgba(0,0,0,0);"));
        leftHandPictureLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/HandL.png")));
        rightHandPictureLabel = new QLabel(frame);
        rightHandPictureLabel->setObjectName(QStringLiteral("rightHandPictureLabel"));
        rightHandPictureLabel->setEnabled(true);
        rightHandPictureLabel->setGeometry(QRect(175, 20, 131, 153));
        rightHandPictureLabel->setStyleSheet(QStringLiteral("background-color:rgba(0,0,0,0);"));
        rightHandPictureLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/HandR.png")));
        lsButton = new QRadioButton(frame);
        lsButton->setObjectName(QStringLiteral("lsButton"));
        lsButton->setGeometry(QRect(31, 38, 14, 14));
        lsButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        lrButton = new QRadioButton(frame);
        lrButton->setObjectName(QStringLiteral("lrButton"));
        lrButton->setGeometry(QRect(45, 23, 14, 14));
        lrButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        lmButton = new QRadioButton(frame);
        lmButton->setObjectName(QStringLiteral("lmButton"));
        lmButton->setGeometry(QRect(65, 16, 14, 14));
        lmButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        lpButton = new QRadioButton(frame);
        lpButton->setObjectName(QStringLiteral("lpButton"));
        lpButton->setGeometry(QRect(86, 25, 14, 14));
        lpButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        lpButton->setChecked(false);
        ltButton = new QRadioButton(frame);
        ltButton->setObjectName(QStringLiteral("ltButton"));
        ltButton->setGeometry(QRect(117, 79, 14, 14));
        ltButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        rtButton = new QRadioButton(frame);
        rtButton->setObjectName(QStringLiteral("rtButton"));
        rtButton->setGeometry(QRect(178, 79, 14, 14));
        rtButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        rtButton->setChecked(false);
        rpButton = new QRadioButton(frame);
        rpButton->setObjectName(QStringLiteral("rpButton"));
        rpButton->setGeometry(QRect(209, 23, 14, 14));
        rpButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        rpButton->setChecked(true);
        rmButton = new QRadioButton(frame);
        rmButton->setObjectName(QStringLiteral("rmButton"));
        rmButton->setGeometry(QRect(229, 15, 14, 14));
        rmButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        rmButton->setChecked(false);
        rrButton = new QRadioButton(frame);
        rrButton->setObjectName(QStringLiteral("rrButton"));
        rrButton->setGeometry(QRect(249, 20, 14, 14));
        rrButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        rrButton->setChecked(false);
        rsButton = new QRadioButton(frame);
        rsButton->setObjectName(QStringLiteral("rsButton"));
        rsButton->setGeometry(QRect(264, 36, 14, 14));
        rsButton->setStyleSheet(QLatin1String("QRadioButton::indicator::unchecked\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked.png);}\n"
"QRadioButton::indicator::checked\n"
"{image: url(:/new/prefix1/res/radiobutton_checked.png);}\n"
"QRadioButton::indicator:unchecked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_hover.png);}\n"
"QRadioButton::indicator:checked:hover\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_hover.png);}\n"
"QRadioButton::indicator:unchecked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_unchecked_pressed.png);}\n"
"QRadioButton::indicator:checked:pressed\n"
"{image: url(:/new/prefix1/res/radiobutton_checked_pressed.png);}\n"
""));
        rsButton->setChecked(false);
        leftHandLabel = new QLabel(frame);
        leftHandLabel->setObjectName(QStringLiteral("leftHandLabel"));
        leftHandLabel->setGeometry(QRect(7, 174, 111, 20));
        leftHandLabel->setStyleSheet(QStringLiteral("background-color:rgba(0,0,0,0);"));
        leftHandLabel->setAlignment(Qt::AlignCenter);
        rightHandLabel = new QLabel(frame);
        rightHandLabel->setObjectName(QStringLiteral("rightHandLabel"));
        rightHandLabel->setGeometry(QRect(190, 174, 101, 18));
        rightHandLabel->setStyleSheet(QStringLiteral("background-color:rgba(0,0,0,0);"));
        rightHandLabel->setAlignment(Qt::AlignCenter);
        currentFingerLabel = new QLabel(frame);
        currentFingerLabel->setObjectName(QStringLiteral("currentFingerLabel"));
        currentFingerLabel->setGeometry(QRect(303, 69, 141, 41));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        currentFingerLabel->setFont(font);
        currentFingerLabel->setStyleSheet(QStringLiteral("background-color:rgba(0,0,0,0);"));
        currentFingerLabel->setFrameShape(QFrame::Panel);
        currentFingerLabel->setFrameShadow(QFrame::Raised);
        currentFingerLabel->setAlignment(Qt::AlignCenter);

        vboxLayout3->addWidget(frame);


        vboxLayout2->addLayout(vboxLayout3);

        tabWidget->addTab(fingerTab, QString());
        scanTab = new QWidget();
        scanTab->setObjectName(QStringLiteral("scanTab"));
        animationLabel = new QLabel(scanTab);
        animationLabel->setObjectName(QStringLiteral("animationLabel"));
        animationLabel->setGeometry(QRect(398, 45, 104, 150));
        animationLabel->setStyleSheet(QStringLiteral("background-color:rgb(0,0,0);"));
        animationLabel->setAlignment(Qt::AlignCenter);
        fingerprintLabel1 = new QLabel(scanTab);
        fingerprintLabel1->setObjectName(QStringLiteral("fingerprintLabel1"));
        fingerprintLabel1->setGeometry(QRect(30, 89, 44, 60));
        fingerprintLabel1->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/Fingerprint.png")));
        fingerprintLabel2 = new QLabel(scanTab);
        fingerprintLabel2->setObjectName(QStringLiteral("fingerprintLabel2"));
        fingerprintLabel2->setGeometry(QRect(100, 89, 44, 60));
        fingerprintLabel2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/Fingerprint.png")));
        fingerprintLabel3 = new QLabel(scanTab);
        fingerprintLabel3->setObjectName(QStringLiteral("fingerprintLabel3"));
        fingerprintLabel3->setGeometry(QRect(170, 89, 44, 60));
        fingerprintLabel3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/Fingerprint.png")));
        acquireLabel = new QLabel(scanTab);
        acquireLabel->setObjectName(QStringLiteral("acquireLabel"));
        acquireLabel->setGeometry(QRect(50, 30, 481, 26));
        acquireLabel->setFont(font);
        fpStatusLabel1 = new QLabel(scanTab);
        fpStatusLabel1->setObjectName(QStringLiteral("fpStatusLabel1"));
        fpStatusLabel1->setGeometry(QRect(0, 170, 100, 18));
        fpStatusLabel1->setAlignment(Qt::AlignCenter);
        fpStatusLabel2 = new QLabel(scanTab);
        fpStatusLabel2->setObjectName(QStringLiteral("fpStatusLabel2"));
        fpStatusLabel2->setGeometry(QRect(70, 170, 100, 18));
        fpStatusLabel2->setAlignment(Qt::AlignCenter);
        fpStatusLabel3 = new QLabel(scanTab);
        fpStatusLabel3->setObjectName(QStringLiteral("fpStatusLabel3"));
        fpStatusLabel3->setGeometry(QRect(140, 170, 100, 18));
        fpStatusLabel3->setAlignment(Qt::AlignCenter);
        fpResultLabel1 = new QLabel(scanTab);
        fpResultLabel1->setObjectName(QStringLiteral("fpResultLabel1"));
        fpResultLabel1->setGeometry(QRect(43, 145, 20, 20));
        fpResultLabel1->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
        fpResultLabel2 = new QLabel(scanTab);
        fpResultLabel2->setObjectName(QStringLiteral("fpResultLabel2"));
        fpResultLabel2->setGeometry(QRect(113, 145, 20, 20));
        fpResultLabel2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
        fpResultLabel3 = new QLabel(scanTab);
        fpResultLabel3->setObjectName(QStringLiteral("fpResultLabel3"));
        fpResultLabel3->setGeometry(QRect(183, 145, 20, 20));
        fpResultLabel3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
        fingerprintLabel4 = new QLabel(scanTab);
        fingerprintLabel4->setObjectName(QStringLiteral("fingerprintLabel4"));
        fingerprintLabel4->setGeometry(QRect(240, 89, 44, 60));
        fingerprintLabel4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/Fingerprint.png")));
        fingerprintLabel5 = new QLabel(scanTab);
        fingerprintLabel5->setObjectName(QStringLiteral("fingerprintLabel5"));
        fingerprintLabel5->setGeometry(QRect(307, 89, 44, 60));
        fingerprintLabel5->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/Fingerprint.png")));
        fpStatusLabel4 = new QLabel(scanTab);
        fpStatusLabel4->setObjectName(QStringLiteral("fpStatusLabel4"));
        fpStatusLabel4->setGeometry(QRect(210, 170, 100, 18));
        fpStatusLabel4->setAlignment(Qt::AlignCenter);
        fpStatusLabel5 = new QLabel(scanTab);
        fpStatusLabel5->setObjectName(QStringLiteral("fpStatusLabel5"));
        fpStatusLabel5->setGeometry(QRect(277, 170, 100, 18));
        fpStatusLabel5->setAlignment(Qt::AlignCenter);
        fpResultLabel5 = new QLabel(scanTab);
        fpResultLabel5->setObjectName(QStringLiteral("fpResultLabel5"));
        fpResultLabel5->setGeometry(QRect(320, 145, 20, 20));
        fpResultLabel5->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
        fpResultLabel4 = new QLabel(scanTab);
        fpResultLabel4->setObjectName(QStringLiteral("fpResultLabel4"));
        fpResultLabel4->setGeometry(QRect(253, 145, 20, 20));
        fpResultLabel4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/fp-error.png")));
        tabWidget->addTab(scanTab, QString());
        settingsTab = new QWidget();
        settingsTab->setObjectName(QStringLiteral("settingsTab"));
        verticalLayout_5 = new QVBoxLayout(settingsTab);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
#ifndef Q_OS_MAC
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
#endif
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setSpacing(0);
        vboxLayout4->setObjectName(QStringLiteral("vboxLayout4"));
        fprintLabel1 = new QLabel(settingsTab);
        fprintLabel1->setObjectName(QStringLiteral("fprintLabel1"));

        vboxLayout4->addWidget(fprintLabel1);

        fprintLabel2 = new QLabel(settingsTab);
        fprintLabel2->setObjectName(QStringLiteral("fprintLabel2"));

        vboxLayout4->addWidget(fprintLabel2);

        noFingerprintsLabel = new QLabel(settingsTab);
        noFingerprintsLabel->setObjectName(QStringLiteral("noFingerprintsLabel"));

        vboxLayout4->addWidget(noFingerprintsLabel);


        horizontalLayout_3->addLayout(vboxLayout4);

        spacerItem1 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(spacerItem1);

        exportButton = new QPushButton(settingsTab);
        exportButton->setObjectName(QStringLiteral("exportButton"));

        horizontalLayout_3->addWidget(exportButton);


        verticalLayout_5->addLayout(horizontalLayout_3);

        line_2 = new QFrame(settingsTab);
        line_2->setObjectName(QStringLiteral("line_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy5);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        testLabel = new QLabel(settingsTab);
        testLabel->setObjectName(QStringLiteral("testLabel"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        testLabel->setFont(font1);

        verticalLayout_4->addWidget(testLabel);

        serviceLabel = new QLabel(settingsTab);
        serviceLabel->setObjectName(QStringLiteral("serviceLabel"));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        serviceLabel->setFont(font2);

        verticalLayout_4->addWidget(serviceLabel);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gdmButton = new QRadioButton(settingsTab);
        gdmButton->setObjectName(QStringLiteral("gdmButton"));
        gdmButton->setChecked(false);

        verticalLayout->addWidget(gdmButton);

        kdmButton = new QRadioButton(settingsTab);
        kdmButton->setObjectName(QStringLiteral("kdmButton"));
        kdmButton->setEnabled(true);
        kdmButton->setChecked(true);

        verticalLayout->addWidget(kdmButton);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        sudoButton = new QRadioButton(settingsTab);
        sudoButton->setObjectName(QStringLiteral("sudoButton"));

        verticalLayout_2->addWidget(sudoButton);

        suButton = new QRadioButton(settingsTab);
        suButton->setObjectName(QStringLiteral("suButton"));

        verticalLayout_2->addWidget(suButton);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gnomescreensaverButton = new QRadioButton(settingsTab);
        gnomescreensaverButton->setObjectName(QStringLiteral("gnomescreensaverButton"));

        verticalLayout_3->addWidget(gnomescreensaverButton);

        lightdmButton = new QRadioButton(settingsTab);
        lightdmButton->setObjectName(QStringLiteral("lightdmButton"));
        lightdmButton->setEnabled(true);

        verticalLayout_3->addWidget(lightdmButton);


        horizontalLayout->addLayout(verticalLayout_3);

        spacerItem2 = new QSpacerItem(13, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem2);

        testButton = new QPushButton(settingsTab);
        testButton->setObjectName(QStringLiteral("testButton"));
        testButton->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout->addWidget(testButton);


        verticalLayout_5->addLayout(horizontalLayout);

        frame_2 = new QFrame(settingsTab);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(4, 0, 4, 0);
        promptLabel = new QLabel(frame_2);
        promptLabel->setObjectName(QStringLiteral("promptLabel"));

        horizontalLayout_5->addWidget(promptLabel);

        resultLabel = new QLineEdit(frame_2);
        resultLabel->setObjectName(QStringLiteral("resultLabel"));
        resultLabel->setMaxLength(256);
        resultLabel->setEchoMode(QLineEdit::Normal);

        horizontalLayout_5->addWidget(resultLabel);


        verticalLayout_5->addWidget(frame_2);

        frame_3 = new QFrame(settingsTab);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(0, 55));
        frame_3->setBaseSize(QSize(0, 0));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget = new QWidget(frame_3);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(110, 0, 301, 51));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        testLabel1 = new QLabel(verticalLayoutWidget);
        testLabel1->setObjectName(QStringLiteral("testLabel1"));
        testLabel1->setFont(font1);

        verticalLayout_9->addWidget(testLabel1);

        testLabel2 = new QLabel(verticalLayoutWidget);
        testLabel2->setObjectName(QStringLiteral("testLabel2"));

        verticalLayout_9->addWidget(testLabel2);


        verticalLayout_5->addWidget(frame_3);

        spacerItem3 = new QSpacerItem(495, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(spacerItem3);

        line_3 = new QFrame(settingsTab);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_3);

        tabWidget->addTab(settingsTab, QString());
        passwordTab = new QWidget();
        passwordTab->setObjectName(QStringLiteral("passwordTab"));
        layoutWidget = new QWidget(passwordTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(-1, 2, 531, 231));
        verticalLayout_8 = new QVBoxLayout(layoutWidget);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        hintText_2 = new QPlainTextEdit(layoutWidget);
        hintText_2->setObjectName(QStringLiteral("hintText_2"));
        hintText_2->setMaximumSize(QSize(519, 85));
        hintText_2->setAcceptDrops(false);
        hintText_2->setFrameShape(QFrame::NoFrame);
        hintText_2->setUndoRedoEnabled(false);

        verticalLayout_8->addWidget(hintText_2);

        warningText_2 = new QPlainTextEdit(layoutWidget);
        warningText_2->setObjectName(QStringLiteral("warningText_2"));
        warningText_2->setMinimumSize(QSize(0, 28));
        warningText_2->setMaximumSize(QSize(520, 20));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(161, 160, 159, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        warningText_2->setPalette(palette);
        warningText_2->setLayoutDirection(Qt::LeftToRight);
        warningText_2->setFrameShape(QFrame::NoFrame);

        verticalLayout_8->addWidget(warningText_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, -1, 5, -1);
        directoryLabel = new QLabel(layoutWidget);
        directoryLabel->setObjectName(QStringLiteral("directoryLabel"));

        horizontalLayout_4->addWidget(directoryLabel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        pathEdit = new QLineEdit(layoutWidget);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));
        pathEdit->setMinimumSize(QSize(340, 0));
        pathEdit->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_4->addWidget(pathEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        pathButton = new QPushButton(layoutWidget);
        pathButton->setObjectName(QStringLiteral("pathButton"));
        pathButton->setMinimumSize(QSize(40, 0));
        pathButton->setMaximumSize(QSize(40, 16777215));
        pathButton->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_4->addWidget(pathButton);


        verticalLayout_8->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(5, -1, 5, -1);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        passwdLabel1 = new QLabel(layoutWidget);
        passwdLabel1->setObjectName(QStringLiteral("passwdLabel1"));

        horizontalLayout_6->addWidget(passwdLabel1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        passwdLine1 = new QLineEdit(layoutWidget);
        passwdLine1->setObjectName(QStringLiteral("passwdLine1"));
        passwdLine1->setMinimumSize(QSize(270, 0));
        passwdLine1->setFocusPolicy(Qt::StrongFocus);
        passwdLine1->setAcceptDrops(false);
        passwdLine1->setEchoMode(QLineEdit::Password);

        horizontalLayout_6->addWidget(passwdLine1);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        passwdLabel2 = new QLabel(layoutWidget);
        passwdLabel2->setObjectName(QStringLiteral("passwdLabel2"));

        horizontalLayout_7->addWidget(passwdLabel2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        passwdLine2 = new QLineEdit(layoutWidget);
        passwdLine2->setObjectName(QStringLiteral("passwdLine2"));
        passwdLine2->setMinimumSize(QSize(270, 0));
        passwdLine2->setFocusPolicy(Qt::StrongFocus);
        passwdLine2->setAcceptDrops(false);
        passwdLine2->setEchoMode(QLineEdit::Password);

        horizontalLayout_7->addWidget(passwdLine2);


        verticalLayout_7->addLayout(horizontalLayout_7);


        horizontalLayout_8->addLayout(verticalLayout_7);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout_8->addWidget(saveButton);


        verticalLayout_8->addLayout(horizontalLayout_8);

        tabWidget->addTab(passwordTab, QString());

        verticalLayout_6->addWidget(tabWidget);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        hboxLayout1->setSizeConstraint(QLayout::SetNoConstraint);
        hboxLayout1->setContentsMargins(5, 0, 5, 0);
        spacerItem4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem4);

        okButton = new QPushButton(centralwidget);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setFocusPolicy(Qt::TabFocus);

        hboxLayout1->addWidget(okButton);

        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout1->addWidget(cancelButton);


        verticalLayout_6->addLayout(hboxLayout1);

        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line);

        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 550, 25));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_About = new QMenu(menubar);
        menu_About->setObjectName(QStringLiteral("menu_About"));
        mainWindow->setMenuBar(menubar);
#ifndef QT_NO_SHORTCUT
        deviceLabel->setBuddy(deviceCombo);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lsButton, lrButton);
        QWidget::setTabOrder(lrButton, lmButton);
        QWidget::setTabOrder(lmButton, lpButton);
        QWidget::setTabOrder(lpButton, ltButton);
        QWidget::setTabOrder(ltButton, rtButton);
        QWidget::setTabOrder(rtButton, rpButton);
        QWidget::setTabOrder(rpButton, rmButton);
        QWidget::setTabOrder(rmButton, rrButton);
        QWidget::setTabOrder(rrButton, rsButton);
        QWidget::setTabOrder(rsButton, rescanButton);
        QWidget::setTabOrder(rescanButton, cancelButton);
        QWidget::setTabOrder(cancelButton, usbDeviceListWidget);
        QWidget::setTabOrder(usbDeviceListWidget, deviceCombo);
        QWidget::setTabOrder(deviceCombo, okButton);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_About->menuAction());
        menu_File->addAction(action_Exit);
        menu_About->addAction(action_Help);
        menu_About->addAction(action_Homepage);
        menu_About->addAction(action_Forum_Online);
        menu_About->addSeparator();
        menu_About->addAction(action_About);
        menu_About->addSeparator();

        retranslateUi(mainWindow);
        QObject::connect(rescanButton, SIGNAL(clicked()), deviceCombo, SLOT(clear()));

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "Setup Fingerprints", Q_NULLPTR));
        action_Exit->setText(QApplication::translate("mainWindow", "&Exit", Q_NULLPTR));
        action_About->setText(QApplication::translate("mainWindow", "&About", Q_NULLPTR));
        action_Help->setText(QApplication::translate("mainWindow", "&Help", Q_NULLPTR));
        action_Forum_Online->setText(QApplication::translate("mainWindow", "&Forum Online", Q_NULLPTR));
        action_Homepage->setText(QApplication::translate("mainWindow", "H&omepage", Q_NULLPTR));
        deviceLabel->setText(QApplication::translate("mainWindow", "Fingerprint Devices:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        deviceCombo->setToolTip(QApplication::translate("mainWindow", "Selection of useable fingerprint devices.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        rescanButton->setToolTip(QApplication::translate("mainWindow", "Scan for devices again.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        rescanButton->setText(QApplication::translate("mainWindow", "&Rescan", Q_NULLPTR));
        vendornameButton->setText(QApplication::translate("mainWindow", "Show Vendor/Device", Q_NULLPTR));
        drivernameButton->setText(QApplication::translate("mainWindow", "Show Drivername", Q_NULLPTR));
        label->setText(QApplication::translate("mainWindow", "Attached USB Devices:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        usbDeviceListWidget->setToolTip(QApplication::translate("mainWindow", "List of discovered USB devices.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(devicesTab), QApplication::translate("mainWindow", "Devices", Q_NULLPTR));
        fingerLabel->setText(QApplication::translate("mainWindow", "Chose Finger to scan", Q_NULLPTR));
        leftHandPictureLabel->setText(QString());
        rightHandPictureLabel->setText(QString());
        lsButton->setText(QString());
        lrButton->setText(QString());
        lmButton->setText(QString());
        lpButton->setText(QString());
        ltButton->setText(QString());
        rtButton->setText(QString());
        rpButton->setText(QString());
        rmButton->setText(QString());
        rrButton->setText(QString());
        rsButton->setText(QString());
        leftHandLabel->setText(QApplication::translate("mainWindow", "Left Hand", Q_NULLPTR));
        rightHandLabel->setText(QApplication::translate("mainWindow", "Right Hand", Q_NULLPTR));
        currentFingerLabel->setText(QApplication::translate("mainWindow", "Right Index", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(fingerTab), QApplication::translate("mainWindow", "Finger", Q_NULLPTR));
        fingerprintLabel1->setText(QString());
        fingerprintLabel2->setText(QString());
        fingerprintLabel3->setText(QString());
        acquireLabel->setText(QApplication::translate("mainWindow", "Please Scan Your Right Index", Q_NULLPTR));
        fpStatusLabel1->setText(QApplication::translate("mainWindow", "waiting...", Q_NULLPTR));
        fpStatusLabel2->setText(QApplication::translate("mainWindow", "try again", Q_NULLPTR));
        fpStatusLabel3->setText(QApplication::translate("mainWindow", "OK", Q_NULLPTR));
        fpResultLabel1->setText(QString());
        fpResultLabel2->setText(QString());
        fpResultLabel3->setText(QString());
        fingerprintLabel4->setText(QString());
        fingerprintLabel5->setText(QString());
        fpStatusLabel4->setText(QApplication::translate("mainWindow", "OK", Q_NULLPTR));
        fpStatusLabel5->setText(QApplication::translate("mainWindow", "OK", Q_NULLPTR));
        fpResultLabel5->setText(QString());
        fpResultLabel4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(scanTab), QApplication::translate("mainWindow", "Scan/Verify", Q_NULLPTR));
        fprintLabel1->setText(QApplication::translate("mainWindow", "Fingerprints are saved to directory \"~/.fprint/\".", Q_NULLPTR));
        fprintLabel2->setText(QApplication::translate("mainWindow", "Export your fingerprints to a file for use in another computer.", Q_NULLPTR));
        noFingerprintsLabel->setText(QApplication::translate("mainWindow", "No Fingerprints yet!", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        exportButton->setToolTip(QApplication::translate("mainWindow", "Save your fingerprints and setting to file.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        exportButton->setText(QApplication::translate("mainWindow", "&Export now", Q_NULLPTR));
        testLabel->setText(QApplication::translate("mainWindow", "Test PAM service", Q_NULLPTR));
        serviceLabel->setText(QApplication::translate("mainWindow", "(Select service to test)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        gdmButton->setToolTip(QApplication::translate("mainWindow", "PAM service to be tested.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        gdmButton->setText(QApplication::translate("mainWindow", "gdm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        kdmButton->setToolTip(QApplication::translate("mainWindow", "PAM service to be tested.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        kdmButton->setText(QApplication::translate("mainWindow", "kdm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        sudoButton->setToolTip(QApplication::translate("mainWindow", "PAM service to be tested.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        sudoButton->setText(QApplication::translate("mainWindow", "sudo", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        suButton->setToolTip(QApplication::translate("mainWindow", "PAM service to be tested.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        suButton->setText(QApplication::translate("mainWindow", "su", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        gnomescreensaverButton->setToolTip(QApplication::translate("mainWindow", "PAM service to be tested.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        gnomescreensaverButton->setText(QApplication::translate("mainWindow", "gnome-screensaver", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lightdmButton->setToolTip(QApplication::translate("mainWindow", "PAM service to be tested.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lightdmButton->setText(QApplication::translate("mainWindow", "lightdm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        testButton->setToolTip(QApplication::translate("mainWindow", "Test selected PAM service.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        testButton->setText(QApplication::translate("mainWindow", "&Test", Q_NULLPTR));
        promptLabel->setText(QApplication::translate("mainWindow", "Swipe your finger or <enter> to abort.", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        resultLabel->setToolTip(QApplication::translate("mainWindow", "Test result is shown here.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        testLabel1->setText(QString());
        testLabel2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(settingsTab), QApplication::translate("mainWindow", "Settings", Q_NULLPTR));
        hintText_2->setPlainText(QApplication::translate("mainWindow", "Hint: You can save your password (encrypted) to some removable media (USB stick). If you login by fingerprint while this media is connected your password is used to unlock gnome-keyring. For more information read the \"Step-by-Step\" manual. ", Q_NULLPTR));
        warningText_2->setPlainText(QApplication::translate("mainWindow", "!!! PLEASE USE THIS ONLY IF YOU UNDERSTAND HOW IT WORKS !!!", Q_NULLPTR));
        directoryLabel->setText(QApplication::translate("mainWindow", "Save to directory:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pathEdit->setToolTip(QApplication::translate("mainWindow", "Path to mounted removable media.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pathButton->setToolTip(QApplication::translate("mainWindow", "Chose path to mounted removable media.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pathButton->setText(QApplication::translate("mainWindow", "...", Q_NULLPTR));
        passwdLabel1->setText(QApplication::translate("mainWindow", "Password:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        passwdLine1->setToolTip(QApplication::translate("mainWindow", "Your login password.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        passwdLabel2->setText(QApplication::translate("mainWindow", "Repeat Password:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        passwdLine2->setToolTip(QApplication::translate("mainWindow", "Your login password again.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QApplication::translate("mainWindow", "Save encrypted login password to removable media.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        saveButton->setText(QApplication::translate("mainWindow", "&Save", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(passwordTab), QApplication::translate("mainWindow", "Password", Q_NULLPTR));
        okButton->setText(QApplication::translate("mainWindow", "&Next", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("mainWindow", "&Cancel", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("mainWindow", "&File", Q_NULLPTR));
        menu_About->setTitle(QApplication::translate("mainWindow", "&Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINGERPRINTGUI_H
