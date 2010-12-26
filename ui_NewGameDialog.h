/********************************************************************************
** Form generated from reading UI file 'NewGameDialog.ui'
**
** Created: Mon Dec 27 00:22:04 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGAMEDIALOG_H
#define UI_NEWGAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewGameDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *rowText;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *mineText;
    QLineEdit *columnText;
    QLabel *label;

    void setupUi(QDialog *NewGameDialog)
    {
        if (NewGameDialog->objectName().isEmpty())
            NewGameDialog->setObjectName(QString::fromUtf8("NewGameDialog"));
        NewGameDialog->resize(289, 197);
        buttonBox = new QDialogButtonBox(NewGameDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 150, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(NewGameDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 246, 118));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        rowText = new QLineEdit(layoutWidget);
        rowText->setObjectName(QString::fromUtf8("rowText"));

        gridLayout->addWidget(rowText, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        mineText = new QLineEdit(layoutWidget);
        mineText->setObjectName(QString::fromUtf8("mineText"));

        gridLayout->addWidget(mineText, 2, 1, 1, 1);

        columnText = new QLineEdit(layoutWidget);
        columnText->setObjectName(QString::fromUtf8("columnText"));

        gridLayout->addWidget(columnText, 1, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        QWidget::setTabOrder(rowText, columnText);
        QWidget::setTabOrder(columnText, mineText);
        QWidget::setTabOrder(mineText, buttonBox);

        retranslateUi(NewGameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewGameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewGameDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewGameDialog);
    } // setupUi

    void retranslateUi(QDialog *NewGameDialog)
    {
        NewGameDialog->setWindowTitle(QApplication::translate("NewGameDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewGameDialog", "Column:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewGameDialog", "Mine Number:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewGameDialog", "Row:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewGameDialog: public Ui_NewGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGAMEDIALOG_H
