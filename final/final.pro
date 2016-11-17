QT += core gui opengl network

TARGET = final
TEMPLATE = app

# If you add your own folders, add them to INCLUDEPATH and DEPENDPATH, e.g.
# INCLUDEPATH += folder1 folder2
# DEPENDPATH += folder1 folder2

SOURCES += main.cpp \
    mainwindow.cpp \
    view.cpp \
    sprite.cpp \
    plane.cpp \
    CS123Matrix.cpp \
    CS123Matrix.inl \
    CS123Vector.inl \
    game.cpp \
    meshmodel.cpp \
    tiny_obj_loader.cc \
    terrain.cpp \
    obj_parser/list.cpp \
    obj_parser/string_extra.cpp \
    obj_parser/obj_parser.cpp \
    obj_parser/objLoader.cpp \
    watershader.cpp \
    support.cpp \
    skydome.cpp \
    simplexnoise.cpp \
    weather.cpp \
    perlinterrain.cpp \
    remotecontrolreceiver.cpp \
    easywsclient.cpp \
    biomes.cpp

HEADERS += mainwindow.h \
    view.h \
    sprite.h \
    plane.h \
    final.h \
    CS123Algebra.h \
    CS123Common.h \
    game.h \
    meshmodel.h \
    tiny_obj_loader.h \
    terrain.h \
    obj_parser/objLoader.h \
    obj_parser/list.h \
    obj_parser/string_extra.h \
    obj_parser/obj_parser.h \
    watershader.h \
    support.h \
    skydome.h \
    simplexnoise.h \
    weather.h \
    perlinterrain.h \
    remotecontrolreceiver.h \
    easywsclient.hpp \
    biomes.h

FORMS += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
