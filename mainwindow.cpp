#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clipboard = QApplication::clipboard();

    QObject::connect(clipboard, &QClipboard::dataChanged, this, clipboardDataChanged);

    QAction *ctrlC_1 = new QAction(this);
    ctrlC_1->setShortcut(Qt::CTRL | Qt::Key_1);
    QObject::connect(ctrlC_1, &QAction::triggered, this, pushClipboard);
    this->addAction(ctrlC_1);

    QAction *ctrlV_1 = new QAction(this);
    ctrlV_1->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_1);
    QObject::connect(ctrlV_1, &QAction::triggered, this, popClipboard);
    this->addAction(ctrlV_1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushClipboard()
{
    mime_data = clipboard->mimeData();
    if (mime_data->hasText()) {
        multiple_buffer.prepend(mime_data->text());
    }
    std::cout << "push" << std::endl;
}

void MainWindow::popClipboard()
{
    if(!multiple_buffer.isEmpty())
        clipboard->setText(multiple_buffer.takeLast());
    std::cout << "pop" << std::endl;
}

void MainWindow::clipboardDataChanged()
{
 //   mime_data = clipboard->mimeData();
 //   if (mime_data->hasText()) {
 //       multiple_buffer.append(mime_data->text());
 //   }
}
