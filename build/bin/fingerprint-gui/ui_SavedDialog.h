/********************************************************************************
** Form generated from reading UI file 'SavedDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEDDIALOG_H
#define UI_SAVEDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SavedDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *modeLabel;
    QLabel *label_2;
    QSpacerItem *spacerItem;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *fp_img;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *yesButton;
    QPushButton *noButton;

    void setupUi(QDialog *SavedDialog)
    {
        if (SavedDialog->objectName().isEmpty())
            SavedDialog->setObjectName(QStringLiteral("SavedDialog"));
        SavedDialog->setWindowModality(Qt::ApplicationModal);
        SavedDialog->resize(236, 271);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/res/fingerprint-gui.png"), QSize(), QIcon::Normal, QIcon::Off);
        SavedDialog->setWindowIcon(icon);
        vboxLayout = new QVBoxLayout(SavedDialog);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(0);
        vboxLayout1->setContentsMargins(5, 5, 5, 5);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        modeLabel = new QLabel(SavedDialog);
        modeLabel->setObjectName(QStringLiteral("modeLabel"));

        vboxLayout1->addWidget(modeLabel);

        label_2 = new QLabel(SavedDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        vboxLayout1->addWidget(label_2);


        hboxLayout->addLayout(vboxLayout1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        fp_img = new QLabel(SavedDialog);
        fp_img->setObjectName(QStringLiteral("fp_img"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(fp_img->sizePolicy().hasHeightForWidth());
        fp_img->setSizePolicy(sizePolicy);
        fp_img->setMinimumSize(QSize(0, 0));
        fp_img->setMaximumSize(QSize(104, 150));
        fp_img->setStyleSheet(QStringLiteral("background-color:rgb(0,0,0);"));
        fp_img->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(fp_img);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        vboxLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(verticalSpacer);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setContentsMargins(5, 5, 5, 5);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        yesButton = new QPushButton(SavedDialog);
        yesButton->setObjectName(QStringLiteral("yesButton"));

        hboxLayout1->addWidget(yesButton);

        noButton = new QPushButton(SavedDialog);
        noButton->setObjectName(QStringLiteral("noButton"));

        hboxLayout1->addWidget(noButton);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(SavedDialog);

        QMetaObject::connectSlotsByName(SavedDialog);
    } // setupUi

    void retranslateUi(QDialog *SavedDialog)
    {
        SavedDialog->setWindowTitle(QApplication::translate("SavedDialog", "Fingerprint saved", Q_NULLPTR));
        modeLabel->setText(QApplication::translate("SavedDialog", "Fingerprint was saved to disk.", Q_NULLPTR));
        label_2->setText(QApplication::translate("SavedDialog", "Select another finger?", Q_NULLPTR));
        yesButton->setText(QApplication::translate("SavedDialog", "&Yes", Q_NULLPTR));
        noButton->setText(QApplication::translate("SavedDialog", "&No", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SavedDialog: public Ui_SavedDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEDDIALOG_H
