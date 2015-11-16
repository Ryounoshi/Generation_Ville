#ifndef PARAMWINDOW_H
#define PARAMWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include "modele/batiment/batparameter.h"
#include <QGridLayout>

class ParamWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ParamWindow(QWidget *parent = 0, bool *mesh = 0, BatParameter *par = 0);
    void update_values();
    void update_sliders();

private:
    bool *_glparent;
    BatParameter *_par;

    QLabel *titre_maxetage;
    QSlider *slider_maxetage;
    QLabel *value_maxetage;

    QLabel *titre_influencecentreville;
    QSlider *slider_influencecentreville;
    QLabel *value_influencecentreville;

    QLabel *titre_split;
    QSlider *slider_split;
    QLabel *value_split;

    QGridLayout *mainlayout;

public slots:
    void changer_maxetage();
    void changer_influencecentreville();
    void changer_splitPourcent();
};

#endif // PARAMWINDOW_H
