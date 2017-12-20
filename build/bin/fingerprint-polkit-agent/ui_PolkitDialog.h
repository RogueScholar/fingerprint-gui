/********************************************************************************
** Form generated from reading UI file 'PolkitDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLKITDIALOG_H
#define UI_POLKITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PolkitDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *detailsButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QHBoxLayout *horizontalLayoutDetails;
    QVBoxLayout *verticalContent;
    QLabel *headerLabel;
    QLabel *contentLabel;
    QComboBox *userCombobox;
    QHBoxLayout *horizontalLayoutPassword;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QHBoxLayout *horizontalError;
    QLabel *errorLabel;
    QHBoxLayout *horizontalLayoutFingerprint;
    QLabel *iconLabel;

    void setupUi(QWidget *PolkitDialog)
    {
        if (PolkitDialog->objectName().isEmpty())
            PolkitDialog->setObjectName(QStringLiteral("PolkitDialog"));
        PolkitDialog->resize(334, 204);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PolkitDialog->sizePolicy().hasHeightForWidth());
        PolkitDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/res/fingerprint-gui.png"), QSize(), QIcon::Normal, QIcon::Off);
        PolkitDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(PolkitDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        detailsButton = new QPushButton(PolkitDialog);
        detailsButton->setObjectName(QStringLiteral("detailsButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(detailsButton->sizePolicy().hasHeightForWidth());
        detailsButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(detailsButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(PolkitDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        sizePolicy1.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(cancelButton);

        okButton = new QPushButton(PolkitDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        sizePolicy1.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy1);
        okButton->setAutoDefault(false);

        horizontalLayout->addWidget(okButton);


        gridLayout->addLayout(horizontalLayout, 8, 0, 1, 4);

        horizontalLayoutDetails = new QHBoxLayout();
        horizontalLayoutDetails->setObjectName(QStringLiteral("horizontalLayoutDetails"));
        horizontalLayoutDetails->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayoutDetails->setContentsMargins(0, 0, -1, -1);

        gridLayout->addLayout(horizontalLayoutDetails, 7, 0, 1, 4);

        verticalContent = new QVBoxLayout();
        verticalContent->setSpacing(6);
        verticalContent->setObjectName(QStringLiteral("verticalContent"));
        verticalContent->setSizeConstraint(QLayout::SetNoConstraint);
        headerLabel = new QLabel(PolkitDialog);
        headerLabel->setObjectName(QStringLiteral("headerLabel"));
        sizePolicy.setHeightForWidth(headerLabel->sizePolicy().hasHeightForWidth());
        headerLabel->setSizePolicy(sizePolicy);
        headerLabel->setWordWrap(true);

        verticalContent->addWidget(headerLabel);

        contentLabel = new QLabel(PolkitDialog);
        contentLabel->setObjectName(QStringLiteral("contentLabel"));
        sizePolicy.setHeightForWidth(contentLabel->sizePolicy().hasHeightForWidth());
        contentLabel->setSizePolicy(sizePolicy);
        contentLabel->setWordWrap(true);

        verticalContent->addWidget(contentLabel);


        gridLayout->addLayout(verticalContent, 0, 1, 2, 3);

        userCombobox = new QComboBox(PolkitDialog);
        userCombobox->setObjectName(QStringLiteral("userCombobox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(userCombobox->sizePolicy().hasHeightForWidth());
        userCombobox->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(userCombobox, 2, 0, 1, 4);

        horizontalLayoutPassword = new QHBoxLayout();
        horizontalLayoutPassword->setObjectName(QStringLiteral("horizontalLayoutPassword"));
        horizontalLayoutPassword->setSizeConstraint(QLayout::SetNoConstraint);
        passwordLabel = new QLabel(PolkitDialog);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(passwordLabel->sizePolicy().hasHeightForWidth());
        passwordLabel->setSizePolicy(sizePolicy3);

        horizontalLayoutPassword->addWidget(passwordLabel);

        passwordEdit = new QLineEdit(PolkitDialog);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        sizePolicy2.setHeightForWidth(passwordEdit->sizePolicy().hasHeightForWidth());
        passwordEdit->setSizePolicy(sizePolicy2);
        passwordEdit->setMinimumSize(QSize(150, 0));
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setProperty("passwordMode", QVariant(true));

        horizontalLayoutPassword->addWidget(passwordEdit);


        gridLayout->addLayout(horizontalLayoutPassword, 3, 0, 1, 4);

        horizontalError = new QHBoxLayout();
        horizontalError->setObjectName(QStringLiteral("horizontalError"));
        horizontalError->setSizeConstraint(QLayout::SetMaximumSize);
        errorLabel = new QLabel(PolkitDialog);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));
        errorLabel->setEnabled(true);
        sizePolicy2.setHeightForWidth(errorLabel->sizePolicy().hasHeightForWidth());
        errorLabel->setSizePolicy(sizePolicy2);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        errorLabel->setFont(font);

        horizontalError->addWidget(errorLabel);


        gridLayout->addLayout(horizontalError, 5, 0, 1, 4);

        horizontalLayoutFingerprint = new QHBoxLayout();
        horizontalLayoutFingerprint->setSpacing(0);
        horizontalLayoutFingerprint->setObjectName(QStringLiteral("horizontalLayoutFingerprint"));
        horizontalLayoutFingerprint->setSizeConstraint(QLayout::SetMaximumSize);

        gridLayout->addLayout(horizontalLayoutFingerprint, 4, 0, 1, 4);

        iconLabel = new QLabel(PolkitDialog);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        sizePolicy3.setHeightForWidth(iconLabel->sizePolicy().hasHeightForWidth());
        iconLabel->setSizePolicy(sizePolicy3);
        iconLabel->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/res/fingerprint-gui.png")));
        iconLabel->setWordWrap(false);

        gridLayout->addWidget(iconLabel, 0, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        headerLabel->setBuddy(passwordEdit);
        passwordLabel->setBuddy(passwordEdit);
        iconLabel->setBuddy(passwordEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(PolkitDialog);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(PolkitDialog);
    } // setupUi

    void retranslateUi(QWidget *PolkitDialog)
    {
        PolkitDialog->setWindowTitle(QApplication::translate("PolkitDialog", "Authenticate", Q_NULLPTR));
        detailsButton->setText(QApplication::translate("PolkitDialog", "&Details >>", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("PolkitDialog", "&Cancel", Q_NULLPTR));
        okButton->setText(QApplication::translate("PolkitDialog", "&OK", Q_NULLPTR));
        headerLabel->setText(QString());
        contentLabel->setText(QString());
        passwordLabel->setText(QApplication::translate("PolkitDialog", "Password:", Q_NULLPTR));
        errorLabel->setText(QApplication::translate("PolkitDialog", "Error Message", Q_NULLPTR));
        iconLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PolkitDialog: public Ui_PolkitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLKITDIALOG_H
