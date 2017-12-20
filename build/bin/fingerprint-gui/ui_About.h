/********************************************************************************
** Form generated from reading UI file 'About.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *iconLabel;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *nameLabel;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *versionLabel;
    QFrame *line_2;
    QPlainTextEdit *textEdit;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *copyrightLabel;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *homeButton;
    QFrame *line;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCommandLinkButton *donateButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *licenseButton;
    QPushButton *okButton;
    QFrame *frame_8;
    QLabel *bitcoinLabel;
    QFrame *frame_7;
    QPushButton *bitcoinButton;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QStringLiteral("AboutDialog"));
        AboutDialog->setWindowModality(Qt::ApplicationModal);
        AboutDialog->resize(394, 313);
        QIcon icon;
        icon.addFile(QStringLiteral(":/newPrefix/res/fingerprint-gui.png"), QSize(), QIcon::Normal, QIcon::Off);
        AboutDialog->setWindowIcon(icon);
        AboutDialog->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        verticalLayout = new QVBoxLayout(AboutDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_2 = new QFrame(AboutDialog);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_2->setLineWidth(0);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        iconLabel = new QLabel(frame_2);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        iconLabel->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        iconLabel->setPixmap(QPixmap(QString::fromUtf8(":/newPrefix/res/fingerprint-gui.png")));
        iconLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(iconLabel);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(AboutDialog);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Plain);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        nameLabel = new QLabel(frame_3);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        nameLabel->setFont(font);
        nameLabel->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        nameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(nameLabel);


        verticalLayout->addWidget(frame_3);

        frame_5 = new QFrame(AboutDialog);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::NoFrame);
        frame_5->setFrameShadow(QFrame::Plain);
        horizontalLayout_6 = new QHBoxLayout(frame_5);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 0, -1, 0);
        versionLabel = new QLabel(frame_5);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));
        versionLabel->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        versionLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(versionLabel);


        verticalLayout->addWidget(frame_5);

        line_2 = new QFrame(AboutDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        textEdit = new QPlainTextEdit(AboutDialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(60);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMinimumSize(QSize(0, 60));
        textEdit->setMaximumSize(QSize(16777215, 60));
        QPalette palette;
        QBrush brush(QColor(237, 236, 235, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        textEdit->setPalette(palette);
        textEdit->setFocusPolicy(Qt::NoFocus);
        textEdit->setAcceptDrops(false);
        textEdit->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        textEdit->setFrameShape(QFrame::NoFrame);
        textEdit->setFrameShadow(QFrame::Plain);
        textEdit->setLineWidth(0);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setUndoRedoEnabled(false);
        textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(textEdit);

        frame_4 = new QFrame(AboutDialog);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::NoFrame);
        frame_4->setFrameShadow(QFrame::Plain);
        frame_4->setLineWidth(0);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, 0);
        copyrightLabel = new QLabel(frame_4);
        copyrightLabel->setObjectName(QStringLiteral("copyrightLabel"));
        copyrightLabel->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        copyrightLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(copyrightLabel);


        verticalLayout->addWidget(frame_4);

        frame_6 = new QFrame(AboutDialog);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Plain);
        frame_6->setLineWidth(0);
        horizontalLayout_5 = new QHBoxLayout(frame_6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, 0);
        homeButton = new QPushButton(frame_6);
        homeButton->setObjectName(QStringLiteral("homeButton"));
        homeButton->setCursor(QCursor(Qt::PointingHandCursor));
        homeButton->setFlat(true);

        horizontalLayout_5->addWidget(homeButton);


        verticalLayout->addWidget(frame_6);

        line = new QFrame(AboutDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        frame = new QFrame(AboutDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        donateButton = new QCommandLinkButton(frame);
        donateButton->setObjectName(QStringLiteral("donateButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(donateButton->sizePolicy().hasHeightForWidth());
        donateButton->setSizePolicy(sizePolicy1);
        donateButton->setMinimumSize(QSize(100, 0));
        donateButton->setMaximumSize(QSize(100, 16777215));
        donateButton->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/newPrefix/res/Green_dollar.png"), QSize(), QIcon::Normal, QIcon::Off);
        donateButton->setIcon(icon1);
        donateButton->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(donateButton);

        horizontalSpacer = new QSpacerItem(77, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        licenseButton = new QPushButton(frame);
        licenseButton->setObjectName(QStringLiteral("licenseButton"));
        licenseButton->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/newPrefix/res/gplv3-88x31.png"), QSize(), QIcon::Normal, QIcon::Off);
        licenseButton->setIcon(icon2);
        licenseButton->setIconSize(QSize(60, 21));

        horizontalLayout->addWidget(licenseButton);

        okButton = new QPushButton(frame);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));

        horizontalLayout->addWidget(okButton);


        verticalLayout->addWidget(frame);

        frame_8 = new QFrame(AboutDialog);
        frame_8->setObjectName(QStringLiteral("frame_8"));
        frame_8->setMinimumSize(QSize(0, 19));
        frame_8->setFrameShape(QFrame::NoFrame);
        frame_8->setFrameShadow(QFrame::Plain);
        bitcoinLabel = new QLabel(frame_8);
        bitcoinLabel->setObjectName(QStringLiteral("bitcoinLabel"));
        bitcoinLabel->setGeometry(QRect(0, 0, 371, 17));
        bitcoinLabel->setLocale(QLocale(QLocale::C, QLocale::AnyCountry));
        bitcoinLabel->setAlignment(Qt::AlignCenter);
        bitcoinLabel->setMargin(0);
        bitcoinLabel->setIndent(-1);

        verticalLayout->addWidget(frame_8);

        frame_7 = new QFrame(AboutDialog);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setMinimumSize(QSize(0, 35));
        frame_7->setFrameShape(QFrame::NoFrame);
        frame_7->setFrameShadow(QFrame::Plain);
        frame_7->setLineWidth(0);
        bitcoinButton = new QPushButton(frame_7);
        bitcoinButton->setObjectName(QStringLiteral("bitcoinButton"));
        bitcoinButton->setGeometry(QRect(9, 0, 358, 31));
        bitcoinButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/newPrefix/res/bitcoin.png"), QSize(), QIcon::Normal, QIcon::Off);
        bitcoinButton->setIcon(icon3);
        bitcoinButton->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(frame_7);


        retranslateUi(AboutDialog);
        QObject::connect(okButton, SIGNAL(clicked()), AboutDialog, SLOT(reject()));

        homeButton->setDefault(false);


        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "About Fingerprint GUI", Q_NULLPTR));
        iconLabel->setText(QString());
        nameLabel->setText(QApplication::translate("AboutDialog", "Fingerprint GUI", Q_NULLPTR));
        versionLabel->setText(QApplication::translate("AboutDialog", "Version: 0.6", Q_NULLPTR));
        textEdit->setPlainText(QApplication::translate("AboutDialog", "Fingerprint GUI is a collection of frontend tools for Linux to enable fingerprint authentication, identification and login.", Q_NULLPTR));
        copyrightLabel->setText(QApplication::translate("AboutDialog", "(C) 2008-2014 Wolfgang Ullrich", Q_NULLPTR));
        homeButton->setText(QApplication::translate("AboutDialog", "http://www.ullrich-online.cc/fingerprint", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        donateButton->setToolTip(QApplication::translate("AboutDialog", "Donate via PayPal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        donateButton->setText(QApplication::translate("AboutDialog", "&Donate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        licenseButton->setToolTip(QApplication::translate("AboutDialog", "Fingerprint GUI is licensed under GPL", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        licenseButton->setText(QApplication::translate("AboutDialog", "&License", Q_NULLPTR));
        okButton->setText(QApplication::translate("AboutDialog", "&OK", Q_NULLPTR));
        bitcoinLabel->setText(QApplication::translate("AboutDialog", "Donate a Bitcoin to the address below (push to copy):", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        bitcoinButton->setToolTip(QApplication::translate("AboutDialog", "Copy to clipboard", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        bitcoinButton->setText(QApplication::translate("AboutDialog", "1LsaAggcE8rgB3Hkrxv2adEYEqDkbVSHFd", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
