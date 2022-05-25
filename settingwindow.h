#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include "application.h"
#include <QMainWindow>

class QSystemTrayIcon;
class QMenu;

namespace Ui {
class settingWindow;
}

class settingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit settingWindow(QWidget *parent = nullptr);
    ~settingWindow();

private slots:
    void on_pathBtn_clicked();

    void on_setBtn_clicked();

    void on_cancelBtn_clicked();

    void on_pauseBtn_clicked();

    void on_stopBtn_clicked();

    void on_Slider_valueChanged(int value);

    void on_startBtn_clicked();

    void on_pathEdit_textChanged(const QString &arg1);

private:
    Ui::settingWindow *ui;
    QSystemTrayIcon *m_trayIcon{nullptr};
    QMenu *m_traymenu{nullptr};
    QMainWindow *m_parentMainWindow{nullptr};
};

#endif // SETTINGWINDOW_H
