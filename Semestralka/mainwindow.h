#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QTimer>

#include <opencv2/opencv.hpp>
#include "filebrowser.h"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

signals:
    void resized();

private slots:
    void on_actionOpen_file_triggered();

    void on_pushButton_clicked();

    void on_pushButton_playPause_clicked();

    void videoPlayer();

    void on_horizontalSlider_videoBar_sliderPressed();

    void on_horizontalSlider_videoBar_sliderReleased();

    void on_horizontalSlider_videoBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<FileBrowser> fileBrowser;
    std::shared_ptr<QDir> openedFile;
    cv::VideoCapture video;
    cv::Mat frame;
    QImage img;
    std::unique_ptr<QTimer> timer;
    double frameInterval;
    bool pause = true;

public:
    void showFrame();
    void videoPlay();
    void videoStop();
    void setVideoBar();
    void moveVideoBar();
};
#endif // MAINWINDOW_H
