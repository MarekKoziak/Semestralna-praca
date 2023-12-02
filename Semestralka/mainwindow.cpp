#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include "QMessageBox"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::openedFile = std::make_shared<QDir>();
    MainWindow::openedFile->setPath("");

    timer = std::make_unique<QTimer>();
    connect(timer.get(), &QTimer::timeout, this, &MainWindow::videoPlayer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (fileBrowser) {
        fileBrowser->close();
    }

    QMainWindow::closeEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    //spravit funkcne menenie velkosti okna
    //QSize sizeMin(50, 50);
    //ui->label_pic->setPixmap(QPixmap().scaled(sizeMin));
    ui->label_pic->setPixmap(QPixmap::fromImage(img).scaled(ui->label_pic->size(), Qt::KeepAspectRatio));
    qDebug() << "label size:" << ui->label_pic->size() << "pixmap size:" << ui->label_pic->pixmap().size();

    ui->horizontalSlider_videoBar->setFixedWidth(ui->label_pic->pixmap().width() - ui->pushButton_playPause->width() - 6);
}

void MainWindow::on_actionOpen_file_triggered()
{
    fileBrowser = std::make_unique<FileBrowser>(nullptr, MainWindow::openedFile);
    fileBrowser->show();
}

void MainWindow::on_pushButton_playPause_clicked()
{
    if(MainWindow::pause){
        MainWindow::videoPlay();
    }else{
        MainWindow::videoStop();
    }
}

void MainWindow::on_horizontalSlider_videoBar_sliderPressed()
{
    timer->stop();
}

void MainWindow::on_horizontalSlider_videoBar_valueChanged(int value)
{
    if(value != ui->horizontalSlider_videoBar->maximum()){
        video.set(cv::CAP_PROP_POS_FRAMES, value*5);
        video.read(frame);
        MainWindow::showFrame();
    }else{
        video.set(cv::CAP_PROP_POS_FRAMES, cv::CAP_PROP_FRAME_COUNT-1);
    }
}

void MainWindow::on_horizontalSlider_videoBar_sliderReleased()
{
    if(!MainWindow::pause){
        qDebug() << "slider released";
        MainWindow::videoPlay();
    }
}


//************Spravit aby sa tento kod spustil po vybrani videa************//
void MainWindow::on_pushButton_clicked()
{
    video.open(MainWindow::openedFile->absolutePath().toStdString());
    MainWindow::frameInterval = 1/video.get(cv::CAP_PROP_FPS)*1000;

    if(!video.isOpened()){
        qDebug() << "Video not opened";
    }else{
        MainWindow::setVideoBar();
    }
}
//************Spravit aby sa tento kod spustsl po vybrani videa************//

void MainWindow::showFrame(){
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    img = QImage((uchar*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
    ui->label_pic->setPixmap(QPixmap::fromImage(img).scaled(ui->label_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::videoPlay(){
        pause = false;
        timer->start(MainWindow::frameInterval);
}

void MainWindow::videoStop(){
        pause = true;
        timer->stop();
}

void MainWindow::setVideoBar(){
    ui->horizontalSlider_videoBar->setMaximum(video.get(cv::CAP_PROP_FRAME_COUNT)/5 +1);
}

void MainWindow::moveVideoBar(){
    ui->horizontalSlider_videoBar->setValue(video.get(cv::CAP_PROP_POS_FRAMES)/5);
}

void MainWindow::videoPlayer()
{
    if (video.read(frame)) {
        MainWindow::showFrame();

        MainWindow::moveVideoBar();
    } else {
        MainWindow::videoStop();
        video.set(cv::CAP_PROP_POS_FRAMES, 0);

        MainWindow::moveVideoBar();

        img = QImage(); //Zistit preco to tu musi byt aby apka nekresla pri scalovaní okna
    }


}

