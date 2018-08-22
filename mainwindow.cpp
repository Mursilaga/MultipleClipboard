#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clipboard = QApplication::clipboard();
    QObject::connect(clipboard, &QClipboard::dataChanged, this, clipboardDataChanged);

    multiple_buffer.resize(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_1)
        pushClipboard(1);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_2)
        pushClipboard(2);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_3)
        pushClipboard(3);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_4)
        pushClipboard(4);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_5)
        pushClipboard(5);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_6)
        pushClipboard(6);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_7)
        pushClipboard(7);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_8)
        pushClipboard(8);
    else if(event->modifiers() == Qt::CTRL && event->key() == Qt::Key_9)
        pushClipboard(9);

    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_1)
        popClipboard(1);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_2)
        popClipboard(2);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_3)
        popClipboard(3);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_4)
        popClipboard(4);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_5)
        popClipboard(5);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_6)
        popClipboard(6);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_7)
        popClipboard(7);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_8)
        popClipboard(8);
    else if(event->modifiers() == Qt::ALT && event->key() == Qt::Key_9)
        popClipboard(9);
}
void MainWindow::pushClipboard(unsigned index)
{
    mime_data = clipboard->mimeData();
    if(mime_data->hasText()) {
        multiple_buffer[index] = mime_data->text();
    }
    std::cout << "push to " << index << std::endl;
}

void MainWindow::popClipboard(unsigned index)
{
    if(!multiple_buffer.isEmpty())
        clipboard->setText(multiple_buffer[index]);
    std::cout << "pop from " << index << std::endl;
}

void MainWindow::clipboardDataChanged()
{
    //mime_data = clipboard->mimeData();
    //if (mime_data->hasText()) {
    //    multiple_buffer[0] = mime_data->text();
    //}
    //std::cout << "push to 0" << std::endl;
}
