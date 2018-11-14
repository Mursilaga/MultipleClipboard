#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMimeData>
#include <QClipboard>
#include <QSystemTrayIcon>
#include "windows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void pushClipboard(unsigned index);
    void popClipboard(unsigned index);

private:
    Ui::MainWindow *ui;

    QVector<QString> multiple_buffer;

    QClipboard *clipboard;
    const QMimeData *mime_data;

    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;

    void clipboardDataChanged();

    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();

    void changeEvent(QEvent*);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    bool isWindowHidden;

};

#endif // MAINWINDOW_H
