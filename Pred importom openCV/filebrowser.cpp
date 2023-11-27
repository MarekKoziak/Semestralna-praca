#include "filebrowser.h"
#include "ui_filebrowser.h"

#include <QPushButton>
#include <QMessageBox>
#include <QFileInfo>

FileBrowser::FileBrowser(QWidget *parent, std::shared_ptr<QDir> openedFile) : QDialog(parent),
    ui(new Ui::FileBrowser),
    openedFile(openedFile)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Open), &QPushButton::clicked, this, &FileBrowser::onOpenButtonClicked);
    connect(ui->lineEdit_filePath, &QLineEdit::returnPressed, this, &FileBrowser::onEnterPressed);

    foreach (QFileInfo var, QDir().drives()) {
            ui->comboBox_drive->addItem(var.absoluteFilePath());
    }
    FileBrowser::listDir();
    FileBrowser::showPath();
}

FileBrowser::~FileBrowser()
{
    delete ui;
}

void FileBrowser::on_comboBox_drive_activated(int index)
{
    FileBrowser::dir.setPath(ui->comboBox_drive->currentText());
    FileBrowser::showPath();
    FileBrowser::listDir();
}

void FileBrowser::onOpenButtonClicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();

    if(item != nullptr){
        FileBrowser::opennItem(item);
    }
}

void FileBrowser::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    FileBrowser::opennItem(item);
}

void FileBrowser::onEnterPressed()
{
    QString path = ui->lineEdit_filePath->text();
    if(QDir(path).exists()){
        if(QFileInfo(path).isDir()){
            FileBrowser::dir.setPath(path);
            FileBrowser::listDir();
        }else if(QFileInfo(path).isFile()){
            FileBrowser::openedFile->setPath(path);
            FileBrowser::close();
        }
    } else {
        FileBrowser::showPath();
    }
}



void FileBrowser::listDir(){
    ui->listWidget->clear();
    foreach (QFileInfo var, FileBrowser::dir.entryInfoList()) {
        ui->listWidget->addItem(var.fileName());
    }
}

void FileBrowser::showPath(){
    ui->lineEdit_filePath->setText(FileBrowser::dir.absolutePath());
}

void FileBrowser::opennItem(QListWidgetItem *item){
    if(FileBrowser::dir.exists(item->text())){
        QString path = FileBrowser::dir.absolutePath() + "/" + item->text();
        if(QFileInfo(path).isDir()){
            FileBrowser::dir.cd(item->text());
            FileBrowser::showPath();
            FileBrowser::listDir();
        }else if(QFileInfo(path).isFile()){
            FileBrowser::openedFile->setPath(path);
            FileBrowser::close();
        }
    }
}
