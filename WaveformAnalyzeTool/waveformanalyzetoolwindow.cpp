#include "waveformanalyzetoolwindow.h"
#include "ui_waveformanalyzetoolwindow.h"

WaveformAnalyzeToolWindow::WaveformAnalyzeToolWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WaveformAnalyzeToolWindow)
{
    ui->setupUi(this);
}

WaveformAnalyzeToolWindow::~WaveformAnalyzeToolWindow()
{
    delete ui;
}
