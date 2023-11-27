#include "videofilters.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoFilters w;
    w.show();

    return a.exec();
}
