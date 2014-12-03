#ifndef WAVEFORMANALYZETOOLWINDOW_H
#define WAVEFORMANALYZETOOLWINDOW_H

#include <QMainWindow>

namespace Ui {
class WaveformAnalyzeToolWindow;
}

class WaveformAnalyzeToolWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WaveformAnalyzeToolWindow(QWidget *parent = 0);
    ~WaveformAnalyzeToolWindow();

private:
    Ui::WaveformAnalyzeToolWindow *ui;
};

#endif // WAVEFORMANALYZETOOLWINDOW_H
