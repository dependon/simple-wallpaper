#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include <QCoreApplication>
#include <QString>
#include <QObject>


#define dApp (static_cast<Application*>(QCoreApplication::instance()))
class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int& argc, char **argv);
    ~Application();

Q_SIGNALS:
    void setPlayPath(const QString &PATH);
    void setMpvPlay();
    void setMpvpause();
    void setMpvstop();
    void setMpvVolume(const qint32 volume);


};

#endif // APPLICATION_H
