#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rspSimFull.h"
#include "L_RadarPar_type.h"
#include "L_Head_type.h"
#include "AntPosition_type.h"
#include "L_RadSimOut_type.h"
#include "L_RspOut_type.h"
#include "ClutSimPar_type.h"
#include "TerMap_type.h"

#include <QString>

const float sampleMin = -8.0f;
const float sampleMax = 8.0f;

//??цяч???р? фя я??ў ?ч э?Ї RspSimFullInit
ClutSimPar_type	gClutSimPar	= CLUTSIMPAR;
double iangle;

#define QUANTITY_DWELL	9

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    idata = new RSPSimFull;

    chart_1d = new QChart;
    series_1d = new QLineSeries();

    chart_1d->legend()->hide();
    chart_1d->addSeries(series_1d);

    // ЋЎкпў«пҐ¬ Ё Ё­ЁжЁ «Ё§ЁагҐ¬ ®бм X Ё ®бм Y
    axisX = new QValueAxis();    axisY = new QValueAxis();
    // “бв ­®ўЁвм ¤Ё Ї §®­ ®в®Ўа ¦Ґ­Ёп ®бЁ Є®®а¤Ё­ в
    axisX->setMin(0);    axisX->setMax(10);
    axisY->setMin(0);    axisY->setMax(50);

    // “бв ­ ў«Ёў Ґ¬ в®зЄЁ бҐвЄЁ ­  ®бЁ Є®®а¤Ё­ в
    axisX->setTickCount(12); axisY->setTickCount(5);

    //axisX->setTitleText(QString::fromLocal8Bit("Время"));    axisY->setTitleText(QString::fromLocal8Bit("Амплитуда"));
    axisX->setTitleText("Время");    axisY->setTitleText("Амплитуда");

    chart_1d->addAxis(axisX, Qt::AlignBottom);    chart_1d->addAxis(axisY, Qt::AlignLeft);
    series_1d->attachAxis(axisX);    series_1d->attachAxis(axisY);

    ui->graphicsView_2->setChart(chart_1d);

    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::blue);//black);
    gr.setColorAt(0.67, Qt::yellow);
    gr.setColorAt(1.0, Qt::red);

    GraphSpectrogram = new Q3DSurface();//Viewer);
    GraphSpectrogram->setObjectName("GraphSpectrogram");
    GraphSpectrogram->setGeometry(QRect(650, 80, 511, 371));

    GraphSpectrogram->setAxisX(new QValue3DAxis);
    GraphSpectrogram->setAxisY(new QValue3DAxis);
    GraphSpectrogram->setAxisZ(new QValue3DAxis);

    q3DProxy_2D = new QSurfaceDataProxy();
    q3DSeries_2D = new QSurface3DSeries(q3DProxy_2D);

    q3DSeries_2D->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
    q3DSeries_2D->setFlatShadingEnabled(true);

    static int preset = Q3DCamera::CameraPresetDirectlyAbove;//FrontLow;
    GraphSpectrogram->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset)preset);

    GraphSpectrogram->scene()->activeCamera()->setWrapXRotation(false);
    GraphSpectrogram->scene()->activeCamera()->setWrapYRotation(false);

    GraphSpectrogram->scene()->activeCamera()->setXRotation(90.);
    GraphSpectrogram->scene()->activeCamera()->setZoomLevel(100.);

    GraphSpectrogram->activeTheme()->setGridEnabled(false);
    GraphSpectrogram->setOrthoProjection(true);

    q3DSeries_2D->setDrawMode(QSurface3DSeries::DrawSurface);
    q3DSeries_2D->setFlatShadingEnabled(true);//false);

    GraphSpectrogram->axisX()->setLabelFormat("%.2f");
    GraphSpectrogram->axisZ()->setLabelFormat("%.2f");
    GraphSpectrogram->axisX()->setRange(sampleMin, sampleMax);
    GraphSpectrogram->axisY()->setRange(0.0f, 2.0f);
    GraphSpectrogram->axisX()->setLabelAutoRotation(10);
    GraphSpectrogram->axisY()->setLabelAutoRotation(10);
    GraphSpectrogram->axisZ()->setLabelAutoRotation(10);

    GraphSpectrogram->axisX()->setTitleVisible(true);  GraphSpectrogram->axisZ()->setTitleVisible(true);
    // GraphSpectrogram->axisX()->setTitle(QString::fromLocal8Bit("Скорость"));
    // GraphSpectrogram->axisZ()->setTitle(QString::fromLocal8Bit("Дальность"));
    GraphSpectrogram->axisX()->setTitle("Скорость");
    GraphSpectrogram->axisZ()->setTitle("Дальность");
    GraphSpectrogram->axisZ()->setReversed(true);

    GraphSpectrogram->setHorizontalAspectRatio(1.0);

    GraphSpectrogram->addSeries(q3DSeries_2D);

    GraphSpectrogram->seriesList().at(0)->setBaseGradient(gr);
    GraphSpectrogram->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    QWidget *container = QWidget::createWindowContainer(GraphSpectrogram);

    ui->verticalLayout_5->addWidget(container, 1);

    idwell = 0;
    iangle = 0;
    ivelocity = 0;
    ifreq = 10;

    ui->Rain_Rate_2->setText(QString::number(gClutSimPar.rain_rate));
    ui->Rain_Vel_2->setText(QString::number(gClutSimPar.rain_vel));
    ui->Rain_VelStd_2->setText(QString::number(gClutSimPar.rain_velstd));
    ui->Rain_Rmin_2->setText(QString::number(gClutSimPar.rain_rmin));
    ui->Rain_Rmax_2->setText(QString::number(gClutSimPar.rain_rmax));
    ui->Rain_Hmax_2->setText(QString::number(gClutSimPar.rain_hmax));

    ui->Raint_Presense_2->setChecked(true);
    ui->Dwell_2->setMinimum(1);
    ui->Dwell_2->setMaximum(QUANTITY_DWELL);
    QIntValidator *validator = new QIntValidator(-10, 80, this);
    ui->Beam_2->setValidator(validator);
    ui->Beam_2->setText("0");
    ui->Freq_ADC_2->setText("10");
    ui->Velocity_2->setMinimum(1);
    ui->Velocity_2->setMaximum(32);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fill_1d(int idwell, int ivelocity) {
    vector<double>* Abs_1d = idata->get_to_ADC_1d(idwell, ivelocity);

    series_1d->clear();
    for (int i = 0; i < Abs_1d->size(); i++) {
        series_1d->append(i, (*Abs_1d)[i]);
    }
    axisX->setMin(0);    axisX->setMax(Abs_1d->size()-1);
    double min0 = *min_element(Abs_1d->begin(), Abs_1d->end());
    double max0 = *max_element(Abs_1d->begin(), Abs_1d->end());
    axisY->setMin(round(min0));    axisY->setMax(round(max0));
}

void MainWindow::fill_2d(int idwell) {

    QSurfaceDataArray *dataArray = new QSurfaceDataArray;
    vector<vector<double>>* Abs_2d = idata->get_to_ADC_2d(idwell);

    int size_z = Abs_2d->size();
    dataArray->reserve(size_z);

    double Min_y_double, Max_y_double;
    vector<int> Min, Max;

    for (int i = 0; i < size_z; i++) {
        float Z = i;
        QSurfaceDataRow *newRow = new QSurfaceDataRow(Abs_2d->at(i).size());
        int X_size = static_cast<int>(Abs_2d->at(i).size());
        Min_y_double = *std::min_element(Abs_2d->at(i).begin(), Abs_2d->at(i).end());
        int Min_y = static_cast<int>(Min_y_double);  Min.push_back(Min_y);
        Max_y_double = *std::max_element(Abs_2d->at(i).begin(), Abs_2d->at(i).end());
        int Max_y = static_cast<int>(Max_y_double);  Max.push_back(Max_y);
        GraphSpectrogram->axisX()->setRange(0, X_size - 1);
        for (int u = 0; u < X_size; u++) {
            float X = u;
            float Y = static_cast<float>((*Abs_2d)[i][u]);

            (*newRow)[u].setPosition(QVector3D(X, Y, Z));
        }
        *dataArray << newRow;
    }
    q3DProxy_2D->resetArray(dataArray);

    int Min_Y = *std::min_element(Min.begin(), Min.end());
    int Max_Y = *std::max_element(Max.begin(), Max.end());

    GraphSpectrogram->axisY()->setRange(Min_Y, Max_Y);
}


#if 0
void MainWindow::on_checkBox_clicked(bool checked)
{
    if (checked == false) gClutSimPar.rain_pres = 0;
    else gClutSimPar.rain_pres = 1;
}

#endif

void MainWindow::on_Rain_Rate_2_textChanged(const QString &arg1)
{
    bool ok;
    gClutSimPar.rain_rate = arg1.toDouble(&ok);

    if (!ok) gClutSimPar.rain_rate = 0.0;
}

void MainWindow::on_Rain_Vel_2_textChanged(const QString &arg1)
{
    bool ok;
    gClutSimPar.rain_vel = arg1.toDouble(&ok);

    if (!ok) gClutSimPar.rain_vel = 0.0;
}

void MainWindow::on_Rain_VelStd_2_textChanged(const QString &arg1)
{
    bool ok;
    gClutSimPar.rain_velstd = arg1.toDouble(&ok);

    if (!ok) gClutSimPar.rain_velstd = 0.0;
}

void MainWindow::on_Rain_Rmin_2_textChanged(const QString &arg1)
{
    bool ok;
    gClutSimPar.rain_rmin = arg1.toDouble(&ok);

    if (!ok) gClutSimPar.rain_rmin = 0.0;
}

void MainWindow::on_Rain_Rmax_2_textChanged(const QString &arg1)
{
    bool ok;
    gClutSimPar.rain_rmax = arg1.toDouble(&ok);

    if (!ok) gClutSimPar.rain_rmax = 0.0;
}

void MainWindow::on_Rain_Hmax_2_textChanged(const QString &arg1)
{
    bool ok;
    gClutSimPar.rain_hmax = arg1.toDouble(&ok);

    if (!ok) gClutSimPar.rain_hmax = 0.0;
}

void MainWindow::on_Freq_ADC_2_textChanged(const QString &arg1)
{
    bool ok;
    ifreq = arg1.toDouble(&ok);

    if(!ok) ifreq = 0.0;
}

void MainWindow::on_Beam_2_textChanged(const QString &arg1)
{
    bool ok;
    iangle = arg1.toDouble(&ok);

    if(!ok) iangle = 0.0;
}

void MainWindow::on_Dwell_2_valueChanged(int arg1)
{
    idwell = arg1 - 1;
}

void MainWindow::on_Velocity_2_valueChanged(int arg1)
{
    ivelocity = arg1 - 1;
}

void MainWindow::on_pushButton_2_clicked()
{
    idata->RspSFI(&gClutSimPar, iangle, ifreq);

    fill_1d(idwell, ivelocity);
    fill_2d(idwell);
}


void MainWindow::on_Raint_Presense_2_clicked(bool checked)
{
    if (checked == true) idata->RspSFI(&gClutSimPar, iangle, ifreq);
}

