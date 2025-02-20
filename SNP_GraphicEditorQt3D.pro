QT       += core gui 3dcore 3dlogic 3dextras 3dinput

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basicfigure.cpp \
    cuboid.cpp \
    downloadobject.cpp \
    main.cpp \
    mainwindow.cpp \
    modulecamera.cpp \
    spheroid.cpp \
    toroid.cpp

HEADERS += \
    basicfigure.hpp \
    cuboid.hpp \
    downloadobject.hpp \
    mainwindow.hpp \
    modulecamera.hpp \
    spheroid.hpp \
    toroid.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  models.qrc
