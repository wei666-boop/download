/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *plainTextEdit;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *savebutton;
    QLineEdit *save_line;
    QPushButton *browser_download;
    QLineEdit *browse_line;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *plainTextEdit_2;
    QTextEdit *output;
    QCheckBox *thread;
    QLabel *label;
    QPushButton *download_button;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 800);
        QFont font;
        font.setFamily(QStringLiteral("Brush Script MT"));
        Widget->setFont(font);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 153, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 2, 1, 1);

        plainTextEdit = new QPlainTextEdit(Widget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QFont font1;
        font1.setPointSize(12);
        plainTextEdit->setFont(font1);

        gridLayout->addWidget(plainTextEdit, 1, 2, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(154, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 7, 1, 1);

        savebutton = new QPushButton(Widget);
        savebutton->setObjectName(QStringLiteral("savebutton"));
        savebutton->setMinimumSize(QSize(30, 0));

        gridLayout->addWidget(savebutton, 2, 2, 1, 1);

        save_line = new QLineEdit(Widget);
        save_line->setObjectName(QStringLiteral("save_line"));
        save_line->setMinimumSize(QSize(261, 20));

        gridLayout->addWidget(save_line, 2, 3, 1, 4);

        browser_download = new QPushButton(Widget);
        browser_download->setObjectName(QStringLiteral("browser_download"));
        browser_download->setMinimumSize(QSize(30, 0));
        browser_download->setCheckable(false);

        gridLayout->addWidget(browser_download, 3, 2, 1, 1);

        browse_line = new QLineEdit(Widget);
        browse_line->setObjectName(QStringLiteral("browse_line"));
        browse_line->setMinimumSize(QSize(261, 20));

        gridLayout->addWidget(browse_line, 3, 3, 1, 4);

        horizontalSpacer = new QSpacerItem(155, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        plainTextEdit_2 = new QPlainTextEdit(Widget);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));

        gridLayout->addWidget(plainTextEdit_2, 4, 1, 1, 3);

        output = new QTextEdit(Widget);
        output->setObjectName(QStringLiteral("output"));

        gridLayout->addWidget(output, 4, 4, 1, 3);

        thread = new QCheckBox(Widget);
        thread->setObjectName(QStringLiteral("thread"));

        gridLayout->addWidget(thread, 5, 1, 1, 1);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 5, 4, 1, 2);

        download_button = new QPushButton(Widget);
        download_button->setObjectName(QStringLiteral("download_button"));
        QFont font2;
        font2.setPointSize(15);
        download_button->setFont(font2);

        gridLayout->addWidget(download_button, 5, 6, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 54, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 6, 5, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("Widget", "\346\254\242\350\277\216\345\244\247\345\256\266\346\235\245\344\275\277\347\224\250\346\210\221\347\232\204\350\277\231\344\270\252\347\216\251\345\205\267\357\274\214\350\277\231\344\270\252\347\216\251\345\205\267\345\217\252\346\230\257\346\210\221\344\270\272\344\272\206\345\255\246\344\271\240\350\200\214\345\201\232\347\232\204\357\274\214\345\271\266\344\270\215\346\230\257\350\203\275\345\244\237\347\234\237\346\255\243\350\256\251\345\244\247\345\256\266\350\203\275\344\275\277\347\224\250\347\232\204\357\274\214\345\233\240\344\270\272\347\274\272\347\202\271\345\244\252\345\244\232", nullptr));
        savebutton->setText(QApplication::translate("Widget", "\344\277\235\345\255\230", nullptr));
        browser_download->setText(QApplication::translate("Widget", "\347\275\221\345\235\200", nullptr));
        plainTextEdit_2->setPlainText(QApplication::translate("Widget", "\347\202\271\345\207\273\346\255\244\346\214\211\351\222\256\345\260\206\351\207\207\347\224\250\345\244\232\347\272\277\347\250\213\344\270\213\350\275\275", nullptr));
        thread->setText(QApplication::translate("Widget", "\345\244\232\347\272\277\347\250\213", nullptr));
        label->setText(QApplication::translate("Widget", "\346\203\263\344\270\213\350\275\275\350\257\267\347\202\271\345\207\273\346\255\244\346\214\211\351\222\256", nullptr));
        download_button->setText(QApplication::translate("Widget", "\344\270\213\350\275\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
