TEMPLATE = app

QT += gui widgets dbus
CONFIG += c++11 link_pkgconfig
PKGCONFIG += mpv
TARGET = wallpaper

SOURCES += main.cpp \
    wallpaper.cpp \
    dbuswallpaperservice.cpp \
    mpvwidget.cpp \
    settingwindow.cpp \
    application.cpp \
    moviepreview.cpp

HEADERS += \
    wallpaper.h \
    dbuswallpaperservice.h \
    mpvwidget.h \
    settingwindow.h \
    application.h \
    moviepreview.h

RESOURCES += \
    qrc.qrc

target.path = /usr/bin/

INSTALLS += target

FORMS += \
    settingwindow.ui
