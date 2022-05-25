#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QSystemTrayIcon>
#include <QFileDialog>
#include <QMenu>
#include <QMainWindow>
#include "moviepreview.h"

settingWindow::settingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingWindow)
{
    ui->setupUi(this);
    m_traymenu=new QMenu();
    QAction *exitAction=new QAction(m_traymenu);
    exitAction->setText(tr("Exit"));
    connect(exitAction,&QAction::triggered,dApp,exit);

    QAction *setMpvPlayAction=new QAction(m_traymenu);
    setMpvPlayAction->setText(tr("Play"));
    connect(setMpvPlayAction,&QAction::triggered,dApp,&Application::setMpvPlay);

    QAction *setMpvpauseAction=new QAction(m_traymenu);
    setMpvpauseAction->setText(tr("Pause"));
    connect(setMpvpauseAction,&QAction::triggered,dApp,&Application::setMpvpause);

    //    QAction *setMpvstopAction=new QAction(m_traymenu);
    //    setMpvstopAction->setText("停止");
    //    connect(setMpvstopAction,&QAction::triggered,dApp,&Application::setMpvstop);

    m_traymenu->addAction(setMpvPlayAction);
    m_traymenu->addAction(setMpvpauseAction);
    //    m_traymenu->addAction(setMpvstopAction);
    m_traymenu->addAction(exitAction);

    m_trayIcon=new QSystemTrayIcon (this);
    m_trayIcon->setContextMenu(m_traymenu);
    m_trayIcon->setToolTip(tr("Double clicked to settings"));
    m_trayIcon->setIcon(QIcon(":/wallpaper.ico"));
    m_trayIcon->show();
    //void activated(QSystemTrayIcon::ActivationReason reason);
    connect(m_trayIcon,&QSystemTrayIcon::activated,this,[=](QSystemTrayIcon::ActivationReason reason){
        if(QSystemTrayIcon::Trigger==reason){
            if(m_parentMainWindow){
                m_parentMainWindow->show();
                m_parentMainWindow->activateWindow();
            }
        }
    });

    MoviePreview::instance();
}

settingWindow::~settingWindow()
{
    delete ui;
}

void settingWindow::on_pathBtn_clicked()
{
    QString path=QFileDialog::getOpenFileName();
    ui->pathEdit->setText(path);
}

void settingWindow::on_setBtn_clicked()
{
    if(ui->pathEdit->text()!=nullptr){
        emit dApp->setPlayPath(ui->pathEdit->text());
        emit dApp->setMpvPlay();
    }
}

void settingWindow::on_cancelBtn_clicked()
{
    if(m_parentMainWindow){
        m_parentMainWindow->close();
    }
}

void settingWindow::on_pauseBtn_clicked()
{
    emit dApp->setMpvpause();
}

void settingWindow::on_stopBtn_clicked()
{
    emit dApp->setMpvstop();
}

void settingWindow::on_Slider_valueChanged(int value)
{
    emit dApp->setMpvVolume(value);
}

void settingWindow::on_startBtn_clicked()
{
    emit dApp->setMpvPlay();
}

void settingWindow::on_pathEdit_textChanged(const QString &arg1)
{
    if(MoviePreview::instance()->isFile(arg1)){
        QImage img=MoviePreview::instance()->getMoviePreview(arg1);
        ui->pixLabel->setPixmap(QPixmap::fromImage(img));
    }
}
