#ifndef VIDEOFILTERS_H
#define VIDEOFILTERS_H

#include "filebrowser.h"
#include <QMainWindow>
#include <memory>

namespace Ui {
class VideoFilters;
}

class VideoFilters : public QMainWindow
{
    Q_OBJECT

public:
    VideoFilters(QWidget *parent = nullptr);
    ~VideoFilters();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionOpen_file_triggered();

    void on_pushButton_clicked();

private:
    Ui::VideoFilters *ui;
    std::unique_ptr<FileBrowser> fileBrowser;
    std::shared_ptr<QDir> openedFile;

public:
    static void setFilePath(QString filePath);
};
#endif // VIDEOFILTERS_H
