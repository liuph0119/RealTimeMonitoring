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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindowClass
{
public:
    QWidget *centralWidget;
    QTextEdit *output;
    QComboBox *cameraId;
    QLabel *label;
    QLabel *cameralbl;
    QLabel *cameralbl_small;
    QPushButton *lunchCamera;
    QPushButton *loadModel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mainwindowClass)
    {
        if (mainwindowClass->objectName().isEmpty())
            mainwindowClass->setObjectName(QStringLiteral("mainwindowClass"));
        mainwindowClass->resize(785, 680);
        QIcon icon;
        icon.addFile(QStringLiteral("C:/Users/liuph/Pictures/icon/viking_128px_1209601_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        mainwindowClass->setWindowIcon(icon);
        centralWidget = new QWidget(mainwindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        output = new QTextEdit(centralWidget);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(0, 460, 771, 161));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        output->setFont(font);
        cameraId = new QComboBox(centralWidget);
        cameraId->setObjectName(QStringLiteral("cameraId"));
        cameraId->setGeometry(QRect(590, 320, 121, 22));
        cameraId->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(520, 320, 54, 12));
        label->setFont(font);
        cameralbl = new QLabel(centralWidget);
        cameralbl->setObjectName(QStringLiteral("cameralbl"));
        cameralbl->setGeometry(QRect(0, 0, 511, 460));
        cameralbl_small = new QLabel(centralWidget);
        cameralbl_small->setObjectName(QStringLiteral("cameralbl_small"));
        cameralbl_small->setGeometry(QRect(520, 10, 256, 256));
        lunchCamera = new QPushButton(centralWidget);
        lunchCamera->setObjectName(QStringLiteral("lunchCamera"));
        lunchCamera->setGeometry(QRect(620, 360, 93, 28));
        lunchCamera->setFont(font);
        loadModel = new QPushButton(centralWidget);
        loadModel->setObjectName(QStringLiteral("loadModel"));
        loadModel->setGeometry(QRect(520, 360, 93, 28));
        loadModel->setFont(font);
        mainwindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 785, 26));
        mainwindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainwindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainwindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainwindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mainwindowClass->setStatusBar(statusBar);

        retranslateUi(mainwindowClass);

        QMetaObject::connectSlotsByName(mainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindowClass)
    {
        mainwindowClass->setWindowTitle(QApplication::translate("mainwindowClass", "\351\203\216\345\222\270\345\271\263\347\233\221\346\216\247\345\231\250", Q_NULLPTR));
        label->setText(QApplication::translate("mainwindowClass", "Cameras", Q_NULLPTR));
        cameralbl->setText(QApplication::translate("mainwindowClass", "ImageShow", Q_NULLPTR));
        cameralbl_small->setText(QApplication::translate("mainwindowClass", "TextLabel", Q_NULLPTR));
        lunchCamera->setText(QApplication::translate("mainwindowClass", "restart", Q_NULLPTR));
        loadModel->setText(QApplication::translate("mainwindowClass", "load ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainwindowClass: public Ui_mainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
