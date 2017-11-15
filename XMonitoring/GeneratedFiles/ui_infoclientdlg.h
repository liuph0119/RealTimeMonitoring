/********************************************************************************
** Form generated from reading UI file 'infoclientdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOCLIENTDLG_H
#define UI_INFOCLIENTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InfoClientClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QTextEdit *text;
    QProgressBar *progressBar;

    void setupUi(QDialog *InfoClientClass)
    {
        if (InfoClientClass->objectName().isEmpty())
            InfoClientClass->setObjectName(QStringLiteral("InfoClientClass"));
        InfoClientClass->resize(311, 203);
        InfoClientClass->setMaximumSize(QSize(311, 203));
        verticalLayout = new QVBoxLayout(InfoClientClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(InfoClientClass);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        label->setFont(font);

        horizontalLayout_2->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        text = new QTextEdit(InfoClientClass);
        text->setObjectName(QStringLiteral("text"));
        text->setFont(font);

        horizontalLayout->addWidget(text);

        progressBar = new QProgressBar(InfoClientClass);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setAutoFillBackground(false);
        progressBar->setStyleSheet(QStringLiteral(""));
        progressBar->setValue(50);
        progressBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(progressBar);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(InfoClientClass);

        QMetaObject::connectSlotsByName(InfoClientClass);
    } // setupUi

    void retranslateUi(QDialog *InfoClientClass)
    {
        InfoClientClass->setWindowTitle(QApplication::translate("InfoClientClass", "InfoClient", Q_NULLPTR));
        label->setText(QApplication::translate("InfoClientClass", "Danger Index", Q_NULLPTR));
        text->setHtml(QApplication::translate("InfoClientClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InfoClientClass: public Ui_InfoClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOCLIENTDLG_H
