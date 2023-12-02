/********************************************************************************
** Form generated from reading UI file 'filebrowser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEBROWSER_H
#define UI_FILEBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FileBrowser
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_drive;
    QLineEdit *lineEdit_filePath;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FileBrowser)
    {
        if (FileBrowser->objectName().isEmpty())
            FileBrowser->setObjectName("FileBrowser");
        FileBrowser->resize(796, 526);
        horizontalLayout_2 = new QHBoxLayout(FileBrowser);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        comboBox_drive = new QComboBox(FileBrowser);
        comboBox_drive->setObjectName("comboBox_drive");

        horizontalLayout->addWidget(comboBox_drive);

        lineEdit_filePath = new QLineEdit(FileBrowser);
        lineEdit_filePath->setObjectName("lineEdit_filePath");

        horizontalLayout->addWidget(lineEdit_filePath);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(FileBrowser);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(FileBrowser);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Open);

        verticalLayout_2->addWidget(buttonBox);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(FileBrowser);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, FileBrowser, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(FileBrowser);
    } // setupUi

    void retranslateUi(QDialog *FileBrowser)
    {
        FileBrowser->setWindowTitle(QCoreApplication::translate("FileBrowser", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileBrowser: public Ui_FileBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEBROWSER_H
