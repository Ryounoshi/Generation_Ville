#include "paramwindow.h"
#include <QDebug>

ParamWindow::ParamWindow(QWidget *parent, bool *mesh,BatParameter *par) : QWidget(parent), _glparent(mesh),_par(par)
{
    setFixedSize(300,500);
    mainlayout = new QGridLayout;

    titre_maxetage = new QLabel("Hauteur Max");
    slider_maxetage = new QSlider();
    slider_maxetage->setRange(1,40);
    slider_maxetage->setValue(_par->maxEtage);
    value_maxetage = new QLabel(QString::number(_par->maxEtage));

    mainlayout->addWidget(titre_maxetage,0,0);
    mainlayout->addWidget(value_maxetage,1,0);
    mainlayout->addWidget(slider_maxetage,2,0);

    titre_influencecentreville = new QLabel("Influence centreville");
    slider_influencecentreville = new QSlider();
    slider_influencecentreville->setRange(1,30);
    slider_influencecentreville->setValue((_par->influenceCentreVille*10.0));
    value_influencecentreville = new QLabel(QString::number(_par->influenceCentreVille));

    mainlayout->addWidget(titre_influencecentreville,0,1);
    mainlayout->addWidget(value_influencecentreville,1,1);
    mainlayout->addWidget(slider_influencecentreville,2,1);

    titre_split = new QLabel("% Split");
    slider_split = new QSlider();
    slider_split->setRange(0,100);
    slider_split->setValue((_par->splitPourcent));
    value_split = new QLabel(QString::number(_par->splitPourcent));

    mainlayout->addWidget(titre_split,0,2);
    mainlayout->addWidget(value_split,1,2);
    mainlayout->addWidget(slider_split,2,2);

    setLayout(mainlayout);

    QObject::connect(slider_maxetage, SIGNAL(valueChanged(int)),this,SLOT(changer_maxetage()));
    QObject::connect(slider_influencecentreville, SIGNAL(valueChanged(int)),this,SLOT(changer_influencecentreville()));
    QObject::connect(slider_split, SIGNAL(valueChanged(int)),this,SLOT(changer_splitPourcent()));
}

void ParamWindow::update_values(){
    value_maxetage->setText(QString::number(_par->maxEtage));
    value_influencecentreville->setText(QString::number(_par->influenceCentreVille));
    value_split->setText(QString::number(_par->splitPourcent));
    update_sliders();
}

void ParamWindow::update_sliders(){
    QObject::disconnect(slider_maxetage, SIGNAL(valueChanged(int)),this,SLOT(changer_maxetage()));
    QObject::disconnect(slider_influencecentreville, SIGNAL(valueChanged(int)),this,SLOT(changer_influencecentreville()));

    slider_maxetage->setValue(_par->maxEtage);
    slider_influencecentreville->setValue((_par->influenceCentreVille*10.0));

    QObject::connect(slider_maxetage, SIGNAL(valueChanged(int)),this,SLOT(changer_maxetage()));
    QObject::connect(slider_influencecentreville, SIGNAL(valueChanged(int)),this,SLOT(changer_influencecentreville()));

}

void ParamWindow::changer_maxetage(){
    _par->maxEtage = slider_maxetage->value();
    *_glparent = false;
    update_values();
}

void ParamWindow::changer_influencecentreville(){
    _par->influenceCentreVille = slider_influencecentreville->value()/10.0;
    *_glparent = false;
    update_values();
}

void ParamWindow::changer_splitPourcent(){
    _par->splitPourcent = slider_split->value();
    *_glparent = false;
    update_values();
}
