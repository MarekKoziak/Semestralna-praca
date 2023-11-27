#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QDialog>
#include <QDir>
#include <QListWidget>
#include <memory>

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
    void fileOpened(const QDir &file);

private slots:
    void on_comboBox_drive_activated();

    void onOpenButtonClicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void onEnterPressed();

private:
    Ui::FileBrowser *ui;
    QDir dir;
    std::shared_ptr<QDir> openedFile;

public:
    void listDir();
    void showPath();
    void opennItem(QListWidgetItem *item);
};

#endif // FILEBROWSER_H
