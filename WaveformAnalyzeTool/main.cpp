#include "waveformanalyzetoolwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WaveformAnalyzeToolWindow w;
    w.show();

    return a.exec();
}
