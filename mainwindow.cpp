#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    std::cout << "copied" << std::endl;
}

void MainWindow::popClipboard()
{
    std::cout << "passed" << std::endl;
}
