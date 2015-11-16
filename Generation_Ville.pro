TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core
QT += gui
QT += opengl
LIBS += -lopengl32 -lglu32

SOURCES += main.cpp \
    geometrie/vector3d.cpp \
    geometrie/box.cpp \
    import_export/objmanager.cpp \
    modele/mesh.cpp \
    geometrie/quadrangle.cpp \
    geometrie/Triangle.cpp \
    geometrie/polygone.cpp \
    geometrie/pentagone.cpp \
    modele/terrainbase.cpp \
    rendu/myglwidget.cpp \
    rendu/mywindow.cpp \
    modele/batiment/toit.cpp \
    modele/batiment/etage.cpp \
    modele/batiment/rezdechausse.cpp\
    modele/batiment/batiment.cpp \
    modele/batiment/batparameter.cpp \
    rendu/paramwindow.cpp \
    geometrie/rayon.cpp \
    modele/quartier/quarpenta.cpp \
    modele/quartier/quarquad.cpp \
    modele/quartier/quartier.cpp \
    modele/quartier/quartri.cpp \
    modele/quartier/patern/paternequadresidence.cpp \
    math/noisegenerator.cpp



HEADERS += \
    geometrie/vector2d.h \
    geometrie/vector3d.h \
    geometrie/box.h \
    import_export/objmanager.h \
    modele/mesh.h \
    geometrie/quadrangle.h \
    geometrie/Triangle.h \
    geometrie/polygone.h \
    geometrie/pentagone.h \
    modele/terrainbase.h \
    rendu/myglwidget.h \
    rendu/mywindow.h \
    modele/batiment/toit.h \
    modele/batiment/etage.h \
    modele/batiment/rezdechausse.h\
    modele/interface_ville.h \
    modele/batiment/batiment.h \
    modele/batiment/batparameter.h \
    rendu/paramwindow.h \
    geometrie/rayon.h \
    modele/quartier/quarpenta.h \
    modele/quartier/quarquad.h \
    modele/quartier/quartier.h \
    modele/quartier/quartri.h \
    modele/quartier/patern/paternequadresidence.h \
    math/noisegenerator.h


