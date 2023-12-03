#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QDialog>
#include <QDir>
#include <QListWidget>
#include <QStringList>
#include <memory>

enum fileType {VIDEO, IMG};

namespace Ui {
class FileBrowser;
}

class FileBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = nullptr, std::shared_ptr<QDir> openedFile = nullptr);
    ~FileBrowser();

signals:
    void fileOpened();

private slots:
    void on_comboBox_drive_activated();

    void onOpenButtonClicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void onEnterPressed();

private:
    Ui::FileBrowser *ui;
    QDir dir;
    std::shared_ptr<QDir> openedFile;
    fileType fileType;

    QStringList videoExtensions = {
        "mp4", "avi", "mkv", "mov", "wmv", "flv", "webm", "m4v", "mpeg", "3gp"
    };

    QStringList imageExtensions = {
        "png", "jpg", "jpeg", "gif", "bmp", "tiff", "ico", "svg", "webp"
    };


public:
    void listDir();
    void showPath();
    void opennItem(QListWidgetItem *item);
    bool fileFilter(QFileInfo file);
    enum fileType getFileType() const;
};

#endif // FILEBROWSER_H
