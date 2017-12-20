/********************************************************************************
** Form generated from reading UI file 'PolkitDetails.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLKITDETAILS_H
#define UI_POLKITDETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PolkitDetails
{
public:
    QGridLayout *gridLayout;
    QLabel *appLabel;
    QLabel *actionLabel;
    QLabel *vendorLabel;
    QLabel *vendorUrlLabel;
    QLabel *actionTextLabel;
    QFrame *line;
    QLabel *appTextLabel;

    void setupUi(QWidget *PolkitDetails)
    {
        if (PolkitDetails->objectName().isEmpty())
            PolkitDetails->setObjectName(QStringLiteral("PolkitDetails"));
        PolkitDetails->resize(273, 90);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PolkitDetails->sizePolicy().hasHeightForWidth());
        PolkitDetails->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(PolkitDetails);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        appLabel = new QLabel(PolkitDetails);
        appLabel->setObjectName(QStringLiteral("appLabel"));

        gridLayout->addWidget(appLabel, 1, 0, 1, 1);

        actionLabel = new QLabel(PolkitDetails);
        actionLabel->setObjectName(QStringLiteral("actionLabel"));

        gridLayout->addWidget(actionLabel, 2, 0, 1, 1);

        vendorLabel = new QLabel(PolkitDetails);
        vendorLabel->setObjectName(QStringLiteral("vendorLabel"));

        gridLayout->addWidget(vendorLabel, 3, 0, 1, 1);

        vendorUrlLabel = new QLabel(PolkitDetails);
        vendorUrlLabel->setObjectName(QStringLiteral("vendorUrlLabel"));
        vendorUrlLabel->setOpenExternalLinks(true);
        vendorUrlLabel->setProperty("useTips", QVariant(true));

        gridLayout->addWidget(vendorUrlLabel, 3, 1, 1, 3);

        actionTextLabel = new QLabel(PolkitDetails);
        actionTextLabel->setObjectName(QStringLiteral("actionTextLabel"));
        actionTextLabel->setProperty("useTips", QVariant(true));

        gridLayout->addWidget(actionTextLabel, 2, 1, 1, 3);

        line = new QFrame(PolkitDetails);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 0, 1, 4);

        appTextLabel = new QLabel(PolkitDetails);
        appTextLabel->setObjectName(QStringLiteral("appTextLabel"));

        gridLayout->addWidget(appTextLabel, 1, 1, 1, 3);


        retranslateUi(PolkitDetails);

        QMetaObject::connectSlotsByName(PolkitDetails);
    } // setupUi

    void retranslateUi(QWidget *PolkitDetails)
    {
        appLabel->setText(QApplication::translate("PolkitDetails", "Application:", Q_NULLPTR));
        actionLabel->setText(QApplication::translate("PolkitDetails", "Action:", Q_NULLPTR));
        vendorLabel->setText(QApplication::translate("PolkitDetails", "Vendor:", Q_NULLPTR));
        vendorUrlLabel->setText(QApplication::translate("PolkitDetails", "Vendor:", Q_NULLPTR));
        vendorUrlLabel->setProperty("tipText", QVariant(QString()));
        actionTextLabel->setText(QApplication::translate("PolkitDetails", "Action:", Q_NULLPTR));
        actionTextLabel->setProperty("tipText", QVariant(QString()));
        appTextLabel->setText(QApplication::translate("PolkitDetails", "Application:", Q_NULLPTR));
        Q_UNUSED(PolkitDetails);
    } // retranslateUi

};

namespace Ui {
    class PolkitDetails: public Ui_PolkitDetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLKITDETAILS_H
