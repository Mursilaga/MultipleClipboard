#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QKeyEvent>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setTrayIconActions();
    this->showTrayIcon();

    for (int i=1; i<=9; i++) {
        RegisterHotKey(HWND(winId()), i, MOD_CONTROL, 0x30 + i);
    }

    for (int i=1; i<=9; i++) {
        RegisterHotKey(HWND(winId()), 10+i, MOD_ALT, 0x30 + i);
    }
    clipboard = QApplication::clipboard();
    QObject::connect(clipboard, &QClipboard::dataChanged, this, clipboardDataChanged);

    multiple_buffer.resize(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushClipboard(unsigned index)
{
    mime_data = clipboard->mimeData();
    if(mime_data->hasText()) {
        multiple_buffer[index] = mime_data->text();
    }
    QMessageBox::information(this, "Push", "Push to " + QString::number(index));
}

void MainWindow::popClipboard(unsigned index)
{
    index-=10; //keys id for pop differ on 10 from push
    if(!multiple_buffer.isEmpty())
        clipboard->setText(multiple_buffer[index]);
    QMessageBox::information(this, "Pop", "Pop from " + QString::number(index));
}

void MainWindow::clipboardDataChanged()
{
    //mime_data = clipboard->mimeData();
    //if (mime_data->hasText()) {
    //    multiple_buffer[0] = mime_data->text();
    //}
    //std::cout << "push to 0" << std::endl;
}

void MainWindow::showTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/arrow.png");
    trayIcon->setIcon(trayImage);
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon, &QSystemTrayIcon::activated, this, trayIconActivated);
    trayIcon->show();
}

void MainWindow::trayActionExecute()
{
    std::cout << "trayActionExecute" << std::endl;
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            this->trayActionExecute();
            break;
        default:
            break;
    }
}

void MainWindow::setTrayIconActions()
{
    minimizeAction = new QAction("Свернуть", this);
    restoreAction = new QAction("Восстановить", this);
    quitAction = new QAction("Выход", this);

    connect(minimizeAction, &QAction::triggered, this, hide);
    connect(restoreAction, &QAction::triggered, this, showNormal);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            this->hide();
        }
    }
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);
    MSG *msg = static_cast<MSG*>(message);
    if(msg->message == WM_HOTKEY) {
        if(msg->lParam & MOD_CONTROL) {
            pushClipboard((unsigned)msg->wParam);
        }
        else if (msg->lParam & MOD_ALT) {
            popClipboard((unsigned)msg->wParam);
        }
        return true;
    }
        return false;
}
