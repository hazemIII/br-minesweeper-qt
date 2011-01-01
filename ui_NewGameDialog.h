/********************************************************************************
** Form generated from reading UI file 'NewGameDialog.ui'
**
** Created: Sat Jan 1 11:25:58 2011
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
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_NewGameDialog
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *basicGroupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *rowText;
    QLabel *label_2;
    QLineEdit *columnText;
    QLabel *label_3;
    QLineEdit *mineText;
    QGroupBox *serverGroupBox;
    QGridLayout *gridLayout_3;
    QLineEdit *serverAddress;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *portNumber;
    QGroupBox *selectPlayerGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QComboBox *player1ComboBox;
    QLabel *label_5;
    QComboBox *player2ComboBox;
    QDialogButtonBox *buttonBox;
    QRadioButton *netMode;
    QRadioButton *normalMode;
    QRadioButton *competeMode;

    void setupUi(QDialog *NewGameDialog)
    {
        if (NewGameDialog->objectName().isEmpty())
            NewGameDialog->setObjectName(QString::fromUtf8("NewGameDialog"));
        NewGameDialog->resize(322, 483);
        gridLayout_4 = new QGridLayout(NewGameDialog);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        basicGroupBox = new QGroupBox(NewGameDialog);
        basicGroupBox->setObjectName(QString::fromUtf8("basicGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(basicGroupBox->sizePolicy().hasHeightForWidth());
        basicGroupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(basicGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(basicGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        rowText = new QLineEdit(basicGroupBox);
        rowText->setObjectName(QString::fromUtf8("rowText"));

        gridLayout->addWidget(rowText, 0, 1, 1, 1);

        label_2 = new QLabel(basicGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        columnText = new QLineEdit(basicGroupBox);
        columnText->setObjectName(QString::fromUtf8("columnText"));

        gridLayout->addWidget(columnText, 1, 1, 1, 1);

        label_3 = new QLabel(basicGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        mineText = new QLineEdit(basicGroupBox);
        mineText->setObjectName(QString::fromUtf8("mineText"));

        gridLayout->addWidget(mineText, 2, 1, 1, 1);


        gridLayout_4->addWidget(basicGroupBox, 0, 0, 1, 3);

        serverGroupBox = new QGroupBox(NewGameDialog);
        serverGroupBox->setObjectName(QString::fromUtf8("serverGroupBox"));
        gridLayout_3 = new QGridLayout(serverGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        serverAddress = new QLineEdit(serverGroupBox);
        serverAddress->setObjectName(QString::fromUtf8("serverAddress"));

        gridLayout_3->addWidget(serverAddress, 0, 1, 1, 1);

        label_6 = new QLabel(serverGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        label_7 = new QLabel(serverGroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        portNumber = new QLineEdit(serverGroupBox);
        portNumber->setObjectName(QString::fromUtf8("portNumber"));

        gridLayout_3->addWidget(portNumber, 1, 1, 1, 1);


        gridLayout_4->addWidget(serverGroupBox, 3, 0, 1, 3);

        selectPlayerGroupBox = new QGroupBox(NewGameDialog);
        selectPlayerGroupBox->setObjectName(QString::fromUtf8("selectPlayerGroupBox"));
        sizePolicy.setHeightForWidth(selectPlayerGroupBox->sizePolicy().hasHeightForWidth());
        selectPlayerGroupBox->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(selectPlayerGroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(selectPlayerGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        player1ComboBox = new QComboBox(selectPlayerGroupBox);
        player1ComboBox->setObjectName(QString::fromUtf8("player1ComboBox"));

        gridLayout_2->addWidget(player1ComboBox, 0, 1, 1, 1);

        label_5 = new QLabel(selectPlayerGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        player2ComboBox = new QComboBox(selectPlayerGroupBox);
        player2ComboBox->setObjectName(QString::fromUtf8("player2ComboBox"));

        gridLayout_2->addWidget(player2ComboBox, 1, 1, 1, 1);


        gridLayout_4->addWidget(selectPlayerGroupBox, 4, 0, 1, 3);

        buttonBox = new QDialogButtonBox(NewGameDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 9, 0, 1, 3);

        netMode = new QRadioButton(NewGameDialog);
        netMode->setObjectName(QString::fromUtf8("netMode"));

        gridLayout_4->addWidget(netMode, 8, 0, 1, 1);

        normalMode = new QRadioButton(NewGameDialog);
        normalMode->setObjectName(QString::fromUtf8("normalMode"));
        normalMode->setChecked(true);

        gridLayout_4->addWidget(normalMode, 6, 0, 1, 1);

        competeMode = new QRadioButton(NewGameDialog);
        competeMode->setObjectName(QString::fromUtf8("competeMode"));

        gridLayout_4->addWidget(competeMode, 6, 1, 1, 1);

        QWidget::setTabOrder(rowText, columnText);
        QWidget::setTabOrder(columnText, mineText);
        QWidget::setTabOrder(mineText, buttonBox);

        retranslateUi(NewGameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewGameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewGameDialog, SLOT(reject()));
        QObject::connect(competeMode, SIGNAL(toggled(bool)), selectPlayerGroupBox, SLOT(setVisible(bool)));
        QObject::connect(netMode, SIGNAL(toggled(bool)), serverGroupBox, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(NewGameDialog);
    } // setupUi

    void retranslateUi(QDialog *NewGameDialog)
    {
        NewGameDialog->setWindowTitle(QApplication::translate("NewGameDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        basicGroupBox->setTitle(QApplication::translate("NewGameDialog", "Basic", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewGameDialog", "Row:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewGameDialog", "Column:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewGameDialog", "Mine Number:", 0, QApplication::UnicodeUTF8));
        serverGroupBox->setTitle(QApplication::translate("NewGameDialog", "Server", 0, QApplication::UnicodeUTF8));
        serverAddress->setText(QApplication::translate("NewGameDialog", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewGameDialog", "Server IP:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("NewGameDialog", "Port:", 0, QApplication::UnicodeUTF8));
        portNumber->setText(QApplication::translate("NewGameDialog", "9527", 0, QApplication::UnicodeUTF8));
        selectPlayerGroupBox->setTitle(QApplication::translate("NewGameDialog", "Select Player", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewGameDialog", "Player1:", 0, QApplication::UnicodeUTF8));
        player1ComboBox->clear();
        player1ComboBox->insertItems(0, QStringList()
         << QApplication::translate("NewGameDialog", "Human", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewGameDialog", "AI", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("NewGameDialog", "Player2", 0, QApplication::UnicodeUTF8));
        player2ComboBox->clear();
        player2ComboBox->insertItems(0, QStringList()
         << QApplication::translate("NewGameDialog", "Human", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("NewGameDialog", "AI", 0, QApplication::UnicodeUTF8)
        );
        netMode->setText(QApplication::translate("NewGameDialog", "net mode", 0, QApplication::UnicodeUTF8));
        normalMode->setText(QApplication::translate("NewGameDialog", "normal mode", 0, QApplication::UnicodeUTF8));
        competeMode->setText(QApplication::translate("NewGameDialog", "compete mode", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewGameDialog: public Ui_NewGameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGAMEDIALOG_H
