#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include "QMessageBox"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setImgUI();

    MainWindow::openedFile = std::make_shared<QDir>();
    MainWindow::openedFile->setPath("");

    timer = std::make_unique<QTimer>();
    connect(timer.get(), &QTimer::timeout, this, &MainWindow::videoPlayer);

    ui->pushButton_playPause->setIcon(MainWindow::playIcon);
    ui->pushButton_playPause->setFixedSize(QSize(35,35));
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

    MainWindow::autoScaleVideoBar();
}

void MainWindow::on_actionOpen_file_triggered()
{
    fileBrowser = std::make_unique<FileBrowser>(nullptr, MainWindow::openedFile);
    connect(fileBrowser.get(), &FileBrowser::fileOpened, this, &MainWindow::on_fileOpened);
    fileBrowser->show();
}

void MainWindow::on_pushButton_playPause_clicked()
{
    if(MainWindow::pause){
        MainWindow::videoPlay();
        ui->pushButton_playPause->setIcon(MainWindow::pauseIcon);
    }else{
        MainWindow::videoStop();
        ui->pushButton_playPause->setIcon(MainWindow::playIcon);
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
        video.set(cv::CAP_PROP_POS_FRAMES, cv::CAP_PROP_FRAME_COUNT);
        video.read(frame);
        MainWindow::showFrame();
        video.set(cv::CAP_PROP_POS_FRAMES, 0);
    }
    qDebug() << "frame count:" << video.get(cv::CAP_PROP_FRAME_COUNT) << " current frame:" << video.get(cv::CAP_PROP_POS_FRAMES);
}

void MainWindow::on_horizontalSlider_videoBar_sliderReleased()
{
    if(!MainWindow::pause){
        MainWindow::videoPlay();
    }
}

void MainWindow::on_fileOpened()
{
    if(fileBrowser->getFileType() == fileType::VIDEO){
        video.open(MainWindow::openedFile->absolutePath().toStdString());

        if(!video.isOpened()){
            qDebug() << "Video not opened";
        }else{
            MainWindow::frameInterval = 1/video.get(cv::CAP_PROP_FPS)*1000;
            MainWindow::setVideoUI();
            MainWindow::setVideoBar();
            video.read(frame);
            MainWindow::showFrame();
            MainWindow::autoScaleVideoBar();
        }
    }else if(fileBrowser->getFileType() == fileType::IMG){
        MainWindow::videoStop();
        MainWindow::setImgUI();
        MainWindow::showImage();
    }
}


//************************************************************FUNCTIONS************************************************************//
void MainWindow::showImage(){
    img = QImage(openedFile->absolutePath());
    ui->label_pic->setPixmap(QPixmap::fromImage(img).scaled(ui->label_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

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
    if((int)video.get(cv::CAP_PROP_FRAME_COUNT) % 5 == 0)
        ui->horizontalSlider_videoBar->setMaximum(video.get(cv::CAP_PROP_FRAME_COUNT)/5);
    else
        ui->horizontalSlider_videoBar->setMaximum(video.get(cv::CAP_PROP_FRAME_COUNT)/5 + 1);
}

void MainWindow::autoScaleVideoBar(){
    ui->horizontalSlider_videoBar->setFixedWidth(ui->label_pic->pixmap().width() - ui->pushButton_playPause->width() - 6);
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

        img = QImage();
    }
}

void MainWindow::setVideoUI()
{
    ui->pushButton_playPause->setHidden(false);
    ui->horizontalSlider_videoBar->setHidden(false);
}

void MainWindow::setImgUI()
{
    ui->pushButton_playPause->setHidden(true);
    ui->horizontalSlider_videoBar->setHidden(true);
}

