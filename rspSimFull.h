#ifndef RSPSIMFULL_H
#define RSPSIMFULL_H

#include <iostream>
#include <QVector>
#include <QObject>
#include <vector>

#include "L_Head_type.h"
#include "L_RadarPar_type.h"
#include "ClutSimPar_type.h"
#include "TerMap_type.h"

using namespace std;

class RSPSimFull : public QObject
{
    Q_OBJECT
protected:
    vector<double> Abs_1d;
    vector<vector<double>> Abs_2d;

public:
    explicit RSPSimFull(QObject *parent = nullptr);
    ~RSPSimFull();

    //void frequency_control(double i_freq);
    void* RspSFI(ClutSimPar_type* pClutSimPar, double i_angle, double i_freq);
    vector<double>* get_to_ADC_1d(int idwell, int ivelocity);
    vector<vector<double>>* get_to_ADC_2d(int idwell);
};
#endif // RSPSIMFULL_H
