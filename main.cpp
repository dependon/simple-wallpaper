#include <QObject>

#include "application.h"
#include "wallpaper.h"
#include "dbuswallpaperservice.h"
#include <malloc.h>
#include "settingwindow.h"
#include <QMainWindow>


int main(int argc, char *argv[])
{
	qputenv("QT_QPA_PLATFORM", "xcb");
    mallopt(M_ARENA_MAX, 1);

    Application a(argc, argv);

    setlocale(LC_NUMERIC, "C");

    if (true) {
        a.setApplicationName(QObject::tr("Simple DreamScene"));
        a.setApplicationVersion("Version 0.1");

        Wallpaper *w = new Wallpaper;
        DBusWallpaperService *dbusInter = new DBusWallpaperService(w);
        Q_UNUSED(dbusInter);

        QDBusConnection::sessionBus().registerService("com.github.wallpaper.fantascene");
        QDBusConnection::sessionBus().registerObject("/com/github/wallpaper/fantascene", "com.github.wallpaper.fantascene", w);

        settingWindow *window=new settingWindow();

        window->show();

    }

    return a.exec();
}


