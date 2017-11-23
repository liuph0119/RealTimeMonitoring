/********************************************************************************
** Form generated from reading UI file 'moyuclientdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOYUCLIENTDLG_H
#define UI_MOYUCLIENTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MoYuClientClass
{
public:
    QAction *actionStart;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_state;
    QPushButton *btn_police;
    QMenuBar *menuBar;
    QMenu *menuSomething;

    void setupUi(QMainWindow *MoYuClientClass)
    {
        if (MoYuClientClass->objectName().isEmpty())
            MoYuClientClass->setObjectName(QStringLiteral("MoYuClientClass"));
        MoYuClientClass->resize(320, 330);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MoYuClientClass->sizePolicy().hasHeightForWidth());
        MoYuClientClass->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/fish.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MoYuClientClass->setWindowIcon(icon);
        actionStart = new QAction(MoYuClientClass);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("icon/start.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon1);
        actionExit = new QAction(MoYuClientClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("icon/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionAbout = new QAction(MoYuClientClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("icon/help.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon3);
        centralWidget = new QWidget(MoYuClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 240, 240));
        label_state = new QLabel(centralWidget);
        label_state->setObjectName(QStringLiteral("label_state"));
        label_state->setGeometry(QRect(10, 276, 301, 20));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        label_state->setFont(font);
        btn_police = new QPushButton(centralWidget);
        btn_police->setObjectName(QStringLiteral("btn_police"));
        btn_police->setGeometry(QRect(292, 0, 31, 31));
        QIcon icon4;
        icon4.addFile(QStringLiteral("icon/police.ico"), QSize(), QIcon::Normal, QIcon::Off);
        btn_police->setIcon(icon4);
        MoYuClientClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MoYuClientClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 320, 26));
        menuSomething = new QMenu(menuBar);
        menuSomething->setObjectName(QStringLiteral("menuSomething"));
        menuSomething->setIcon(icon);
        MoYuClientClass->setMenuBar(menuBar);

        menuBar->addAction(menuSomething->menuAction());
        menuSomething->addAction(actionStart);
        menuSomething->addAction(actionAbout);
        menuSomething->addAction(actionExit);

        retranslateUi(MoYuClientClass);

        QMetaObject::connectSlotsByName(MoYuClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *MoYuClientClass)
    {
        MoYuClientClass->setWindowTitle(QApplication::translate("MoYuClientClass", "MoYu", Q_NULLPTR));
        actionStart->setText(QApplication::translate("MoYuClientClass", "Start", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MoYuClientClass", "Exit", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MoYuClientClass", "About", Q_NULLPTR));
        label->setText(QApplication::translate("MoYuClientClass", "TextLabel", Q_NULLPTR));
        label_state->setText(QApplication::translate("MoYuClientClass", "state: safe", Q_NULLPTR));
        btn_police->setText(QString());
        menuSomething->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MoYuClientClass: public Ui_MoYuClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOYUCLIENTDLG_H
