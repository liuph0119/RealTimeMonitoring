/********************************************************************************
** Form generated from reading UI file 'whatisit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHATISIT_H
#define UI_WHATISIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_whatisit
{
public:
    QLabel *label;
    QLabel *label_text;

    void setupUi(QWidget *whatisit)
    {
        if (whatisit->objectName().isEmpty())
            whatisit->setObjectName(QStringLiteral("whatisit"));
        whatisit->resize(400, 190);
        QIcon icon;
        icon.addFile(QStringLiteral("help.ico"), QSize(), QIcon::Normal, QIcon::Off);
        whatisit->setWindowIcon(icon);
        label = new QLabel(whatisit);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 80, 80));
        label_text = new QLabel(whatisit);
        label_text->setObjectName(QStringLiteral("label_text"));
        label_text->setGeometry(QRect(100, 10, 291, 171));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(8);
        font.setItalic(true);
        label_text->setFont(font);

        retranslateUi(whatisit);

        QMetaObject::connectSlotsByName(whatisit);
    } // setupUi

    void retranslateUi(QWidget *whatisit)
    {
        whatisit->setWindowTitle(QApplication::translate("whatisit", "what is it?", Q_NULLPTR));
        label->setText(QApplication::translate("whatisit", "TextLabel", Q_NULLPTR));
        label_text->setText(QApplication::translate("whatisit", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class whatisit: public Ui_whatisit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHATISIT_H
