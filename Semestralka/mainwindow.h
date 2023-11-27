#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

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

private slots:
    void on_actionOpen_file_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<FileBrowser> fileBrowser;
    std::shared_ptr<QDir> openedFile;
};
#endif // MAINWINDOW_H
