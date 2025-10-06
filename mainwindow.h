#define BYTE_DEFINED
#include <windows.h>
#ifdef BYTE_DEFINED
#undef byte
#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rspSimFull.h"

#include <QApplication>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>

#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QChart *chart_1d;
    int idwell;
    double iangle;
    int ivelocity;
    double ifreq;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QValueAxis *axisX2;
    QValueAxis *axisY2;
    Q3DSurface *GraphSpectrogram;
    QSurfaceDataProxy *q3DProxy_2D;
    QSurface3DSeries *q3DSeries_2D;
    QLineSeries *series_1d;
    RSPSimFull *idata;

    void fill_1d(int idwell, int ivelocity);
    void fill_2d(int idwell);

private slots:



    void on_Rain_Rate_2_textChanged(const QString &arg1);

    void on_Rain_Vel_2_textChanged(const QString &arg1);

    void on_Rain_VelStd_2_textChanged(const QString &arg1);

    void on_Rain_Rmin_2_textChanged(const QString &arg1);

    void on_Rain_Rmax_2_textChanged(const QString &arg1);

    void on_Rain_Hmax_2_textChanged(const QString &arg1);

    void on_Freq_ADC_2_textChanged(const QString &arg1);

    void on_Beam_2_textChanged(const QString &arg1);

    void on_Dwell_2_valueChanged(int arg1);

    void on_Velocity_2_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_Raint_Presense_2_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
