/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindowClass
{
public:
    QAction *actioninitialfromimages;
    QAction *actionCopyRight;
    QAction *actionExit;
    QAction *actioninitial_from_db;
    QAction *actionsimulation_danger;
    QAction *actionsimulation_safe;
    QWidget *centralWidget;
    QTextEdit *output;
    QComboBox *cameraId;
    QLabel *label;
    QLabel *cameralbl;
    QLabel *cameralbl_small;
    QPushButton *btn_restart;
    QDoubleSpinBox *warningprob;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuSetting;

    void setupUi(QMainWindow *mainwindowClass)
    {
        if (mainwindowClass->objectName().isEmpty())
            mainwindowClass->setObjectName(QStringLiteral("mainwindowClass"));
        mainwindowClass->resize(661, 528);
        QIcon icon;
        icon.addFile(QStringLiteral("icon/Server_cloud.ico"), QSize(), QIcon::Normal, QIcon::Off);
        mainwindowClass->setWindowIcon(icon);
        actioninitialfromimages = new QAction(mainwindowClass);
        actioninitialfromimages->setObjectName(QStringLiteral("actioninitialfromimages"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("icon/image.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioninitialfromimages->setIcon(icon1);
        actionCopyRight = new QAction(mainwindowClass);
        actionCopyRight->setObjectName(QStringLiteral("actionCopyRight"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("icon/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopyRight->setIcon(icon2);
        actionExit = new QAction(mainwindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("icon/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actioninitial_from_db = new QAction(mainwindowClass);
        actioninitial_from_db->setObjectName(QStringLiteral("actioninitial_from_db"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("icon/database.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioninitial_from_db->setIcon(icon4);
        actionsimulation_danger = new QAction(mainwindowClass);
        actionsimulation_danger->setObjectName(QStringLiteral("actionsimulation_danger"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("icon/police.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionsimulation_danger->setIcon(icon5);
        actionsimulation_safe = new QAction(mainwindowClass);
        actionsimulation_safe->setObjectName(QStringLiteral("actionsimulation_safe"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("icon/safe.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsimulation_safe->setIcon(icon6);
        centralWidget = new QWidget(mainwindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        output = new QTextEdit(centralWidget);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(5, 280, 151, 221));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        output->setFont(font);
        output->setFrameShape(QFrame::StyledPanel);
        cameraId = new QComboBox(centralWidget);
        cameraId->setObjectName(QStringLiteral("cameraId"));
        cameraId->setGeometry(QRect(10, 190, 81, 22));
        cameraId->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 170, 54, 12));
        label->setFont(font);
        cameralbl = new QLabel(centralWidget);
        cameralbl->setObjectName(QStringLiteral("cameralbl"));
        cameralbl->setGeometry(QRect(160, 0, 500, 500));
        cameralbl->setFrameShape(QFrame::NoFrame);
        cameralbl_small = new QLabel(centralWidget);
        cameralbl_small->setObjectName(QStringLiteral("cameralbl_small"));
        cameralbl_small->setGeometry(QRect(5, 5, 150, 150));
        cameralbl_small->setFrameShape(QFrame::NoFrame);
        btn_restart = new QPushButton(centralWidget);
        btn_restart->setObjectName(QStringLiteral("btn_restart"));
        btn_restart->setGeometry(QRect(95, 190, 61, 23));
        btn_restart->setFont(font);
        warningprob = new QDoubleSpinBox(centralWidget);
        warningprob->setObjectName(QStringLiteral("warningprob"));
        warningprob->setGeometry(QRect(95, 240, 62, 22));
        warningprob->setFont(font);
        warningprob->setMaximum(1);
        warningprob->setSingleStep(0.01);
        warningprob->setValue(0.2);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 242, 81, 16));
        label_2->setFont(font);
        mainwindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 661, 23));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        mainwindowClass->setMenuBar(menuBar);

        menuBar->addAction(menuSetting->menuAction());
        menuSetting->addAction(actioninitialfromimages);
        menuSetting->addAction(actioninitial_from_db);
        menuSetting->addAction(actionsimulation_danger);
        menuSetting->addAction(actionsimulation_safe);
        menuSetting->addAction(actionCopyRight);
        menuSetting->addAction(actionExit);

        retranslateUi(mainwindowClass);

        QMetaObject::connectSlotsByName(mainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindowClass)
    {
        mainwindowClass->setWindowTitle(QApplication::translate("mainwindowClass", "MoYu Server", Q_NULLPTR));
        actioninitialfromimages->setText(QApplication::translate("mainwindowClass", "Initial from Images", Q_NULLPTR));
        actionCopyRight->setText(QApplication::translate("mainwindowClass", "Help", Q_NULLPTR));
        actionExit->setText(QApplication::translate("mainwindowClass", "Exit", Q_NULLPTR));
        actioninitial_from_db->setText(QApplication::translate("mainwindowClass", "Initial from Database", Q_NULLPTR));
        actionsimulation_danger->setText(QApplication::translate("mainwindowClass", "Simulation Danger", Q_NULLPTR));
        actionsimulation_safe->setText(QApplication::translate("mainwindowClass", "Simulation Safe", Q_NULLPTR));
        label->setText(QApplication::translate("mainwindowClass", "Cameras", Q_NULLPTR));
        cameralbl->setText(QApplication::translate("mainwindowClass", "ImageShow", Q_NULLPTR));
        cameralbl_small->setText(QApplication::translate("mainwindowClass", "TextLabel", Q_NULLPTR));
        btn_restart->setText(QApplication::translate("mainwindowClass", "restart", Q_NULLPTR));
        label_2->setText(QApplication::translate("mainwindowClass", "Warning Prob", Q_NULLPTR));
        menuSetting->setTitle(QApplication::translate("mainwindowClass", "Setting", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainwindowClass: public Ui_mainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
