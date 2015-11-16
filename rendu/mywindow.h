#ifndef MYWINDOW_H
#include "myGLWidget.h"
#include "modele/batiment/batiment.h"
#include "modele/mesh.h"
#include "import_export/objmanager.h"
#include "modele/batiment/batparameter.h"
#include "modele/quartier/patern/paternequadresidence.h"
#include "paramwindow.h"
#define MYWINDOW_H


#include <QImage>

class myWindow : public myGLWidget
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );
    void keyReleaseEvent(QKeyEvent *keyEvent);
    void loadTexture(QString textureName);
    void _draw_text(double x, double y, double z, QString txt);
    Mesh _mesh;
    bool meshUpToDate;

private:
    float multiplicateurovertimezoom=1.0;
    float multiplicateurovertimerotation=1.0;
    float multiplicateurovertimeplonger=1.0;
    float multiplicateurovertimemonter=1.0;
    float _zoomspeed = 6;
    float _rotationspeed = 6;
    bool _zooming = false;
    bool _dezooming = false;
    bool _turningright = false;
    bool _turningleft = false;
    bool _plonger = false;
    bool _deplonger = false;
    bool _monter = false;
    bool _demonter = false;
    float _zoom = -20.0;
    GLuint texture[1];
    float _fx;
    float _speed;
    float _angle;
    float _hauteurcam;
    BatParameter _par;
    ParamWindow *frame;
};

#endif // MYWINDOW_H
