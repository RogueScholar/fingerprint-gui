/********************************************************************************
** Form generated from reading UI file 'ExistDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXISTDIALOG_H
#define UI_EXISTDIALOG_H

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

class Ui_ExistDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *fingerLabel;
    QLabel *label_2;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QPushButton *verifyButton;
    QPushButton *acquireButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ExistDialog)
    {
        if (ExistDialog->objectName().isEmpty())
            ExistDialog->setObjectName(QStringLiteral("ExistDialog"));
        ExistDialog->setWindowModality(Qt::ApplicationModal);
        ExistDialog->resize(433, 116);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/res/fingerprint-gui.png"), QSize(), QIcon::Normal, QIcon::Off);
        ExistDialog->setWindowIcon(icon);
        vboxLayout = new QVBoxLayout(ExistDialog);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(0);
        vboxLayout1->setContentsMargins(5, 5, 5, 5);
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        fingerLabel = new QLabel(ExistDialog);
        fingerLabel->setObjectName(QStringLiteral("fingerLabel"));

        vboxLayout1->addWidget(fingerLabel);

        label_2 = new QLabel(ExistDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        vboxLayout1->addWidget(label_2);


        hboxLayout->addLayout(vboxLayout1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem1);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(5, 5, 5, 5);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        verifyButton = new QPushButton(ExistDialog);
        verifyButton->setObjectName(QStringLiteral("verifyButton"));

        hboxLayout1->addWidget(verifyButton);

        acquireButton = new QPushButton(ExistDialog);
        acquireButton->setObjectName(QStringLiteral("acquireButton"));

        hboxLayout1->addWidget(acquireButton);

        cancelButton = new QPushButton(ExistDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout1->addWidget(cancelButton);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(ExistDialog);

        QMetaObject::connectSlotsByName(ExistDialog);
    } // setupUi

    void retranslateUi(QDialog *ExistDialog)
    {
        ExistDialog->setWindowTitle(QApplication::translate("ExistDialog", "Fingerprint exists", Q_NULLPTR));
        fingerLabel->setText(QApplication::translate("ExistDialog", "A fingerprint for Left Little exists already.", Q_NULLPTR));
        label_2->setText(QApplication::translate("ExistDialog", "You can verify this fingerprint or remove it and acquire new.", Q_NULLPTR));
        verifyButton->setText(QApplication::translate("ExistDialog", "&Verify", Q_NULLPTR));
        acquireButton->setText(QApplication::translate("ExistDialog", "&Acquire new", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("ExistDialog", "&Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ExistDialog: public Ui_ExistDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXISTDIALOG_H
