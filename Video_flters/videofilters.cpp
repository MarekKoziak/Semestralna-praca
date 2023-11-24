#include "videofilters.h"
#include "ui_videofilters.h"

#include "QMessageBox"
#include <QDebug>

VideoFilters::VideoFilters(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::VideoFilters)
{
    ui->setupUi(this);

    VideoFilters::openedFile = std::make_shared<QDir>();
    VideoFilters::openedFile->setPath("");
}

VideoFilters::~VideoFilters()
{
    delete ui;
}

void VideoFilters::closeEvent(QCloseEvent *event)
{
    if (fileBrowser) {
        fileBrowser->close();
    }

    QMainWindow::closeEvent(event);
}

void VideoFilters::on_actionOpen_file_triggered()
{
    fileBrowser = std::make_unique<FileBrowser>(nullptr, VideoFilters::openedFile);
    fileBrowser->show();
}

void VideoFilters::on_pushButton_clicked(){
    QMessageBox::information(this,"", VideoFilters::openedFile->absolutePath());
}

void VideoFilters::setFilePath(QString filePath){

}

