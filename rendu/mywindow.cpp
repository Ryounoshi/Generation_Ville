#include "myWindow.h"
#include <QDebug>
#include "modele/terrainbase.h"
#include "modele/quartier/quartier.h"
#include "stdio.h"

bool townmode;

myWindow::myWindow(QWidget *parent)
    : myGLWidget(60, parent, "Génération ville")
{
}

void myWindow::_draw_text(double x, double y, double z, QString txt)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0,1.0,1.0);
    renderText(x, y, z, txt, QFont("Arial", 12, QFont::Bold, false) );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}


void myWindow::initializeGL()
{
    _fx = 0.0;
    _speed =0.1;
    _angle = -50.0;
    _hauteurcam = -2.0;
    townmode = true;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glShadeModel(GL_SMOOTH);
    glClearColor(24.0f/255.0f, 94.0f/255.0f, 139.0f/255.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    meshUpToDate = false;
    frame = new ParamWindow(0,&meshUpToDate,&_par);
    frame->show();

}

void myWindow::loadTexture(QString textureName){
    QImage qim_Texture;
    QImage qim_TempTexture;
    qim_TempTexture.load(textureName);
    qim_Texture = QGLWidget::convertToGLFormat( qim_TempTexture );
    glGenTextures( 1, &texture[0] );
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void myWindow::keyReleaseEvent(QKeyEvent *keyEvent){
    switch(keyEvent->key())
    {
            //zoom
        case Qt::Key_Z:
            _zooming = false;
        break;
        case Qt::Key_S:
            _dezooming = false;
        break;
            //rotation
        case Qt::Key_Left:
            _turningright = false;
        break;
        case Qt::Key_Right:
            _turningleft = false;
        break;
            //angle
        case Qt::Key_Up:
            _plonger = false;
        break;
        case Qt::Key_Down:
            _deplonger = false;
        break;
            //hauteur camera
        case Qt::Key_E:
            _monter = false;
        break;
        case Qt::Key_A:
            _demonter = false;
        break;
        case Qt::Key_V:
            townmode = !townmode;
            meshUpToDate = false;
        break;
    }
}

void myWindow::keyPressEvent(QKeyEvent *keyEvent)
{

    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Plus:
            _speed += 0.05;
        break;
        case Qt::Key_Minus:
            _speed -= 0.05;
        break;
            //zoom
        case Qt::Key_Z:
            _zooming = true;
        break;
        case Qt::Key_S:
            _dezooming = true;
        break;
            //zoom
        case Qt::Key_T:
            _par.hauteurEtage += 0.5;
            std::cout << "Hauteur Etage (m) : " << _par.hauteurEtage << std::endl;
            meshUpToDate = false;
        break;
        case Qt::Key_G:
            _par.hauteurEtage -= 0.5;
            if(_par.hauteurEtage <1.0)_par.hauteurEtage = 1.0;
            std::cout << "Hauteur Etage (m) : " << _par.hauteurEtage << std::endl;
            meshUpToDate = false;
        break;
            //rotation
        case Qt::Key_Left:
            _turningright = true;
        break;
        case Qt::Key_Right:
            _turningleft = true;
        break;
            //angle
        case Qt::Key_Up:
            _plonger = true;
            //_angle -= 5.0;
        break;
        case Qt::Key_Down:
            _deplonger = true;
            //_angle += 5.0;
        break;
            //hauteur camera
        case Qt::Key_E:
            _monter = true;
        break;
        case Qt::Key_A:
            _demonter = true;
        break;
            //position centreville
        case Qt::Key_8:
            _par._centreVille.y -= 10.0;
            meshUpToDate = false;
        break;
        case Qt::Key_2:
            _par._centreVille.y += 10.0;
            meshUpToDate = false;
        break;
        case Qt::Key_4:
            _par._centreVille.x -= 10.0;
            meshUpToDate = false;
        break;
        case Qt::Key_6:
            _par._centreVille.x += 10.0;
            meshUpToDate = false;
        break;
        // hauteur max
        case Qt::Key_P:
            _par.maxEtage += 1;
            meshUpToDate = false;
        break;
        case Qt::Key_M:
            _par.maxEtage -= 1;
            meshUpToDate = false;
        break;
        // influence centreville
        case Qt::Key_O:
            _par.influenceCentreVille += .1;
            meshUpToDate = false;
        break;
        case Qt::Key_L:
            _par.influenceCentreVille -= .1;
            meshUpToDate = false;
        break;
        //reset params
        case Qt::Key_N:
            _par.influenceCentreVille = DEFAULT_INFLUENCE_CENTREVILLE;
            _par._centreVille.set(0,0,0);
            _par.maxEtage = DEFAULT_MAX_ETAGE;
            meshUpToDate = false;
        break;
        //sauver mesh
        case Qt::Key_B:
            ObjManager::writeToObj("ville.obj", _mesh.getVertex(), _mesh.getFace());
        break;

        case Qt::Key_Y:
            _par.minLargeurBatiment *= 1.1;
            meshUpToDate = false;
        break;
        case Qt::Key_U:
            _par.minLargeurBatiment *= 0.9;
            meshUpToDate = false;
        break;

    }
}


// Replaces gluPerspective. Sets the frustum to perspective mode.
// fovY     - Field of vision in degrees in the y direction
// aspect   - Aspect ratio of the viewport
// zNear    - The near clipping distance
// zFar     - The far clipping distance
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );

}


void myWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(90.0f, (GLfloat)width/(GLfloat)height, 0.1f, 800.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myWindow::paintGL()
{
    double deltaTime = t_Timer->interval()/1000.0;

    int LightPos[4] = {1,5,-1,0};
    int Light2Pos[4] = {-2,7,2,0};
    int Light3Pos[4] = {5,4,0,0};
    _fx += _speed;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPolygonMode( GL_FRONT, GL_FILL );

    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    glLightiv(GL_LIGHT1,GL_POSITION,Light2Pos);
    glLightiv(GL_LIGHT2,GL_POSITION,Light3Pos);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 10);

    //zoom
    if(_zooming){
        multiplicateurovertimezoom += 0.15;
        _zoom += _zoomspeed * multiplicateurovertimezoom * deltaTime;
    }else if(_dezooming){
        multiplicateurovertimezoom += 0.15;
        _zoom -= _zoomspeed * multiplicateurovertimezoom * deltaTime;
    }else{
        multiplicateurovertimezoom = 1.0;
    }
    //rotation
    if(_turningleft){
        multiplicateurovertimerotation += 0.15;
        _fx -= _rotationspeed * multiplicateurovertimerotation * deltaTime;
    }else if(_turningright){
        multiplicateurovertimerotation += 0.15;
        _fx += _rotationspeed * multiplicateurovertimerotation * deltaTime;
    }else{
        multiplicateurovertimerotation = 1.0;
    }
    //angle
    if(_plonger){
        multiplicateurovertimeplonger += 0.15;
        _angle += _rotationspeed* multiplicateurovertimeplonger *deltaTime;
    }else if(_deplonger){
        multiplicateurovertimeplonger += 0.15;
        _angle -= _rotationspeed* multiplicateurovertimeplonger *deltaTime;
    }else{
        multiplicateurovertimeplonger = 1.0;
    }
    //hauteur camera
    if(_monter){
        multiplicateurovertimemonter += 0.15;
        _hauteurcam -= 2 * multiplicateurovertimemonter *deltaTime;
    }else if(_demonter){
        multiplicateurovertimemonter += 0.15;
        _hauteurcam += 2 * multiplicateurovertimemonter *deltaTime;
    }else{
        multiplicateurovertimemonter = 1.0;
    }

    glTranslatef(0.f, _hauteurcam, _zoom);
    glRotated(_angle,1,0,0);
    glRotated(_fx,0,0,1);

    //***************************************//
    //************* Création Mesh ***********//
    //***************************************//

    if(!meshUpToDate){
        _par.resetEtageLePlusHaut();

        qDebug()<<_mesh.nbFace();

        if(townmode){
            std::vector<TerrainBase> bases;
            bases.push_back(TerrainBase(Triangle(Vector2D(0,200),Vector2D(200,-200),Vector2D(-200,-200)), &_par));
            bases.push_back(TerrainBase(Quadrangle(Vector2D(0,200),Vector2D(200,400),Vector2D(400,200),Vector2D(200,-200)), &_par));
            bases.push_back(TerrainBase(Quadrangle(Vector2D(200,-200),Vector2D(200,-400),Vector2D(-200,-400),Vector2D(-200,-200)), &_par));
            bases.push_back(TerrainBase(Quadrangle(Vector2D(-200,-200),Vector2D(-400,200),Vector2D(-200,400),Vector2D(0,200)), &_par));

            bases.push_back(TerrainBase(Triangle(Vector2D(250,-200),Vector2D(500,200),Vector2D(500,-200)), &_par));
            bases.push_back(TerrainBase(Quadrangle(Vector2D(250,-200),Vector2D(500,-200),Vector2D(450,-350),Vector2D(250,-400)), &_par));

            Mesh m1;
            for(TerrainBase& base : bases)
            {
                std::vector<Vector2D> points = base.getPoints();
                m1.addTriangle(Vector3D(XY(points[0]), 0), Vector3D(XY(points[2]), 0), Vector3D(XY(points[1]), 0));
                if(points.size() == 4)
                    m1.addTriangle(Vector3D(XY(points[0]), 0), Vector3D(XY(points[3]), 0), Vector3D(XY(points[2]), 0));

                base.decoupeSimple(4000);
                base.shrink(2.f);
                m1.merge(base.generate());
            }
            _mesh = m1;
        }else{
            float lar,lon;
            lar = 10.0;
            lon = 10.0+rand()%10;

            Vector3D p1(-lar-7.5+rand()%15,-lon-7.5+rand()%15,0);
            Vector3D p2(-lar-7.5+rand()%15,lon-7.5+rand()%15,0);
            Vector3D p3(lar-7.5+rand()%15,lon-7.5+rand()%15,0);
            Vector3D p4(lar-7.5+rand()%15,-lon-7.5+rand()%15,0);

            Batiment test(p1,
                          p2,
                          p3,
                          p4,
                          &_par);

            Mesh m1;
            m1.merge(test.generate());
            _mesh = m1;
        }

        meshUpToDate = true;
        frame->update_values();
    }
    glEnable(GL_LIGHTING);
    int nbfaces = _mesh.nbFace();
    for(int i=0; i<nbfaces; i+=3){
        Vector3D dir1, dir2; //pour le calcul des normals
        Vector3D normal;
        Vector3D p1 = _mesh.getVertex(_mesh.getFace(i));
        Vector3D p2 = _mesh.getVertex(_mesh.getFace(i+1));
        Vector3D p3 = _mesh.getVertex(_mesh.getFace(i+2));
        dir1 = p2-p1;
        dir2 = p3-p1;
        normal = dir1.crossProduct(dir2);
        normal.normalize();;
        glColor3f(0.0,1.0,0.0); //Y vert
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glBegin(GL_TRIANGLES);
            glNormal3f(normal.x,normal.y,normal.z);
            glVertex3f(p1.x,p1.y,p1.z);
            glVertex3f(p2.x,p2.y,p2.z);
            glVertex3f(p3.x,p3.y,p3.z);
        glEnd();
    }

    glDisable(GL_LIGHTING);
    float angle = (2*M_PI)/64;
    glColor3f(1.0,0.2,0.2);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);

    for(float i = 0; i < 2*M_PI ; i+=angle){
        glVertex3f(cos(i)*200*_par.influenceCentreVille+_par._centreVille.x, sin(i)*200*_par.influenceCentreVille+_par._centreVille.y,10);
    }
    glEnd();
    _draw_text(_par.hauteurEtageLePlusHaut.x,_par.hauteurEtageLePlusHaut.y,_par.hauteurEtageLePlusHaut.z,QString(QString::number(_par.etageLePlusHaut)));
}
