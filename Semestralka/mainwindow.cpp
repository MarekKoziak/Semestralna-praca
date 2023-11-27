#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/opencv.hpp>

#include "QMessageBox"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::openedFile = std::make_shared<QDir>();
    MainWindow::openedFile->setPath("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (fileBrowser) {
        fileBrowser->close();
    }

    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionOpen_file_triggered()
{
    fileBrowser = std::make_unique<FileBrowser>(nullptr, MainWindow::openedFile);
    fileBrowser->show();
}

void MainWindow::on_pushButton_clicked(){
    QMessageBox::information(this,"", MainWindow::openedFile->absolutePath());
}
