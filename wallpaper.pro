TEMPLATE = app

QT += gui widgets dbus
CONFIG += c++11 link_pkgconfig
PKGCONFIG += mpv
TARGET = simple-wallpaper

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

icon.path=/usr/share/icons
icon.files= $$PWD/install/simple-wallpaper.png

desktop.path = /usr/share/applications/
desktop.files = $$PWD/install/simple-wallpaper.desktop

INSTALLS += target icon desktop

FORMS += \
    settingwindow.ui
